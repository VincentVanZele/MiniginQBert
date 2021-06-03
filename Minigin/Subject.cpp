#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"

void dae::Subject::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	m_Observers.erase
	(std::find(m_Observers.begin(), m_Observers.end(), observer));
}

void dae::Subject::RemoveAllObservers()
{
	m_Observers.erase(m_Observers.begin(), m_Observers.end());
}

void dae::Subject::DeleteAllObservers()
{
	for (Observer* pObserver : m_Observers)
	{
		if (pObserver != nullptr)
		{
			delete(pObserver);
			pObserver = nullptr;
		}
	}
	RemoveAllObservers();
}

void dae::Subject::Notify(GameEvent event)
{
	for (Observer* observer : m_Observers)
	{
		observer->Notify(event);
	}
}