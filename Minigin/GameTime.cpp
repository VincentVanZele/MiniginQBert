#include "MiniginPCH.h"
#include "GameTime.h"

void dae::GameTime::Update(float deltaTime)
{
	m_DeltaTime = deltaTime;
	m_ElapsedTime += m_DeltaTime;
}

float dae::GameTime::GetDeltaTime() const
{
	return m_DeltaTime;
}

float dae::GameTime::GetFPS() const
{
	return (int)1.0f / m_DeltaTime;
}

int dae::GameTime::GetMsPerFrame() const
{
	return msPerFrame;
}