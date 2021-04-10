#pragma once

namespace dae
{
	class GameObject;
	
	class ActorState
	{
	public:
		ActorState(dae::GameObject* pGameObject)
		: m_pGameObject{ pGameObject }
		{};
		virtual ~ActorState()
		{
			m_pGameObject = nullptr;
		}

		ActorState(const ActorState& other) = delete;
		ActorState(ActorState&& other) noexcept = delete;
		ActorState& operator=(const ActorState& other) = delete;
		ActorState& operator=(ActorState&& other) noexcept = delete;
		
		virtual void EnterState() = 0;
		virtual void ExitState() = 0;
		
		virtual ActorState* Update(float deltaTime) = 0;
		

		GameObject* GetGameObject() const
		{
			return m_pGameObject;
		}
		void SetGameObject(GameObject* gameObject)
		{
			m_pGameObject = gameObject;
		}
	
	protected:
		GameObject* m_pGameObject = nullptr;
	};
}
