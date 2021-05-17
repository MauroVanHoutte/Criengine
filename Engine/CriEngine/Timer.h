#pragma once
#include <chrono>

class Timer
{
public:
	static Timer* GetInstance();
	void Update();
	float GetElapsed();
	float GetStepTime();
	float GetTotalTime();
	void SetUpdateTime(float seconds);
	float GetUpdateTime();
	void SetRenderTime(float seconds);
	float GetRenderTime();

	void Delete();

private:
	Timer();
	Timer(Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(Timer&) = delete;
	Timer& operator=(Timer&&) = delete;

	static Timer* m_pInstance;

	std::chrono::steady_clock::time_point m_LastTime;
	float m_TotalTime = 0.0f;
	float m_RenderTime = 0.0f;
	float m_UpdateTime = 0.0f;
	float m_FrameTime = 0.0f;
	const float m_StepTime = 0.16f; //16 for 60 fps, 33 for 30 fps
};