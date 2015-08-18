#include <Pipeman.h>


Pipeman::Pipeman(const std::string& p_PipeName) : 
	m_Running(true),
	m_PipeName(p_PipeName),
	m_Pipe(NULL),
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

void Pipeman::SendPipeMessage(const std::string& p_Module, const std::string& p_Type, const std::string& p_Content)
{
	EnterCriticalSection(&m_CriticalSection);

	std::string s_Module(p_Module);
	std::string s_Type(p_Type);

	if (s_Module.size() == 0)
		s_Module = "__";
	else if (s_Module.size() == 1)
		s_Module = s_Module + "_";
	else
		s_Module = s_Module.substr(0, 2);

	if (s_Type.size() == 0)
		s_Type = "__";
	else if (s_Type.size() == 1)
		s_Type = s_Type + "_";
	else
		s_Type = s_Type.substr(0, 2);

	std::string s_Data = s_Module + s_Type;
	s_Data.append(p_Content.data(), p_Content.size());

	m_QueuedData.push(s_Data);

	LeaveCriticalSection(&m_CriticalSection);
}

void Pipeman::Update()
{
	while (m_Running)
	{
		Sleep(5);

		if (m_Pipe == NULL)
		{
			// Connect to the handshake pipe.
			m_Pipe = CreateFileA(m_PipeName.c_str(),
				GENERIC_WRITE | GENERIC_READ,
				0,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);

			if (m_Pipe == NULL || m_Pipe == INVALID_HANDLE_VALUE || GetLastError() == ERROR_PIPE_BUSY)
			{
				SetLastError(0);
				m_Pipe = NULL;
				continue;
			}

			SetLastError(0);

			char s_HandshakeLengthBuffer[4];
			DWORD s_HandshakeLengthBufferLength;

			// Read the handshake length.
			if (!ReadFile(m_Pipe, s_HandshakeLengthBuffer, 4, &s_HandshakeLengthBufferLength, NULL) || s_HandshakeLengthBufferLength != 4)
			{
				m_Pipe = NULL;
				continue;
			}

			uint32_t s_HandshakeLength = *(uint32_t*) &s_HandshakeLengthBuffer[0];

			char* s_HandshakeBuffer = new char[s_HandshakeLength];
			DWORD s_HandshakeBufferLength;

			// Read the handshake length.
			if (!ReadFile(m_Pipe, s_HandshakeBuffer, s_HandshakeLength, &s_HandshakeBufferLength, NULL) || s_HandshakeBufferLength != s_HandshakeLength)
			{
				delete [] s_HandshakeBuffer;
				m_Pipe = NULL;
				continue;
			}

			// Close the handshake pipe.
			CloseHandle(m_Pipe);
			m_Pipe = NULL;

			// Parse the handshake.
			std::string s_Handshake(s_HandshakeBuffer, s_HandshakeBufferLength);

			delete [] s_HandshakeBuffer;

			std::string s_Module = s_Handshake.substr(0, 2);
			std::string s_Type = s_Handshake.substr(2, 2);
			std::string s_Content = s_Handshake.substr(4, s_HandshakeLength - 4);

			if (s_Module != "SM" || s_Type != "HS")
				continue;

			std::string s_MainPipe = "\\\\.\\pipe\\" + s_Content;

			// Connect to the main pipe.
			m_Pipe = CreateFileA(s_MainPipe.c_str(),
				GENERIC_WRITE | GENERIC_READ,
				0,
				NULL,
				OPEN_EXISTING,
				0,
				NULL);

			while (GetLastError() == ERROR_FILE_NOT_FOUND)
			{
				Sleep(33);

				m_Pipe = CreateFileA(s_MainPipe.c_str(),
					GENERIC_WRITE | GENERIC_READ,
					0,
					NULL,
					OPEN_EXISTING,
					0,
					NULL);
			}

			if (m_Pipe == NULL || m_Pipe == INVALID_HANDLE_VALUE || GetLastError() == ERROR_PIPE_BUSY)
			{
				SetLastError(0);
				m_Pipe = NULL;
				continue;
			}
		}

		if (m_Pipe == NULL)
			continue;

		// We should be connected by now; send data.
		EnterCriticalSection(&m_CriticalSection);

		if (!m_QueuedData.empty())
		{
			std::string s_Data;

			// Write data length.
			uint32_t s_DataLength = m_QueuedData.front().size();
			s_Data.append((char*) &s_DataLength, 4);

			// Write data.
			s_Data.append(m_QueuedData.front().data(), s_DataLength);

			// And then write to the pipe.
			DWORD s_Written;
			if (!WriteFile(m_Pipe, s_Data.data(), s_Data.size(), &s_Written, NULL))
			{
				m_Pipe = NULL;
				LeaveCriticalSection(&m_CriticalSection);
				continue;
			}

			m_QueuedData.pop();
		}

		LeaveCriticalSection(&m_CriticalSection);
	}
}