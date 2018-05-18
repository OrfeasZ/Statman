using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection.Emit;
using System.Runtime.InteropServices;
using System.Text;

namespace Statman.Util.Injection
{
    public class Injector : IDisposable
    {
        private class ProcessModuleInfo
        {
            public MODULEINFO Info { get; set; }

            public string FullPath { get; set; }
        }

        public bool EjectOnDispose { get; set; }

        private readonly Process m_Process;
        private IntPtr m_Handle;
        private readonly Dictionary<string, ProcessModuleInfo> m_InjectedModules;

        public Injector(Process p_Process) : this(p_Process, true) { }

        public Injector(Process p_Process, bool p_EjectOnDispose)
        {
            if (p_Process == null)
                throw new ArgumentNullException(nameof(p_Process));

            if (p_Process.Id == Process.GetCurrentProcess().Id)
                throw new InvalidOperationException("Cannot create an injector for the current process");

            Process.EnterDebugMode();

            m_Handle = Imports.OpenProcess(
                ProcessAccessFlags.QueryInformation | ProcessAccessFlags.CreateThread |
                ProcessAccessFlags.VMOperation | ProcessAccessFlags.VMWrite |
                ProcessAccessFlags.VMRead, false, p_Process.Id);

            if (m_Handle == IntPtr.Zero)
                throw new Win32Exception(Marshal.GetLastWin32Error());

            m_Process = p_Process;
            EjectOnDispose = p_EjectOnDispose;
            m_InjectedModules = new Dictionary<string, ProcessModuleInfo>();
        }

        private static string ConvertNTPathToDOS(string p_Path)
        {
            var s_DriveStringsBuf = new char[2048];

            if (Imports.GetLogicalDriveStrings((uint) (s_DriveStringsBuf.Length - 1), s_DriveStringsBuf) == 0)
                return p_Path;

            var s_DriveStrings = new string(s_DriveStringsBuf);
            var s_Drives = s_DriveStrings.Split(new[]{ '\0' }, StringSplitOptions.RemoveEmptyEntries);

            var s_DosDevMem = Marshal.AllocHGlobal(2048);

            foreach (var s_Drive in s_Drives)
            { 
                // Look up each device name
                var s_FinalLen = Imports.QueryDosDevice(s_Drive.Substring(0, 2), s_DosDevMem, 2048);

                if (s_FinalLen == 0)
                    continue;

                var s_Device = Marshal.PtrToStringAnsi(s_DosDevMem, s_FinalLen).Trim('\0');
                
                // Is this the device the file is in?
                if (p_Path.StartsWith(s_Device))
                {
                    Marshal.FreeHGlobal(s_DosDevMem);
                    return p_Path.Replace(s_Device, s_Drive.Substring(0, 2));
                }
            }

            Marshal.FreeHGlobal(s_DosDevMem);

            return p_Path;
        }

        private static IEnumerable<ProcessModuleInfo> EnumerateProcessModules(Process p_Process)
        {
            var s_Modules = new IntPtr[0];

            // Don't request data, only used for module count.
            if (!Imports.EnumProcessModulesEx(p_Process.Handle, s_Modules, 0, out var s_BytesNeeded, (uint) ModuleFilterFlags.ListModulesAll))
                yield break;

            // Allocate storage.
            s_Modules = new IntPtr[s_BytesNeeded / IntPtr.Size];

            // Enumerate all the loaded modules.
            if (!Imports.EnumProcessModulesEx(p_Process.Handle, s_Modules, s_BytesNeeded, out s_BytesNeeded, (uint) ModuleFilterFlags.ListModulesAll))
                yield break;

            foreach (var s_Module in s_Modules)
            {
                if (!Imports.GetModuleInformation(p_Process.Handle, s_Module, out var s_ModuleInfo, (uint) (s_Modules.Length * IntPtr.Size)))
                    continue;

                // Try getting the mapped name.
                var s_PathBuilder = new StringBuilder(1024);

                // If this doesn't work try to get the module file name normally.
                // This might result in getting back redirected WOW64 paths when cross-examining.
                if (Imports.GetMappedFileName(p_Process.Handle, s_ModuleInfo.lpBaseOfDll, s_PathBuilder,
                        (uint) s_PathBuilder.Capacity) == 0 || s_PathBuilder.Length == 0)
                {
                    // If this fails too then there's something else going on here. We don't care much for drama.
                    if (Imports.GetModuleFileNameEx(p_Process.Handle, s_Module, s_PathBuilder, (uint) s_PathBuilder.Capacity) == 0)
                        continue;
                }
                else
                {
                    s_PathBuilder = new StringBuilder(ConvertNTPathToDOS(s_PathBuilder.ToString()));
                }
                
                yield return new ProcessModuleInfo()
                {
                    FullPath = s_PathBuilder.ToString(),
                    Info = s_ModuleInfo,
                };
            }
        }

        private static IntPtr GetRemoteProcAddress(Process p_Process, string p_Module, string p_Function)
        {
            foreach (var s_Module in EnumerateProcessModules(p_Process))
            {
                string s_FileName = Path.GetFileName(s_Module.FullPath);

                // These are not the modules you're looking for ✌️
                if (!s_FileName.Equals(p_Module, StringComparison.OrdinalIgnoreCase) &&
                    !s_FileName.Equals(p_Module + ".dll", StringComparison.OrdinalIgnoreCase))
                    continue;

                // We found our module. Let's find the function address!
                try
                {
                    // Parse the PE file.
                    var s_PE = new PeNet.PeFile(s_Module.FullPath);

                    // Find the export for our function.
                    foreach (var s_Function in s_PE.ExportedFunctions)
                    {
                        if (string.IsNullOrWhiteSpace(s_Function.Name))
                            continue;

                        if (s_Function.Name != p_Function)
                            continue;

                        // We got it!
                        return new IntPtr(s_Module.Info.lpBaseOfDll.ToInt64() + s_Function.Address);
                    }
                }
                catch
                {
                    // ignored
                }

                // Stop the process if we found the module but not the function.
                return IntPtr.Zero;
            }

            return IntPtr.Zero;
        }

        private static ProcessModuleInfo GetProcessModuleInfo(Process p_Process, string p_Module)
        {
            foreach (var s_Module in EnumerateProcessModules(p_Process))
            {
                string s_FileName = Path.GetFileName(s_Module.FullPath);

                // These are not the modules you're looking for ✌️
                if (!s_FileName.Equals(p_Module, StringComparison.OrdinalIgnoreCase) &&
                    !s_FileName.Equals(p_Module + ".dll", StringComparison.OrdinalIgnoreCase))
                    continue;

                return s_Module;
            }

            return null;
        }

        /// <summary>
        /// Injects a library into this Injector's process. <paramref name="p_LibPath"/> can be 
        /// relative or absolute; either way, the injected module will be referred to by module name only.
        /// I.e. "c:\some\directory\library.dll", "library.dll" and "..\library.dll" will all be referred to
        /// as "library.dll"
        /// </summary>
        /// <param name="p_LibPath">Relative or absolute path to the dll to be injected</param>
        public void InjectLibrary(string p_LibPath)
        {
            // (in?)sanity check, pretty sure this is never possible as the constructor will error - left over from how it previously was developed
            if (m_Process == null)
                throw new InvalidOperationException("This injector has no associated process and thus cannot inject a library");

            if (m_Handle == IntPtr.Zero)
                throw new InvalidOperationException("This injector does not have a valid handle to the associated process and thus cannot inject a library");

            if (!File.Exists(p_LibPath))
                throw new FileNotFoundException($"Unable to find library {p_LibPath} to inject into process {m_Process.ProcessName}", p_LibPath);

            // convenience variables
            string s_FullPath = Path.GetFullPath(p_LibPath);
            string s_LibName = Path.GetFileName(s_FullPath);

            // declare resources that need to be freed in finally
            IntPtr s_PathMemoryPtr = IntPtr.Zero; // pointer to allocated memory of lib path string
            IntPtr s_RemoteThreadHandle = IntPtr.Zero; // handle to thread from CreateRemoteThread
            IntPtr s_UnmanagedPath = Marshal.StringToHGlobalUni(s_FullPath); // unmanaged C-String pointer

            try
            {
                var s_ByteCount = (uint) Encoding.Unicode.GetByteCount(s_FullPath);

                IntPtr s_LoadLibraryPtr = GetRemoteProcAddress(m_Process, "kernel32.dll", "LoadLibraryW");

                if (s_LoadLibraryPtr == IntPtr.Zero)
                    throw new Win32Exception(Marshal.GetLastWin32Error());

                // allocate memory to the local process for libFullPath
                s_PathMemoryPtr = Imports.VirtualAllocEx(m_Handle, IntPtr.Zero, s_ByteCount, AllocationType.Commit, MemoryProtection.ReadWrite);

                if (s_PathMemoryPtr == IntPtr.Zero)
                    throw new Win32Exception(Marshal.GetLastWin32Error());

                // write libFullPath to pLibPath
                if (!Imports.WriteProcessMemory(m_Handle, s_PathMemoryPtr, s_UnmanagedPath, s_ByteCount, out var s_BytesWritten) || s_BytesWritten != (int)s_ByteCount)
                    throw new Win32Exception(Marshal.GetLastWin32Error());

                Debug.WriteLine(Marshal.GetLastWin32Error());

                // load dll via call to LoadLibrary using CreateRemoteThread
                s_RemoteThreadHandle = Imports.CreateRemoteThread(m_Handle, IntPtr.Zero, 0, s_LoadLibraryPtr, s_PathMemoryPtr, 0, IntPtr.Zero);

                Debug.WriteLine(Marshal.GetLastWin32Error());

                if (s_RemoteThreadHandle == IntPtr.Zero)
                    throw new Win32Exception(Marshal.GetLastWin32Error());

                if (Imports.WaitForSingleObject(s_RemoteThreadHandle, (uint)ThreadWaitValue.Infinite) != (uint)ThreadWaitValue.Object0)
                    throw new Win32Exception(Marshal.GetLastWin32Error());

                // get address of loaded module - this doesn't work in x64, so just iterate module list to find injected module
                if (!Imports.GetExitCodeThread(s_RemoteThreadHandle, out IntPtr s_ModuleHandle))
                    throw new Win32Exception(Marshal.GetLastWin32Error());

                if (s_ModuleHandle == IntPtr.Zero)
                    throw new Exception("Code executed properly, but unable to get an appropriate module handle, possible Win32Exception", new Win32Exception(Marshal.GetLastWin32Error()));

                // iterate modules in target process to find our newly injected module
                var s_LoadedModule = GetProcessModuleInfo(m_Process, s_LibName);

                if (s_LoadedModule == null)
                    throw new Exception("Injected module could not be found within the target process!");

                m_InjectedModules.Add(s_LibName, s_LoadedModule);
            }
            finally
            {
                Marshal.FreeHGlobal(s_UnmanagedPath); // free unmanaged string
                Imports.CloseHandle(s_RemoteThreadHandle); // close thread from CreateRemoteThread
                Imports.VirtualFreeEx(m_Process.Handle, s_PathMemoryPtr, 0, AllocationType.Release); // Free memory allocated
            }
        }

        /// <summary>
        /// Ejects a library that this Injector has previously injected into the target process. <paramref name="p_LibName"/> is the name of the module to
        /// eject, as per the name stored in <see cref="Injector.InjectLibrary"/>. Passing the same value as passed to InjectLibrary should always work unless a 
        /// relative path was used and the program's working directory has changed.
        /// </summary>
        /// <param name="p_LibName">The name of the module to eject</param>
        public void EjectLibrary(string p_LibName)
        {
            string s_LibSearchName = File.Exists(p_LibName) ? Path.GetFileName(Path.GetFullPath(p_LibName)) : p_LibName;

            if (!m_InjectedModules.ContainsKey(s_LibSearchName))
                throw new InvalidOperationException("That module has not been injected into the process and thus cannot be ejected");

            // resources that need to be freed
            IntPtr s_RemoteThreadHandle = IntPtr.Zero;

            try
            {
                // get handle to kernel32 and FreeLibrary
                IntPtr s_FreeLibraryPtr = GetRemoteProcAddress(m_Process, "kernel32.dll", "FreeLibrary");

                if (s_FreeLibraryPtr == IntPtr.Zero)
                    throw new Win32Exception(Marshal.GetLastWin32Error());

                s_RemoteThreadHandle = Imports.CreateRemoteThread(m_Handle, IntPtr.Zero, 0, s_FreeLibraryPtr,
                    m_InjectedModules[s_LibSearchName].Info.lpBaseOfDll, 0, IntPtr.Zero);

                if (s_RemoteThreadHandle == IntPtr.Zero)
                    throw new Win32Exception(Marshal.GetLastWin32Error());

                if (Imports.WaitForSingleObject(s_RemoteThreadHandle, (uint) ThreadWaitValue.Infinite) != (uint) ThreadWaitValue.Object0)
                    throw new Win32Exception(Marshal.GetLastWin32Error());

                // get exit code of FreeLibrary
                if (!Imports.GetExitCodeThread(s_RemoteThreadHandle, out IntPtr s_ModuleHandle))
                    throw new Win32Exception(Marshal.GetLastWin32Error());

                if (s_ModuleHandle == IntPtr.Zero)
                    throw new Exception("FreeLibrary failed in remote process");
            }
            catch
            {
                // ignored
            }
            finally
            {
                Imports.CloseHandle(s_RemoteThreadHandle);
            }
        }
        
        #region IDisposable Members

        public void Dispose()
        {
            if (EjectOnDispose)
                foreach (var s_Key in m_InjectedModules.Keys)
                    EjectLibrary(s_Key);
            
            if (m_Handle != IntPtr.Zero)
                Imports.CloseHandle(m_Handle);

            m_Handle = IntPtr.Zero;

            Process.LeaveDebugMode();
        }

        #endregion
    }
}
