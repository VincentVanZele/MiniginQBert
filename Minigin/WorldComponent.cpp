#include "MiniginPCH.h"
#include "WorldComponent.h"

#include "Enums.h"
#include "Subject.h"

dae::WorldComponent::WorldComponent()
{
	m_pSubject = new Subject();
}

dae::WorldComponent::~WorldComponent()
{
	m_pSubject->DeleteAllObservers();
	if (m_pSubject != nullptr)
	{
		delete(m_pSubject);
		m_pSubject = nullptr;
	}
}

void dae::WorldComponent::Initialize()
{
}

void dae::WorldComponent::Update()
{

	if (m_hasKilled)
	{
		m_pSubject->Notify(Event::Killed);
		m_hasKilled = false;
	}
	if(m_hasChengedTile)
	{
		m_pSubject->Notify(Event::TileChanged);
		m_hasChengedTile = false;
	}
}

void dae::WorldComponent::Render()
{
}

void dae::WorldComponent::AddObserver(Observer* observer)
{
	m_pSubject->AddObserver(observer);
}

void dae::WorldComponent::RemoveObserver(Observer* observer)
{
	m_pSubject->RemoveObserver(observer);
}