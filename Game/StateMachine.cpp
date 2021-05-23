#include "pch.h"
#include "StateMachine.h"
#include "InputManager.h"
#include "TransformComponent.h"
#include "GameObject.h"

// ==========
//    Idle
// ==========

dae::IdleState::IdleState(std::shared_ptr<GameObject> pGameObject)
    : ActorState(pGameObject)
{
    m_pPlayer = pGameObject->GetComponent<Player>();
}

void dae::IdleState::EnterState()
{
    m_pSpriteComp->SetActiveAnimation("Up");
}

dae::ActorState* dae::IdleState::Update()
{

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


dae::UpState::UpState(std::shared_ptr<GameObject> pGameObject)
    : ActorState(pGameObject)
{
    m_pPlayer = pGameObject->GetComponent<Player>();
    m_pSpriteComp = pGameObject->GetComponent<SpriteComponent>();
}

void dae::UpState::EnterState()
{
    m_pSpriteComp->SetActiveAnimation("Up");
}

dae::ActorState* dae::UpState::Update( )
{
    if (m_pPlayer->GetInput() == Input::Up)
    {
        Float2 pos = m_pGameObject->GetTransform()->GetPosition();
        //pos._x -= deltaTime * m_pPlayer->GetWalkSpeed();
    	
        m_pGameObject->GetTransform()->SetPosition(Float2{ pos._x, pos._y });
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

dae::DownState::DownState(std::shared_ptr<GameObject> pGameObject)
    : ActorState(pGameObject)
{
    m_pPlayer = pGameObject->GetComponent<Player>();
    m_pSpriteComp = pGameObject->GetComponent<SpriteComponent>();
}

void dae::DownState::EnterState()
{
    m_pSpriteComp->SetActiveAnimation("Down");
}

dae::ActorState* dae::DownState::Update( )
{
    if (m_pPlayer->GetInput() == Input::Down)
    {
        Float2 pos = m_pGameObject->GetTransform()->GetPosition();
        //pos._x += deltaTime * m_pPlayer->GetWalkSpeed();
    	
        m_pGameObject->GetTransform()->SetPosition(Float2{ pos._x, pos._y });
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

dae::LeftState::LeftState(std::shared_ptr<GameObject> pGameObject)
    : ActorState(pGameObject)
{
    m_pPlayer = pGameObject->GetComponent<Player>();
    m_pSpriteComp = pGameObject->GetComponent<SpriteComponent>();
}

void dae::LeftState::EnterState()
{
    m_pSpriteComp->SetActiveAnimation("Left");
}

dae::ActorState* dae::LeftState::Update( )
{
    if (m_pPlayer->GetInput() == Input::Left)
    {
        Float2 pos = m_pGameObject->GetTransform()->GetPosition();
        //pos._y += deltaTime * m_pPlayer->GetWalkSpeed();
    	
        m_pGameObject->GetTransform()->SetPosition(Float2{ pos._x, pos._y });
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

dae::RightState::RightState(std::shared_ptr<GameObject> pGameObject)
    : ActorState(pGameObject)
{
    m_pPlayer = pGameObject->GetComponent<Player>();
    m_pSpriteComp = pGameObject->GetComponent<SpriteComponent>();
}

void dae::RightState::EnterState()
{
    m_pSpriteComp->SetActiveAnimation("Right");
}

dae::ActorState* dae::RightState::Update( )
{
	// walk will probably delete
    if (m_pPlayer->GetInput() == Input::Up)
    {
        Float2 pos = m_pGameObject->GetTransform()->GetPosition();
       // pos._y -= deltaTime * m_pPlayer->GetWalkSpeed();
    	
        m_pGameObject->GetTransform()->SetPosition(Float2{ pos._x, pos._y });
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

dae::JumpingState::JumpingState(std::shared_ptr<GameObject> pGameObject)
	: ActorState(pGameObject)
{
	
}

void dae::JumpingState::EnterState()
{
	
}

dae::ActorState* dae::JumpingState::Update( )
{

    return new IdleState(m_pGameObject);
}

void dae::JumpingState::ExitState()
{
	
}
