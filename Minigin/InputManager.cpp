#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>

#define ZeroMemory RtlZeroMemory
#define ERROR_SUCCESS                    0L

// Microsoft : Getting Started With XInput
// https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput#multiple-controllers

//      DWORD dwResult;
//      for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
//      {
//      	  XINPUT_STATE state;
//      	  ZeroMemory(&state, sizeof(XINPUT_STATE));
//      	  
//      	  // Simply get the state of the controller from XInput.
//      	  dwResult = XInputGetState(i, &state);
//      	  
//      	  if (dwResult == ERROR_SUCCESS)
//      	  {
//      	  	// Controller is connected
//      	  }
//      	  else
//      	  {
//      	  	// Controller is not connected
//      	  }
//      }

dae::InputManager::~InputManager()
{
	for (std::pair<ControllerButton, BaseCommand*> pair : m_mapCommands)
	{
		if (pair.second != nullptr)
		{
			delete(pair.second);
			pair.second = nullptr;
		}
	}
}

void dae::InputManager::Initialize()
{
	// Retrieve Controller State
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&m_XInputCurrStates[i].second, sizeof(XINPUT_STATE));

		dwResult = XInputGetState(i, &m_XInputCurrStates[i].second);

		if (dwResult == ERROR_SUCCESS) // Connected
		{
			m_XInputCurrStates[i].first = true;
			std::cout << "XInputGetState - Controller " << i << " connected.\n";
		}
		else // Not connected
		{
			m_XInputCurrStates[i].first = false;
			std::cout << "XInputGetState - Controller " << i << " not connected.\n";
		}

		dwResult = XInputGetKeystroke(i, 0, &m_XInputKeyState[i]);

		if (dwResult == ERROR_NOT_CONNECTED) // Not Connected
		{
			std::cout << "XInputGetKeystroke - Controller " << i << " not connected.\n";
		}
	}
}

bool dae::InputManager::ProcessInput()
{
	if (!ProcessKeyboardInput())
	{
		return false;
	}
	if(!ProcessControllerInput())
	{
		return false;
	}
	
	return true;
}

bool dae::InputManager::ProcessKeyboardInput()
{
	for (auto& cmd : m_KeyCommands)
	{
		cmd.second._keyDown = false;
		cmd.second._keyUp = false;
	}

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		auto key = event.key.keysym.sym;

		switch (event.type)
		{
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			// command buttons
			for (std::pair<const std::string, SDLCommand>& cmd : m_KeyCommands)
			{
				if (cmd.second._sdlKey == key)
				{
					if (cmd.second._keyPressed)
						break;

					cmd.second._keyPressed = true;
					cmd.second._keyDown = true;
					break;
				}
			}
			break;
		case SDL_KEYUP:
			if (key == SDLK_ESCAPE)
				return false;

			for (std::pair<const std::string, SDLCommand>& cmd : m_KeyCommands)
			{
				if (cmd.second._sdlKey == key)
				{
					cmd.second._keyPressed = false;
					cmd.second._keyUp = true;
					break;
				}
			}
			break;
		}
	}
	return true;
}

dae::Float2 dae::InputManager::GetMousePos()
{
	return m_mousePos;
}

void dae::InputManager::UpdateMousePos()
{
	int x{}, y{};
	SDL_GetMouseState(&x, &y);

	m_mousePos._x = (float)x;
	m_mousePos._y = (float)y;
}

void dae::InputManager::AddInput(const std::string& name, int32_t sdlKey)
{
	m_KeyCommands[name] = SDLCommand(sdlKey);
}

bool dae::InputManager::IsPressed(std::string&& name)
{
	return m_KeyCommands[std::move(name)]._keyPressed;
}

bool dae::InputManager::KeyDown(std::string&& name)
{
	return m_KeyCommands[std::move(name)]._keyDown;
}

bool dae::InputManager::KeyUp(std::string&& name)
{
	return m_KeyCommands[std::move(name)]._keyUp;
}

bool dae::InputManager::ProcessControllerInput()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&m_XInputCurrStates[i].second, sizeof(XINPUT_STATE));

		dwResult = XInputGetState(i, &m_XInputCurrStates[i].second);

		if (dwResult == ERROR_SUCCESS) // Connected
		{
			m_XInputCurrStates[i].first = true;
		}
		else // Not connected
		{
			m_XInputCurrStates[i].first = false;
		}

		dwResult = XInputGetKeystroke(i, 0, &m_XInputKeyState[i]);
	}

	for (auto it = m_mapCommands.cbegin(); it != m_mapCommands.cend(); ++it)
	{
		switch (it->second->GetKeyState())
		{
		case RequiredKeyState::KeyDown:
			if (KeyDown(it->first, it->second->GetControllerId()))
			{
				it->second->Execute();
			}
			break;
		case RequiredKeyState::KeyUp:
			if (KeyUp(it->first, it->second->GetControllerId()))
			{
				it->second->Execute();
			}
			break;
		case RequiredKeyState::KeyPressed:
			if (IsPressed(it->first, it->second->GetControllerId()))
			{
				it->second->Execute();
			}
			break;
		case RequiredKeyState::Default:
			break;
		}
	}

	// Escape program
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || e.type == SDL_SCANCODE_ESCAPE)
		{
			return false;
		}
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button, int controllerID) const
{
	if (m_XInputCurrStates[controllerID].second.Gamepad.wButtons & static_cast<WORD>(button))
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool dae::InputManager::KeyUp(ControllerButton button, int controllerID) const
{
	// XINPUT VK
	if (m_XInputKeyState[controllerID].Flags == XINPUT_KEYSTROKE_KEYUP
		&& m_XInputKeyState[controllerID].VirtualKey == static_cast<WORD>(button))
	{
		return true;
	}

	return false;
}

bool dae::InputManager::KeyDown(ControllerButton button, int controllerID) const
{
	// XINPUT VK
	if (m_XInputKeyState[controllerID].Flags == XINPUT_KEYSTROKE_KEYDOWN
		&& m_XInputKeyState[controllerID].VirtualKey == static_cast<WORD>(button))
	{
		return true;
	}

	return false;
}

void dae::InputManager::SetRumble(int controllerId) const
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = static_cast<WORD>(m_vibrationValue);
	vibration.wRightMotorSpeed = static_cast<WORD>(m_vibrationValue);
	XInputSetState(static_cast<DWORD>(controllerId), &vibration);
}

bool dae::InputManager::AddCommand(BaseCommand* pCommand, ControllerButton button)
{
	if (pCommand != nullptr)
	{
		m_mapCommands[button] = pCommand;
		return true;
	}
	else
	{
		return false;
	}
}
