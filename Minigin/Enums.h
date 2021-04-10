#pragma once

enum class RequiredKeyState
{
	KeyDown,
	KeyUp,
	KeyPressed,

	Default
};

enum class Event
{
	Default,
	Died,
	Killed,
	TileChanged
};

enum class PlayerNumber
{
	PlayerOne,
	PlayerTwo
};