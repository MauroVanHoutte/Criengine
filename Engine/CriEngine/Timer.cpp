#include "Timer.h"

Timer* Timer::m_pInstance = nullptr;

Timer::Timer()
{
	m_LastTime = std::chrono::high_resolution_clock::now();
}

Timer* Timer::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new Timer();
	
	return m_pInstance;
}

void Timer::Update()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	m_pInstance->m_FrameTime = std::chrono::duration<float>(currentTime - m_pInstance->m_LastTime).count();
	m_pInstance->m_TotalTime += m_pInstance->m_FrameTime;
	m_pInstance->m_LastTime = currentTime;
}

float Timer::GetElapsed()
{
	return m_pInstance->m_FrameTime;
}

float Timer::GetStepTime()
{
	return m_pInstance->m_StepTime;
}

float Timer::GetTotalTime()
{
	return m_pInstance->m_TotalTime;
}

void Timer::SetUpdateTime(float seconds)
{
	m_UpdateTime = seconds;
}

float Timer::GetUpdateTime()
{
	return m_UpdateTime;
}

void Timer::SetRenderTime(float seconds)
{
	m_RenderTime = seconds;
}

float Timer::GetRenderTime()
{
	return m_RenderTime;
}

void Timer::Delete()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
	}
}
