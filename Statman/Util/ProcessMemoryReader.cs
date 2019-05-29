using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace Statman.Util
{
    public class ProcessMemoryReader
    {
        [DllImport("kernel32.dll")]
        private static extern IntPtr OpenProcess(uint dwDesiredAccess, int bInheritHandle, uint dwProcessId);

        [DllImport("kernel32.dll")]
        private static extern int CloseHandle(IntPtr hObject);

        [DllImport("kernel32.dll")]
        private static extern int ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, [In, Out] byte[] buffer, long size, out IntPtr lpNumberOfBytesRead);

        public Process Process { get; private set; }

        private IntPtr m_Process = IntPtr.Zero;

        public ProcessMemoryReader(Process p_Process)
        {
            Process = p_Process;
        }

        public bool OpenProcess()
        {
            m_Process = OpenProcess(0x0010 /* PROCESS_VM_READ */, 1, (uint) Process.Id);
            return m_Process != IntPtr.Zero;
        }

        public void CloseHandle()
        {
            CloseHandle(m_Process);
        }

        public byte[] Read(long p_MemoryAddress, long p_BytesToRead)
        {
            var s_Data = Read(new IntPtr(p_MemoryAddress), p_BytesToRead, out var s_BytesRead);
            return s_BytesRead != p_BytesToRead ? null : s_Data;
        }

        public byte[] Read(IntPtr p_MemoryAddress, long p_BytesToRead)
        {
            var s_Data = Read(p_MemoryAddress, p_BytesToRead, out var s_BytesRead);
            return s_BytesRead != p_BytesToRead ? null : s_Data;
        }

        public byte[] Read(long p_MemoryAddress, long p_BytesToRead, out long p_BytesRead)
        {
            return Read(new IntPtr(p_MemoryAddress), p_BytesToRead, out p_BytesRead);
        }

        public byte[] Read(IntPtr p_MemoryAddress, long p_BytesToRead, out long p_BytesRead)
        {
            p_BytesRead = 0;
            var s_Buffer = new byte[p_BytesToRead];

            if (ReadProcessMemory(m_Process, p_MemoryAddress, s_Buffer, p_BytesToRead, out var s_BytesRead) == 0)
                return null;

            p_BytesRead = s_BytesRead.ToInt64();

            return s_Buffer;
        }
    }
}
