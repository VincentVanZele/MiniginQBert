#include "pch.h"
#include "StateMachine.h"
#include "InputManager.h"

// ==========
//    Idle
// ==========

dae::IdleState::IdleState(dae::GameObject* pGameObject)
    : ActorState(pGameObject)
{
    m_pPlayer = pGameObject->GetComponent<Player>();
}

void dae::IdleState::EnterState()
{
    m_pSpriteComp->SetActiveAnimation("Up");
}

dae::ActorState* dae::IdleState::Update(float deltaTime)
{
    UNREFERENCED_PARAMETER(deltaTime);

    if (m_pPlayer != nullptr)
    {
        if (m_pPlayer->GetInput() == Input::Up)
        {
            return new UpState(m_pGameObject);
        }

        if (m_pPlayer->GetInput() == Input::Down)
        {
            return new DownState(m_pGameObject);
        }
    	
        if (m_pPlayer->GetInput() == Input::Left)
        {
            return new LeftState(m_pGameObject);
        }

        if (m_pPlayer->GetInput() == Input::Right)
        {
            return new RightState(m_pGameObject);
        }       
    }

    return nullptr;
}

void dae::IdleState::ExitState()
{
	
}

// ==========
//     Up
// ==========


dae::UpState::UpState(dae::GameObject* pGameObject)
    : ActorState(pGameObject)
{
    m_pPlayer = pGameObject->GetComponent<Player>();
    m_pSpriteComp = pGameObject->GetComponent<SpriteComponent>();
}

void dae::UpState::EnterState()
{
    m_pSpriteComp->SetActiveAnimation("Up");
}

dae::ActorState* dae::UpState::Update(float )
{
    if (m_pPlayer->GetInput() == Input::Up)
    {
        Float3 pos = m_pGameObject->GetPosition();
        //pos._x -= deltaTime * m_pPlayer->GetWalkSpeed();
    	
        m_pGameObject->SetPosition(pos._x, pos._y);
        return nullptr;
    }

    return new IdleState(m_pGameObject);
}

void dae::UpState::ExitState()
{
}

// ==========
//    Down
// ==========

dae::DownState::DownState(dae::GameObject* pGameObject)
    : ActorState(pGameObject)
{
    m_pPlayer = pGameObject->GetComponent<Player>();
    m_pSpriteComp = pGameObject->GetComponent<SpriteComponent>();
}

void dae::DownState::EnterState()
{
    m_pSpriteComp->SetActiveAnimation("Down");
}

dae::ActorState* dae::DownState::Update(float )
{
    if (m_pPlayer->GetInput() == Input::Down)
    {
        Float3 pos = m_pGameObject->GetPosition();
        //pos._x += deltaTime * m_pPlayer->GetWalkSpeed();
    	
        m_pGameObject->SetPosition(pos._x, pos._y);
        return nullptr;
    }

    return new IdleState(m_pGameObject);
}

void dae::DownState::ExitState()
{
}

// ==========
//    Left
// ==========

dae::LeftState::LeftState(dae::GameObject* pGameObject)
    : ActorState(pGameObject)
{
    m_pPlayer = pGameObject->GetComponent<Player>();
    m_pSpriteComp = pGameObject->GetComponent<SpriteComponent>();
}

void dae::LeftState::EnterState()
{
    m_pSpriteComp->SetActiveAnimation("Left");
}

dae::ActorState* dae::LeftState::Update(float )
{
    if (m_pPlayer->GetInput() == Input::Left)
    {
        Float3 pos = m_pGameObject->GetPosition();
        //pos._y += deltaTime * m_pPlayer->GetWalkSpeed();
    	
        m_pGameObject->SetPosition(pos._x, pos._y);
        return nullptr;
    }

    return new IdleState(m_pGameObject);
}

void dae::LeftState::ExitState()
{
}

// ===========
//    Right
// ===========

dae::RightState::RightState(dae::GameObject* pGameObject)
    : ActorState(pGameObject)
{
    m_pPlayer = pGameObject->GetComponent<Player>();
    m_pSpriteComp = pGameObject->GetComponent<SpriteComponent>();
}

void dae::RightState::EnterState()
{
    m_pSpriteComp->SetActiveAnimation("Right");
}

dae::ActorState* dae::RightState::Update(float )
{
	// walk will probably delete
    if (m_pPlayer->GetInput() == Input::Up)
    {
        Float3 pos = m_pGameObject->GetPosition();
       // pos._y -= deltaTime * m_pPlayer->GetWalkSpeed();
    	
        m_pGameObject->SetPosition(pos._x, pos._y);
        return nullptr;
    }

    return new IdleState(m_pGameObject);
}

void dae::RightState::ExitState()
{
}

// ===========
//    Jump
// ===========

dae::JumpingState::JumpingState(dae::GameObject* pGameObject)
	: ActorState(pGameObject)
{
	
}

void dae::JumpingState::EnterState()
{
	
}

dae::ActorState* dae::JumpingState::Update(float )
{

    return new IdleState(m_pGameObject);
}

void dae::JumpingState::ExitState()
{
	
}
