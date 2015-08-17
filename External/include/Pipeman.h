#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <string>
#include <queue>
#include <atomic>
#include <thread>

class Pipeman
{
public:
	Pipeman(const std::string& p_PipeName);
	~Pipeman();

public:
	void SendData(const std::string& p_Data);
	void Disconnect();

private:
	void Update();

private:
	std::thread m_Thread;
	std::string m_PipeName;
	CRITICAL_SECTION m_CriticalSection;
	std::queue<std::string> m_QueuedData;
	std::atomic<bool> m_Running;
};