#include "MiniginPCH.h"
#include "PlayerComponent.h"

#include "Commands.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "WorldComponent.h"

dae::PlayerComponent::PlayerComponent(PlayerIndex player)
	: m_PlayerNumber{ player }
{
	m_pSubject = new Subject();
}

dae::PlayerComponent::~PlayerComponent()
{
	m_pSubject->DeleteAllObservers();
	if (m_pSubject != nullptr)
	{
		delete(m_pSubject);
		m_pSubject = nullptr;
	}
}

void dae::PlayerComponent::Initialize()
{
	switch(m_PlayerNumber)
	{
	case PlayerIndex::PlayerOne:
		// 0 -> first controller
		if (ServiceLocator::GetInputManager()->GetInstance().IsControllerConnected(0))
		{
			m_ControllerId = 0;
			break;
		}
	case PlayerIndex::PlayerTwo:
		// 1 -> second controller  
		if (ServiceLocator::GetInputManager()->GetInstance().IsControllerConnected(1))
		{
			m_ControllerId = 1;
			break;
		}
	}

	InputManager::GetInstance().AddCommand(new Die(m_ControllerId, RequiredKeyState::KeyDown, GetGameObject()->GetComponent<PlayerComponent>()->m_hasDied), ControllerButton::AVK);
	InputManager::GetInstance().AddCommand(new Kill(m_ControllerId, RequiredKeyState::KeyDown, GetGameObject()->GetComponent<WorldComponent>()->m_hasKilled ), ControllerButton::XVK);
	InputManager::GetInstance().AddCommand(new ChangeTile(m_ControllerId, RequiredKeyState::KeyDown, GetGameObject()->GetComponent<WorldComponent>()->m_hasChengedTile), ControllerButton::YVK);
}

void dae::PlayerComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	//temporary -> will be changed to state machine
	if(m_hasDied)
	{
		--m_lives;
		m_pSubject->Notify(GetGameObject(), Event::Died);
		m_hasDied = false;
	}
}

void dae::PlayerComponent::Render()
{
	
}

void dae::PlayerComponent::AddObserver(Observer* observer)
{
	m_pSubject->AddObserver(observer);
}

void dae::PlayerComponent::RemoveObserver(Observer* observer)
{
	m_pSubject->RemoveObserver(observer);
}