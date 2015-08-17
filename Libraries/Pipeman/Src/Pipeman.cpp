#include <Pipeman.h>


Pipeman::Pipeman(const std::string& p_PipeName) : 
	m_Running(true),
	m_PipeName(p_PipeName),
	m_Thread(&Pipeman::Update, this)
{
	InitializeCriticalSection(&m_CriticalSection);
}

Pipeman::~Pipeman()
{
	Disconnect();
	DeleteCriticalSection(&m_CriticalSection);
}

void Pipeman::Disconnect()
{
	m_Running = false;
}

void Pipeman::SendData(const std::string& p_Data)
{
	EnterCriticalSection(&m_CriticalSection);

	m_QueuedData.push(p_Data);

	LeaveCriticalSection(&m_CriticalSection);
}

void Pipeman::Update()
{
	while (m_Running)
	{
		Sleep(5);

		// We should be connected by now; send data.
		EnterCriticalSection(&m_CriticalSection);

		if (!m_QueuedData.empty())
		{
			HANDLE s_Pipe = CreateFileA(TEXT(m_PipeName.c_str()),
				GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);

			if (s_Pipe == NULL || s_Pipe == INVALID_HANDLE_VALUE || GetLastError() == ERROR_PIPE_BUSY)
			{
				SetLastError(0);
				LeaveCriticalSection(&m_CriticalSection);
				continue;
			}

			std::string s_Data;

			// Write data length.
			uint32_t s_DataLength = m_QueuedData.front().size();
			s_Data.append((char*) &s_DataLength, 4);

			// Write data.
			s_Data.append(m_QueuedData.front().data(), s_DataLength);

			// And then write to the pipe.
			DWORD s_Written;
			WriteFile(s_Pipe, s_Data.data(), s_Data.size(), &s_Written, NULL);

			m_QueuedData.pop();

			CloseHandle(s_Pipe);
		}

		LeaveCriticalSection(&m_CriticalSection);
	}
}