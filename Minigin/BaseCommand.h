#pragma once
#include "Enums.h"

namespace dae
{
	class Player;

	class BaseCommand
	{
	public:
		BaseCommand(int controllerID, RequiredKeyState state, Player* player)
			: m_controllerId{ controllerID }
			, m_keyState{ state }
			, m_player{player}
		{
		}
		virtual ~BaseCommand() = default;

		virtual void Execute() = 0;

		void SetControllerId(int controllerId)
		{
			m_controllerId = controllerId;
		}
		int GetControllerId() const
		{
			return m_controllerId;
		}

		void SetKeyState(RequiredKeyState state)
		{
			m_keyState = state;
		}
		RequiredKeyState GetKeyState() const
		{
			return m_keyState;
		}

		void SetPlayer(Player* player)
		{
			m_player = player;
		}
		Player* GetPlayer() const
		{
			return m_player;
		}

	protected:
		int m_controllerId = 0;

		RequiredKeyState m_keyState = RequiredKeyState::Default;
		Player* m_player;
	};
}