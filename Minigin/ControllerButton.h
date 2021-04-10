#pragma once
#pragma comment(lib, "XInput.lib")

#include <windows.h>
#include <XInput.h>

namespace dae
{
	// VK in order to get the "key state" of the controller button
	enum class ControllerButton
	{
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y,

		AVK = VK_PAD_A,
		BVK = VK_PAD_B,
		XVK = VK_PAD_X,
		YVK = VK_PAD_Y,

		DpadUp = XINPUT_GAMEPAD_DPAD_UP,
		DpadDown = XINPUT_GAMEPAD_DPAD_DOWN,
		DpadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		DpadRight = XINPUT_GAMEPAD_DPAD_RIGHT,

		DpadUpVK = VK_GAMEPAD_DPAD_UP,
		DpadDownVK = VK_GAMEPAD_DPAD_DOWN,
		DpadLeftVK = VK_GAMEPAD_DPAD_LEFT,
		DpadRightVK = VK_GAMEPAD_DPAD_RIGHT,
	};
}