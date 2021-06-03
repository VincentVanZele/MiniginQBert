#include "MiniginPCH.h"
#include "Listener.h"

#include "Event.h"

int dae::Listener::m_idCounter{};

dae::Listener::Listener()
	: m_NotifyFunction{}
{
	m_currId = m_idCounter;		
	m_idCounter++;
}

void dae::Listener::SetNotifyFunction(std::function<void()> notifyFunc)
{
	m_NotifyFunction = notifyFunc;
}

void dae::Listener::Notify() const
{
	m_NotifyFunction();
}

size_t dae::Listener::GetListenerId() const
{
	return m_currId;
}

bool dae::Listener::CompareId(const Listener& list)
{
	return m_currId = list.m_currId;
}

void dae::Listener::StopListening()
{
	m_pEvent->RemoveListener(m_currId);
}
