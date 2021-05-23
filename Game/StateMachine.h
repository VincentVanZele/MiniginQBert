#pragma once
#include "Player.h"
#include "ActorState.h"

namespace dae
{
	class IdleState : public ActorState
	{
	public:
		IdleState(std::shared_ptr<GameObject> pGameObject);
		~IdleState() override = default;

		void EnterState() override;
		ActorState* Update() override;
		void ExitState() override;

	};

	class UpState : public ActorState
	{
	public:
		UpState(std::shared_ptr<GameObject> pGameObject);
		~UpState() override = default;

		void EnterState() override;
		ActorState* Update() override;
		void ExitState() override;

	};

	class DownState : public ActorState
	{
	public:
		DownState(std::shared_ptr<GameObject> pGameObject);
		~DownState() = default;

		void EnterState() override;
		ActorState* Update() override;
		void ExitState() override;

	};

	class LeftState : public ActorState
	{
	public:
		LeftState(std::shared_ptr<GameObject> pGameObject);
		~LeftState() override = default;

		void EnterState() override;
		ActorState* Update() override;
		void ExitState() override;

	};

	class RightState : public ActorState
	{
	public:
		RightState(std::shared_ptr<GameObject> pGameObject);
		~RightState() override = default;

		void EnterState() override;
		ActorState* Update() override;
		void ExitState() override;

	};

	class JumpingState : public ActorState
	{
	public:
		JumpingState(std::shared_ptr<GameObject> pGameObject);
		~JumpingState() override = default;

		void EnterState() override;
		ActorState* Update() override;
		void ExitState() override;

	};
}