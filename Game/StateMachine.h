#pragma once
#include "Player.h"
#include "ActorState.h"

namespace dae
{
	class IdleState : public ActorState
	{
	public:
		IdleState(dae::GameObject* pGameObject);
		~IdleState() = default;

		void EnterState() override;
		ActorState* Update(float deltaTime) override;
		void ExitState() override;

	};

	class UpState : public ActorState
	{
	public:
		UpState(dae::GameObject* pGameObject);
		~UpState() = default;

		void EnterState() override;
		ActorState* Update(float deltaTime) override;
		void ExitState() override;

	};

	class DownState : public ActorState
	{
	public:
		DownState(dae::GameObject* pGameObject);
		~DownState() = default;

		void EnterState() override;
		ActorState* Update(float deltaTime) override;
		void ExitState() override;

	};

	class LeftState : public ActorState
	{
	public:
		LeftState(dae::GameObject* pGameObject);
		~LeftState() = default;

		void EnterState() override;
		ActorState* Update(float deltaTime) override;
		void ExitState() override;

	};

	class RightState : public ActorState
	{
	public:
		RightState(dae::GameObject* pGameObject);
		~RightState() = default;

		void EnterState() override;
		ActorState* Update(float deltaTime) override;
		void ExitState() override;

	};
}