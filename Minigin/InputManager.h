#pragma once
#include <XInput.h>
#include <map>

#include "Singleton.h"
#include "ControllerButton.h"
#include "BaseCommand.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		~InputManager() override;

		void Initialize();
		bool ProcessInput();

		bool AddCommand(BaseCommand* pCommand, ControllerButton button);

		bool IsPressed(ControllerButton button, int controllerId) const;
		bool KeyUp(ControllerButton button, int controllerId) const;
		bool KeyDown(ControllerButton button, int controllerId) const;

		bool IsControllerConnected(int controllerId) const
		{
			return m_XInputCurrStates[controllerId].first;
		}

		void SetRumble(int controllerId) const;

	private:
		// Command
		std::map<ControllerButton, BaseCommand*> m_mapCommands;
		// Controller state
		std::pair<bool, XINPUT_STATE> m_XInputCurrStates[XUSER_MAX_COUNT]{};
		// Key state
		XINPUT_KEYSTROKE m_XInputKeyState[XUSER_MAX_COUNT]{};

		int m_vibrationValue{};
	};

}
