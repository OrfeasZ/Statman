#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <string>
#include <queue>
#include <atomic>
#include <thread>
#include <functional>

class Pipeman
{
public:
	Pipeman(const std::string& p_PipeName, const std::string& p_Module);
	~Pipeman();

public:
	typedef std::function<void(const std::string&, const std::string&)> MessageCallback_t;

	void SetMessageCallback(MessageCallback_t p_Callback);
	void SetConnectedCallback(std::function<void()> p_Callback);
	void SetDisconnectedCallback(std::function<void()> p_Callback);
	void SendPipeMessage(const std::string& p_Type, const std::string& p_Content);
	void Disconnect();

private:
	void Update();

private:
	HANDLE m_Pipe;
	std::thread m_Thread;
	std::string m_Module;
	std::string m_PipeName;
	CRITICAL_SECTION m_CriticalSection;
	std::queue<std::string> m_QueuedData;
	std::atomic<bool> m_Running;
	uint32_t m_PendingMessageLength;
	MessageCallback_t m_MessageCallback;
	std::function<void()> m_ConnectedCallback;
	std::function<void()> m_DisconnectedCallback;
};