#pragma once
#include <XInput.h>
#include <map>
#include <unordered_map>


#include "Singleton.h"
#include "ControllerButton.h"
#include "BaseCommand.h"
#include "Structs.h"

namespace dae
{
	// SDL Key code
	struct SDLCommand
	{
		SDLCommand()
			:_sdlKey{ '\0' } //https://wiki.libsdl.org/SDLKeycodeLookup SDL_UNKNOWN
		{}
		// int32_t correspond to a certain key code by SDL
		SDLCommand(int32_t key)
			:_sdlKey{ key }
		{}

		int32_t _sdlKey;

		bool _keyPressed{ false };
		bool _keyUp{ false };
		bool _keyDown{ false };
	};
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager() = default;
		~InputManager() override;

		void Initialize();
		
		bool ProcessInput();
		bool ProcessKeyboardInput();
		bool ProcessControllerInput();

		// Mouse
		Float2 GetMousePos();
		void UpdateMousePos();

		void AddInput(const std::string& name, int32_t sdlKey);
		bool AddCommand(BaseCommand* pCommand, ControllerButton button);

		bool IsPressed(std::string&& name);	  // get input by name
		bool KeyDown(std::string&& name);
		bool KeyUp(std::string&& name);
		
		bool IsPressed(ControllerButton button, int controllerId) const;
		bool KeyUp(ControllerButton button, int controllerId) const;
		bool KeyDown(ControllerButton button, int controllerId) const;

		bool IsControllerConnected(int controllerId) const
		{
			return m_XInputCurrStates[controllerId].first;
		}

		void SetRumble(int controllerId) const;

	private:

		Float2 m_mousePos;

		std::unordered_map<std::string, SDLCommand> m_KeyCommands;
		// Command
		std::map<ControllerButton, BaseCommand*> m_mapCommands;
		// Controller state
		std::pair<bool, XINPUT_STATE> m_XInputCurrStates[XUSER_MAX_COUNT]{};
		// Key state
		XINPUT_KEYSTROKE m_XInputKeyState[XUSER_MAX_COUNT]{};

		int m_vibrationValue{};
	};

}
