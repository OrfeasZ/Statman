using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Statman.Util.Injection
{
    /// <summary>
    /// Memory allocation type - taken from #defines in WinNT.h
    /// </summary>
    [Flags]
    public enum AllocationType : uint
    {
        Commit = 0x1000,       //#define MEM_COMMIT           0x1000     
        Reserve = 0x2000,       //#define MEM_RESERVE          0x2000     
        Decommit = 0x4000,       //#define MEM_DECOMMIT         0x4000     
        Release = 0x8000,       //#define MEM_RELEASE          0x8000     
        Free = 0x10000,      //#define MEM_FREE            0x10000     
        Private = 0x20000,      //#define MEM_PRIVATE         0x20000     
        Mapped = 0x40000,      //#define MEM_MAPPED          0x40000     
        Reset = 0x80000,      //#define MEM_RESET           0x80000     
        TopDown = 0x100000,     //#define MEM_TOP_DOWN       0x100000     
        WriteWatch = 0x200000,     //#define MEM_WRITE_WATCH    0x200000     
        Physical = 0x400000,     //#define MEM_PHYSICAL       0x400000     
        Rotate = 0x800000,     //#define MEM_ROTATE         0x800000     
        LargePages = 0x20000000,   //#define MEM_LARGE_PAGES  0x20000000     
        FourMbPages = 0x80000000    //#define MEM_4MB_PAGES    0x80000000
    }

    /// <summary>
    /// Memory protection type - taken from #defines in WinNT.h
    /// </summary>
    public enum MemoryProtection : uint
    {
        NoAccess = 0x001,    //#define PAGE_NOACCESS          0x01     
        ReadOnly = 0x002,    //#define PAGE_READONLY          0x02     
        ReadWrite = 0x004,    //#define PAGE_READWRITE         0x04     
        WriteCopy = 0x008,    //#define PAGE_WRITECOPY         0x08     
        Execute = 0x010,    //#define PAGE_EXECUTE           0x10     
        ExecuteRead = 0x020,    //#define PAGE_EXECUTE_READ      0x20     
        ExecuteReadWrite = 0x040,    //#define PAGE_EXECUTE_READWRITE 0x40     
        ExecuteWriteCopy = 0x080,    //#define PAGE_EXECUTE_WRITECOPY 0x80     
        PageGuard = 0x100,    //#define PAGE_GUARD            0x100     
        NoCache = 0x200,    //#define PAGE_NOCACHE          0x200     
        WriteCombine = 0x400,    //#define PAGE_WRITECOMBINE     0x400
    }

    /// <summary>
    /// Process access flags - taken from #defines in WinNT.h
    /// </summary>
    [Flags]
    public enum ProcessAccessFlags : uint
    {
        Terminate = 0x0001,     //#define PROCESS_TERMINATE                  (0x0001)  
        CreateThread = 0x0002,     //#define PROCESS_CREATE_THREAD              (0x0002) 
        SetSessionID = 0x0004,     //#define PROCESS_SET_SESSIONID              (0x0004)
        VMOperation = 0x0008,     //#define PROCESS_VM_OPERATION               (0x0008)  
        VMRead = 0x0010,     //#define PROCESS_VM_READ                    (0x0010) 
        VMWrite = 0x0020,     //#define PROCESS_VM_WRITE                   (0x0020)
        DUPHandle = 0x0040,     //#define PROCESS_DUP_HANDLE                 (0x0040)
        CreateProcess = 0x0080,     //#define PROCESS_CREATE_PROCESS             (0x0080)  
        SetQuota = 0x0100,     //#define PROCESS_SET_QUOTA                  (0x0100)  
        SetInformation = 0x0200,     //#define PROCESS_SET_INFORMATION            (0x0200)
        QueryInformation = 0x0400,     //#define PROCESS_QUERY_INFORMATION          (0x0400)
        SuspendResume = 0x0800,     //#define PROCESS_SUSPEND_RESUME             (0x0800)
        QueryLimitedInformation = 0x1000,     //#define PROCESS_QUERY_LIMITED_INFORMATION  (0x1000)
        AllAccess = Synchronize | StandardRightsRequired | 0xFFFF,
        //#define PROCESS_ALL_ACCESS        (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | 0xFFFF)

        Synchronize = 0x100000,     //#define SYNCHRONIZE                      (0x00100000L)
        StandardRightsRequired = 0x0F0000      //#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)
    }

    /// <summary>
    /// Flags used in LoadLibraryEx to determine behaviour when loading library into process
    /// </summary>
    [Flags]
    public enum LoadLibraryExFlags : uint
    {
        DontResolveDllReferences = 0x00000001,     //#define DONT_RESOLVE_DLL_REFERENCES         0x00000001
        LoadLibraryAsDatafile = 0x00000002,     //#define LOAD_LIBRARY_AS_DATAFILE            0x00000002
        LoadLibraryWithAlteredSearchPath = 0x00000008,     //#define LOAD_WITH_ALTERED_SEARCH_PATH       0x00000008
        LoadIgnoreCodeAuthzLevel = 0x00000010,     //#define LOAD_IGNORE_CODE_AUTHZ_LEVEL        0x00000010
        LoadLibraryAsImageResource = 0x00000020,     //#define LOAD_LIBRARY_AS_IMAGE_RESOURCE      0x00000020
        LoadLibraryAsDatafileExclusive = 0x00000040      //#define LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE  0x00000040
    }

    [Flags]
    public enum ProcessCreationFlags : uint
    {
        None = 0x00000000,

        DebugProcess = 0x00000001,
        DebugOnlyThisProcess = 0x00000002,
        CreateSuspended = 0x00000004,
        DetachedProcess = 0x00000008,
        CreateNewConsole = 0x00000010,

        CreateNewProcessGroup = 0x00000200,
        CreateUnicodeEnvironment = 0x00000400,
        CreateSeparateWowVDM = 0x00000800,
        CreateSharedWowVDM = 0x00001000,

        InheritParentAffinity = 0x00010000,
        CreateProtectedProcess = 0x00040000,
        ExtendedStartupInfoPresent = 0x00080000,

        CreateBreakawayFromJob = 0x01000000,
        CreatePreserveCodeAuthzLevel = 0x02000000,
        CreateDefaultErrorMode = 0x04000000,
        CreateNoWindow = 0x08000000,
    }

    public enum ThreadWaitValue : uint
    {
        Object0 = 0x00000000,
        Abandoned = 0x00000080,
        Timeout = 0x00000102,
        Failed = 0xFFFFFFFF,
        Infinite = 0xFFFFFFFF
    }

    public enum ModuleFilterFlags : uint
    {
        ListModulesDefault = 0x0,
        ListModules32Bit = 0x01,
        ListModules64Bit = 0x02,
        ListModulesAll = 0x03,
    }

    /// <summary>
    /// IMAGE_DOS_HEADER struct taken from pinvoke.net. Represents Dos Header in a module image
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct IMAGE_DOS_HEADER
    {
        public UInt16 e_magic;       // Magic number
        public UInt16 e_cblp;        // Bytes on last page of file
        public UInt16 e_cp;          // Pages in file
        public UInt16 e_crlc;        // Relocations
        public UInt16 e_cparhdr;     // Size of header in paragraphs
        public UInt16 e_minalloc;    // Minimum extra paragraphs needed
        public UInt16 e_maxalloc;    // Maximum extra paragraphs needed
        public UInt16 e_ss;          // Initial (relative) SS value
        public UInt16 e_sp;          // Initial SP value
        public UInt16 e_csum;        // Checksum
        public UInt16 e_ip;          // Initial IP value
        public UInt16 e_cs;          // Initial (relative) CS value
        public UInt16 e_lfarlc;      // File address of relocation table
        public UInt16 e_ovno;        // Overlay number
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 4)]
        public UInt16[] e_res1;        // Reserved words
        public UInt16 e_oemid;       // OEM identifier (for e_oeminfo)
        public UInt16 e_oeminfo;     // OEM information; e_oemid specific
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 10)]
        public UInt16[] e_res2;        // Reserved words
        public Int32 e_lfanew;      // File address of new exe header
    }

    /// <summary>
    /// Represents NT Header in a module image. Definition from pinvoke.net
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct IMAGE_NT_HEADERS
    {
        public UInt32 Signature;
        public IMAGE_FILE_HEADER FileHeader;
        public IMAGE_OPTIONAL_HEADER32 OptionalHeader;
    }

    /// <summary>
    /// Represents COFF header format. Definition from pinvoke.net
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct IMAGE_FILE_HEADER
    {
        public UInt16 Machine;
        public UInt16 NumberOfSections;
        public UInt32 TimeDateStamp;
        public UInt32 PointerToSymbolTable;
        public UInt32 NumberOfSymbols;
        public UInt16 SizeOfOptionalHeader;
        public UInt16 Characteristics;
    }

    /// <summary>
    /// Represents the optional header format. Definition from pinvoke.net
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct IMAGE_OPTIONAL_HEADER32
    {
        //
        // Standard fields.
        //
        public UInt16 Magic;
        public Byte MajorLinkerVersion;
        public Byte MinorLinkerVersion;
        public UInt32 SizeOfCode;
        public UInt32 SizeOfInitializedData;
        public UInt32 SizeOfUninitializedData;
        public UInt32 AddressOfEntryPoint;
        public UInt32 BaseOfCode;
        public UInt32 BaseOfData;
        //
        // NT additional fields.
        //
        public UInt32 ImageBase;
        public UInt32 SectionAlignment;
        public UInt32 FileAlignment;
        public UInt16 MajorOperatingSystemVersion;
        public UInt16 MinorOperatingSystemVersion;
        public UInt16 MajorImageVersion;
        public UInt16 MinorImageVersion;
        public UInt16 MajorSubsystemVersion;
        public UInt16 MinorSubsystemVersion;
        public UInt32 Win32VersionValue;
        public UInt32 SizeOfImage;
        public UInt32 SizeOfHeaders;
        public UInt32 CheckSum;
        public UInt16 Subsystem;
        public UInt16 DllCharacteristics;
        public UInt32 SizeOfStackReserve;
        public UInt32 SizeOfStackCommit;
        public UInt32 SizeOfHeapReserve;
        public UInt32 SizeOfHeapCommit;
        public UInt32 LoaderFlags;
        public UInt32 NumberOfRvaAndSizes;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public IMAGE_DATA_DIRECTORY[] DataDirectory;
    }

    /// <summary>
    /// Represents the Data Directory. Defintion from pinvoke.net
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct IMAGE_DATA_DIRECTORY
    {
        public UInt32 VirtualAddress;
        public UInt32 Size;
    }

    /// <summary>
    /// Represents the Export Directory. Definition from pinvoke.net
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct IMAGE_EXPORT_DIRECTORY
    {
        public UInt32 Characteristics;
        public UInt32 TimeDateStamp;
        public UInt16 MajorVersion;
        public UInt16 MinorVersion;
        public UInt32 Name;
        public UInt32 Base;
        public UInt32 NumberOfFunctions;
        public UInt32 NumberOfNames;
        public UInt32 AddressOfFunctions;     // RVA from base of image
        public UInt32 AddressOfNames;     // RVA from base of image
        public UInt32 AddressOfNameOrdinals;  // RVA from base of image
    }

    /// <summary>
    /// Startup Info struct used with <see cref="Imports.CreateProcess"/>. Definition from pinvoke.net.
    /// </summary>
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    public struct STARTUPINFO
    {
        public Int32 cb;
        public string lpReserved;
        public string lpDesktop;
        public string lpTitle;
        public Int32 dwX;
        public Int32 dwY;
        public Int32 dwXSize;
        public Int32 dwYSize;
        public Int32 dwXCountChars;
        public Int32 dwYCountChars;
        public Int32 dwFillAttribute;
        public Int32 dwFlags;
        public Int16 wShowWindow;
        public Int16 cbReserved2;
        public IntPtr lpReserved2;
        public IntPtr hStdInput;
        public IntPtr hStdOutput;
        public IntPtr hStdError;
    }

    /// <summary>
    /// Process Information struct, used with <see cref="Imports.CreateProcess"/>. Definition from pinvoke.net.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    public struct PROCESS_INFORMATION
    {
        public IntPtr hProcess;
        public IntPtr hThread;
        public int dwProcessId;
        public int dwThreadId;
    }

    public struct MODULEINFO
    {
        public IntPtr lpBaseOfDll;
        public uint SizeOfImage;
        public IntPtr EntryPoint;
    }

    [StructLayout(LayoutKind.Sequential, Pack = 0)]
    public struct IO_STATUS_BLOCK
    {
        public uint status;
        public IntPtr information;
    }

    [StructLayout(LayoutKind.Sequential, Pack = 0)]
    public struct OBJECT_ATTRIBUTES
    {
        public Int32 Length;
        public IntPtr RootDirectory;
        public IntPtr ObjectName;
        public uint Attributes;
        public IntPtr SecurityDescriptor;
        public IntPtr SecurityQualityOfService;

    }

    [StructLayout(LayoutKind.Sequential, Pack = 0)]
    public struct UNICODE_STRING
    {
        public ushort Length;
        public ushort MaximumLength;
        public IntPtr Buffer;

    }

    public enum FILE_INFORMATION_CLASS
    {
        FileDirectoryInformation = 1,     // 1
        FileFullDirectoryInformation,     // 2
        FileBothDirectoryInformation,     // 3
        FileBasicInformation,         // 4
        FileStandardInformation,      // 5
        FileInternalInformation,      // 6
        FileEaInformation,        // 7
        FileAccessInformation,        // 8
        FileNameInformation,          // 9
        FileRenameInformation,        // 10
        FileLinkInformation,          // 11
        FileNamesInformation,         // 12
        FileDispositionInformation,       // 13
        FilePositionInformation,      // 14
        FileFullEaInformation,        // 15
        FileModeInformation = 16,     // 16
        FileAlignmentInformation,     // 17
        FileAllInformation,           // 18
        FileAllocationInformation,    // 19
        FileEndOfFileInformation,     // 20
        FileAlternateNameInformation,     // 21
        FileStreamInformation,        // 22
        FilePipeInformation,          // 23
        FilePipeLocalInformation,     // 24
        FilePipeRemoteInformation,    // 25
        FileMailslotQueryInformation,     // 26
        FileMailslotSetInformation,       // 27
        FileCompressionInformation,       // 28
        FileObjectIdInformation,      // 29
        FileCompletionInformation,    // 30
        FileMoveClusterInformation,       // 31
        FileQuotaInformation,         // 32
        FileReparsePointInformation,      // 33
        FileNetworkOpenInformation,       // 34
        FileAttributeTagInformation,      // 35
        FileTrackingInformation,      // 36
        FileIdBothDirectoryInformation,   // 37
        FileIdFullDirectoryInformation,   // 38
        FileValidDataLengthInformation,   // 39
        FileShortNameInformation,     // 40
        FileHardLinkInformation = 46    // 46    
    }

    /// <summary>
    /// Static class containing all Win32 Import functions
    /// </summary>
    public static class Imports
    {

        #region Process

        /// <summary>
        /// Open process and retrieve handle for manipulation
        /// </summary>
        /// <param name="dwDesiredAccess"><see cref="ProcessAccessFlags"/> for external process.</param>
        /// <param name="bInheritHandle">Indicate whether to inherit a handle.</param>
        /// <param name="dwProcessId">Unique process ID of process to open</param>
        /// <returns>Returns a handle to opened process if successful or <see cref="IntPtr.Zero"/> if unsuccessful.
        /// Use <see cref="Marshal.GetLastWin32Error" /> to get Win32 Error on failure</returns>
        [DllImport("kernel32.dll", EntryPoint = "OpenProcess", SetLastError = true)]
        public static extern IntPtr OpenProcess(
            ProcessAccessFlags dwDesiredAccess,
            [MarshalAs(UnmanagedType.Bool)] 
            bool bInheritHandle,
            int dwProcessId);

        /// <summary>
        /// Creates a new process and its primary thread. The new process runs in the security context of the calling process.
        /// </summary>
        /// <param name="lpApplicationName">The name of the module to be executed. The string can specify the full path and file name of hte module to execute
        /// or it can specify a partial name.</param>
        /// <param name="lpCommandLine">The command line to be executed.</param>
        /// <param name="lpProcessAttributes">A pointer to a SECURITY_ATTRIBUTES structure that determines whether the returned handle to the new process object can be inherited by child processes. If lpProcessAttributes is <see cref="IntPtr.Zero"/>, the handle cannot be inherited.</param>
        /// <param name="lpThreadAttributes">A pointer to a SECURITY_ATTRIBUTES structure that determines whether the returned handle to the new thread object can be inherited by child processes. If lpThreadAttributes is <see cref="IntPtr.Zero"/>, the handle cannot be inherited.</param>
        /// <param name="bInheritHandles">If this parameter is true, each inheritable handle in the calling process is inherited by the new process. If the parameter is FALSE, the handles are not inherited. Note that inherited handles have the same value and access rights as the original handles.</param>
        /// <param name="dwCreationFlags">The flags that control the priority class and the creation of the process. See <see cref="ProcessCreationFlags"/></param>
        /// <param name="lpEnvironment">A pointer to the environment block for the new process. If this parameter is <see cref="IntPtr.Zero"/>, the new process uses the environment of the calling process.</param>
        /// <param name="lpCurrentDirectory">The full path to the current directory for the process. The string can also specify a UNC path.</param>
        /// <param name="lpStartupInfo">A pointer to a <see cref="STARTUPINFO"/> structure.</param>
        /// <param name="lpProcessInformation">A pointer to a <see cref="PROCESS_INFORMATION"/> structure that receives identification information about the new process.</param>
        /// <returns>If the function succeeds, the return value is true. If the function fails, the return value is false. Call <see cref="Marshal.GetLastWin32Error"/> to get the Win32 Error.</returns>
        [DllImport("kernel32.dll", EntryPoint = "CreateProcessW", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool CreateProcess(
            [MarshalAs(UnmanagedType.LPWStr)]
            string lpApplicationName,
            string lpCommandLine,
            IntPtr lpProcessAttributes,
            IntPtr lpThreadAttributes,
            bool bInheritHandles,
            ProcessCreationFlags dwCreationFlags,
            IntPtr lpEnvironment,
            string lpCurrentDirectory,
            ref STARTUPINFO lpStartupInfo,
            out PROCESS_INFORMATION lpProcessInformation);

        [DllImport("kernel32.dll", SetLastError = true, CallingConvention = CallingConvention.Winapi)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool IsWow64Process([In] IntPtr process, [Out] out bool wow64Process);

        #endregion

        #region Module

        /// <summary>
        /// Loads the specified module into the address space of the calling process. The specified module may cause other modules to be loaded.
        /// </summary>
        /// <param name="lpFileName">
        /// <para>The name of the module. This can be either a library module (.dll) or an executable module (.exe).</para>
        /// <para>If the string specifies a full path, the function searches only that path for the module. 
        /// Relative paths or files without a path will be searched for using standard strategies.</para>
        /// </param>
        /// <returns>If the function succeeds, a handle to the module is returned. 
        /// Otherwise, <see cref="IntPtr.Zero"/> is returned. Call <see cref="Marshal.GetLastWin32Error"/> on failure to get Win32 error.</returns>
        [DllImport("kernel32.dll", EntryPoint = "LoadLibraryW", SetLastError = true)]
        public static extern IntPtr LoadLibrary(string lpFileName);

        /// <summary>
        /// Loads the specified module into the address space of the calling process. The specified module may cause other modules to be loaded.
        /// </summary>
        /// <param name="lpFileName"><para>The name of the module. This can be either a library module (.dll) or an executable module (.exe).</para>
        /// <para>If the string specifies a full path, the function searches only that path for the module. 
        /// Relative paths or files without a path will be searched for using standard strategies.</para></param>
        /// <param name="hFile">This parameter is reserved for future use. It must be NULL (<see cref="IntPtr.Zero"/>)</param>
        /// <param name="dwFlags">The action to be taken when loading the module. If no flags are specified, the behaviour is identical to <see cref="LoadLibrary"/>.
        /// The parameter can be one of the values defined in <see cref="LoadLibraryExFlags"/></param>
        /// <returns></returns>
        [DllImport("kernel32.dll", EntryPoint = "LoadLibraryExW", SetLastError = true)]
        public static extern IntPtr LoadLibraryEx(
            [MarshalAs(UnmanagedType.LPWStr)]
            string lpFileName,
            IntPtr hFile,
            LoadLibraryExFlags dwFlags);

        /// <summary>
        /// Frees the loaded Dll module.
        /// </summary>
        /// <param name="hModule">Handle to the loaded library to free</param>
        /// <returns>True if the function succeeds, otherwise false. Call <see cref="Marshal.GetLastWin32Error"/> on failure to get Win32 error.</returns>
        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool FreeLibrary(IntPtr hModule);

        /// <summary>
        /// Retrieve a module handle for the specified module. The module must have been loaded by the calling process.
        /// </summary>
        /// <param name="lpModuleName">The name of the loaded module.</param>
        /// <returns>If the function succeeds, a handle to the module is returned. Otherwise, <see cref="IntPtr.Zero"/> is returned. Call <see cref="Marshal.GetLastWin32Error"/> on failure to get last Win32 error</returns>
        [DllImport("kernel32.dll", EntryPoint = "GetModuleHandleW", SetLastError = true)]
        public static extern IntPtr GetModuleHandle(
            [MarshalAs(UnmanagedType.LPWStr)] string lpModuleName);

        /// <summary>
        /// Retrieves the address of an exported function from the specified Dll.
        /// </summary>
        /// <param name="hModule">Handle to the Dll module that contains the exported function</param>
        /// <param name="procName">The function name.</param>
        /// <returns></returns>
        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

        [DllImport("psapi.dll")]
        public static extern bool EnumProcessModulesEx(IntPtr hProcess, [MarshalAs(UnmanagedType.LPArray, ArraySubType = UnmanagedType.U4)] [In][Out] IntPtr[] lphModule, int cb, [MarshalAs(UnmanagedType.U4)] out int lpcbNeeded, uint dwFilterFlag);

        [DllImport("psapi.dll")]
        public static extern uint GetModuleFileNameEx(IntPtr hProcess, IntPtr hModule, [Out] StringBuilder lpBaseName, [In] [MarshalAs(UnmanagedType.U4)] uint nSize);

        [DllImport("psapi.dll", SetLastError = true)]
        public static extern bool GetModuleInformation(IntPtr hProcess, IntPtr hModule, out MODULEINFO lpmodinfo, uint cb);


        [DllImport("psapi.dll", SetLastError = true)]
        public static extern uint GetMappedFileName(IntPtr m_hProcess, IntPtr lpv, StringBuilder
            lpFilename, uint nSize);


        #endregion

        #region Thread

        /// <summary>
        /// Create a thread that runs in the virtual address space of another process
        /// </summary>
        /// <param name="hProcess">A handle to the process in which the thread is to be created</param>
        /// <param name="lpThreadAttributes">A pointer to a SECURITY_ATTRIBUTES structure that specifies a security descriptor for the new thread and determines whether child processes can inherit the returned handle.</param>
        /// <param name="dwStackSize">The initial size of the stack, in bytes. The system rounds this value to the nearest page. If this parameter is 0 (zero), the new thread uses the default size for the executable.</param>
        /// <param name="lpStartAddress">A pointer to the application-defined function of type LPTHREAD_START_ROUTINE to be executed by the thread and represents the starting address of the thread in the remote process. The function must exist in the remote process.</param>
        /// <param name="lpParameter">A pointer to a variable to be passed to the thread function</param>
        /// <param name="dwCreationFlags">The flags that control the creation of the thread</param>
        /// <param name="lpThreadId">A pointer to a variable that receives the thread identifier. If this parameter is <see cref="IntPtr.Zero"/>, the thread identifier is not returned.</param>
        /// <returns>If the function succeeds, the return value is a handle to the new thread. If the function fails, the return value is <see cref="IntPtr.Zero"/>. Call <see cref="Marshal.GetLastWin32Error"/> to get Win32 Error.</returns>
        [DllImport("kernel32.dll", EntryPoint = "CreateRemoteThread", SetLastError = true)]
        public static extern IntPtr CreateRemoteThread(
            IntPtr hProcess,
            IntPtr lpThreadAttributes,
            uint dwStackSize,
            IntPtr lpStartAddress,
            IntPtr lpParameter,
            uint dwCreationFlags,
            [Out] IntPtr lpThreadId);

        /// <summary>
        /// Waits until the specified object is in the signaled state or the time-out interval elapses.
        /// </summary>
        /// <param name="hObject">A handle to the object. For a list of the object types whose handles can be specified, see the following Remarks section.</param>
        /// <param name="dwMilliseconds">The time-out interval, in milliseconds. The function returns if the interval elapses, even if the object's state is nonsignaled. If dwMilliseconds is zero, the function tests the object's state and returns immediately. If dwMilliseconds is INFINITE, the function's time-out interval never elapses.</param>
        /// <returns>If the function succeeds, the return value indicates the event that caused the function to return. If the function fails, the return value is WAIT_FAILED ((DWORD)0xFFFFFFFF).</returns>
        [DllImport("kernel32", EntryPoint = "WaitForSingleObject")]
        public static extern uint WaitForSingleObject(IntPtr hObject, uint dwMilliseconds);

        /// <summary>
        /// Retrieves the termination status of the specified thread.
        /// </summary>
        /// <param name="hThread">Handle to the thread</param>
        /// <param name="lpExitCode">A pointer to a variable to receive the thread termination status. If this works properly, this should be the return value from the thread function of <see cref="CreateRemoteThread"/></param>
        /// <returns></returns>
        [DllImport("kernel32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetExitCodeThread(IntPtr hThread, out IntPtr lpExitCode);

        /// <summary>
        /// Retrieves the termination status of the specified thread.
        /// </summary>
        /// <param name="hThread">Handle to the thread</param>
        /// <param name="lpExitCode">A pointer to a variable to receive the thread termination status. If this works properly, this should be the return value from the thread function of <see cref="CreateRemoteThread"/></param>
        /// <returns></returns>
        [DllImport("kernel32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetExitCodeThread(IntPtr hThread, out uint lpExitCode);


        #endregion

        #region Handle

        /// <summary>
        /// Close an open handle
        /// </summary>
        /// <param name="hObject">Object handle to close</param>
        /// <returns>True if success, false if failure. Use <see cref="Marshal.GetLastWin32Error"/> on failure to get Win32 error.</returns>
        [DllImport("kernel32.dll", EntryPoint = "CloseHandle")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool CloseHandle(IntPtr hObject);


        #endregion

        #region Memory

        /// <summary>
        /// Reserves or commits a region of memory within the virtual address space of a specified process.
        /// The function initializes the memory it allocates to zero, unless <see cref="AllocationType.Reset"/> is used.
        /// </summary>
        /// <param name="hProcess">The handle to a process. The function allocated memory within the virtual address space of this process.
        /// The process must have the <see cref="ProcessAccessFlags.VMOperation"/> access right.</param>
        /// <param name="lpAddress">Optional desired address to begin allocation from. Use <see cref="IntPtr.Zero"/> to let the function determine the address</param>
        /// <param name="dwSize">The size of the region of memory to allocate, in bytes</param>
        /// <param name="flAllocationType">
        /// <see cref="AllocationType"/> type of allocation. Must contain one of <see cref="AllocationType.Commit"/>, <see cref="AllocationType.Reserve"/> or <see cref="AllocationType.Reset"/>.
        /// Can also specify <see cref="AllocationType.LargePages"/>, <see cref="AllocationType.Physical"/>, <see cref="AllocationType.TopDown"/>.
        /// </param>
        /// <param name="flProtect">One of <see cref="MemoryProtection"/> constants.</param>
        /// <returns>If the function succeeds, the return value is the base address of the allocated region of pages.
        /// If the function fails, the return value is <see cref="IntPtr.Zero"/>. Call <see cref="Marshal.GetLastWin32Error"/> to get Win32 error.</returns>
        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        public static extern IntPtr VirtualAllocEx(
            IntPtr hProcess,
            IntPtr lpAddress,
            uint dwSize,
            AllocationType flAllocationType,
            MemoryProtection flProtect);

        /// <summary>
        /// Releases, decommits, or releases and decommits a region of memory within the virtual address space of a specified process
        /// </summary>
        /// <param name="hProcess">A handle to a process. The function frees memory within the virtual address space of this process.
        /// The handle must have the <see cref="ProcessAccessFlags.VMOperation"/> access right</param>
        /// <param name="lpAddress">A pointer to the starting address of the region of memory to be freed.
        /// If the <paramref name="dwFreeType"/> parameter is <see cref="AllocationType.Release"/>, this address must be the base address
        /// returned by <see cref="VirtualAllocEx"/>.</param>
        /// <param name="dwSize">The size of the region of memory to free, in bytes.
        /// If the <paramref name="dwFreeType"/> parameter is <see cref="AllocationType.Release"/>, this parameter must be 0. The function
        /// frees the entire region that is reserved in the initial allocation call to <see cref="VirtualAllocEx"/></param>
        /// <param name="dwFreeType">The type of free operation. This parameter can be one of the following values: 
        /// <see cref="AllocationType.Decommit"/> or <see cref="AllocationType.Release"/></param>
        /// <returns>If the function is successful, it returns true. If the function fails, it returns false. Call <see cref="Marshal.GetLastWin32Error"/> to get Win32 error.</returns>
        [DllImport("kernel32.dll", SetLastError = true, ExactSpelling = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool VirtualFreeEx(
            IntPtr hProcess,
            IntPtr lpAddress,
            uint dwSize,
            AllocationType dwFreeType);

        /// <summary>
        /// Reads data from an area of memory in the specified process.
        /// </summary>
        /// <param name="hProcess">Handle to the process from which the memory is being read. 
        /// The handle must have <see cref="ProcessAccessFlags.VMRead"/> access to the process.</param>
        /// <param name="lpBaseAddress">A pointer to the base address in the specified process to begin reading from</param>
        /// <param name="lpBuffer">A pointer to a buffer that receives the contents from the address space of the process</param>
        /// <param name="dwSize">The number of bytes to be read</param>
        /// <param name="lpNumberOfBytesRead">The number of bytes read into the specified buffer</param>
        /// <returns>If the function succeeds, it returns true. Otherwise, false is returned and calling <see cref="Marshal.GetLastWin32Error"/> will retrieve the error.</returns>
        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool ReadProcessMemory(
            IntPtr hProcess,
            IntPtr lpBaseAddress,
            out byte[] lpBuffer,
            uint dwSize,
            out int lpNumberOfBytesRead);

        /// <summary>
        /// Reads data from an area of memory in the specified process.
        /// </summary>
        /// <param name="hProcess">Handle to the process from which the memory is being read. 
        /// The handle must have <see cref="ProcessAccessFlags.VMRead"/> access to the process.</param>
        /// <param name="lpBaseAddress">A pointer to the base address in the specified process to begin reading from</param>
        /// <param name="lpBuffer">A pointer to a buffer that receives the contents from the address space of the process</param>
        /// <param name="dwSize">The number of bytes to be read</param>
        /// <param name="lpNumberOfBytesRead">The number of bytes read into the specified buffer</param>
        /// <returns>If the function succeeds, it returns true. Otherwise, false is returned and calling <see cref="Marshal.GetLastWin32Error"/> will retrieve the error.</returns>
        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool ReadProcessMemory(
            IntPtr hProcess,
            IntPtr lpBaseAddress,
            out IntPtr lpBuffer,
            uint dwSize,
            out int lpNumberOfBytesRead);

        /// <summary>
        /// Writes data to an area of memory in a specified process.
        /// </summary>
        /// <param name="hProcess">Handle to the process to write memory to.
        /// The handle must have <see cref="ProcessAccessFlags.VMWrite"/> and <see cref="ProcessAccessFlags.VMOperation"/> access to the process</param>
        /// <param name="lpBaseAddress">A pointer to the base address to write to in the specified process</param>
        /// <param name="lpBuffer">A pointer to a buffer that contains the data to be written</param>
        /// <param name="nSize">The number of bytes to write</param>
        /// <param name="lpNumberOfBytesWritten">The number of bytes written.</param>
        /// <returns>If the function succeeds, it returns true. Otherwise false is returned and calling <see cref="Marshal.GetLastWin32Error"/> will retrieve the error.</returns>
        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool WriteProcessMemory(
            IntPtr hProcess,
            IntPtr lpBaseAddress,
            byte[] lpBuffer,
            uint nSize,
            out int lpNumberOfBytesWritten);

        /// <summary>
        /// Writes data to an area of memory in a specified process.
        /// </summary>
        /// <param name="hProcess">Handle to the process to write memory to.
        /// The handle must have <see cref="ProcessAccessFlags.VMWrite"/> and <see cref="ProcessAccessFlags.VMOperation"/> access to the process</param>
        /// <param name="lpBaseAddress">A pointer to the base address to write to in the specified process</param>
        /// <param name="lpBuffer">A pointer to a buffer that contains the data to be written</param>
        /// <param name="nSize">The number of bytes to write</param>
        /// <param name="lpNumberOfBytesWritten">The number of bytes written.</param>
        /// <returns>If the function succeeds, it returns true. Otherwise false is returned and calling <see cref="Marshal.GetLastWin32Error"/> will retrieve the error.</returns>
        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool WriteProcessMemory(
            IntPtr hProcess,
            IntPtr lpBaseAddress,
            IntPtr lpBuffer,
            uint nSize,
            out int lpNumberOfBytesWritten);

        #endregion

        #region Window
        #endregion

        [DllImport("ntdll.dll", ExactSpelling = true, SetLastError = true)]
        public static extern int NtCreateFile(
            out Microsoft.Win32.SafeHandles.SafeFileHandle handle,
            System.IO.FileAccess access,
            ref OBJECT_ATTRIBUTES objectAttributes,
            ref IO_STATUS_BLOCK ioStatus,
            ref long allocSize,
            uint fileAttributes,
            System.IO.FileShare share,
            uint createDisposition,
            uint createOptions,
            IntPtr eaBuffer,
            uint eaLength);

        [DllImport("ntdll.dll", SetLastError = true)]
        public static extern IntPtr NtQueryInformationFile(IntPtr fileHandle, ref IO_STATUS_BLOCK IoStatusBlock, IntPtr pInfoBlock, uint length, FILE_INFORMATION_CLASS fileInformation);

        [DllImport("kernel32.dll")]
        // static extern uint GetLogicalDriveStrings(uint nBufferLength, 
        //    [Out] StringBuilder lpBuffer); --- Don't do this!

        // if we were to use the StringBuilder, only the first string would be returned
        // so, since arrays are reference types, we can pass an array of chars
        // just initialize it prior to call the function as
        // char[] lpBuffer = new char[nBufferLength];
        public static extern int GetLogicalDriveStrings(uint nBufferLength, [Out] char[] lpBuffer);

        [DllImport("kernel32.dll", SetLastError = true)]
        public static extern int QueryDosDevice(string lpDeviceName, IntPtr lpTargetPath, uint ucchMax);
    }
}
