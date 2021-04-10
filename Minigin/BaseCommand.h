#pragma once
#include "Enums.h"

namespace dae
{
	class BaseCommand
	{
	public:
		BaseCommand(int controllerID, RequiredKeyState state)
			: m_controllerId{ controllerID }
			, m_keyState{ state }
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

	protected:
		int m_controllerId = 0;

		RequiredKeyState m_keyState = RequiredKeyState::Default;
	};
}