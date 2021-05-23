#include "pch.h"
#include "GameCommands.h"
#include "GameObject.h"
#include "Player.h"

dae::MoveUp::MoveUp(int ID, RequiredKeyState state, Player* gO)
	: BaseCommand(ID, state)
{
	if (gO)
	{
		_cmdInput = gO->GetInput();
	}
	else
	{
		std::cout << "MoveUp Command: GameObject has no PlayerController component.\n";
	}
}

void dae::MoveUp::Execute()
{
	_cmdInput = Input::Up;
}

dae::MoveDown::MoveDown(int ID, RequiredKeyState state, Player* gO)
	: BaseCommand(ID, state)
{
	if (gO)
	{
		_cmdInput = gO->GetInput();
	}
	else
	{
		std::cout << "MoveDown Command: GameObject has no PlayerController component.\n";
	}
}

void dae::MoveDown::Execute()
{
	_cmdInput = Input::Down;
}

dae::MoveLeft::MoveLeft(int ID, RequiredKeyState state, Player* gO)
	: BaseCommand(ID, state)
{
	if (gO)
	{
		_cmdInput = gO->GetInput();
	}
	else
	{
		std::cout << "MoveLeft Command: GameObject has no PlayerController component.\n";

	}
}

void dae::MoveLeft::Execute()
{
	_cmdInput = Input::Left;
}

dae::MoveRight::MoveRight(int ID, RequiredKeyState state, Player* gO)
	: BaseCommand(ID, state)
{
	if (gO)
	{
		_cmdInput = gO->GetInput();
	}
	else
	{
		std::cout << "MoveRight Command: GameObject has no PlayerController component.\n";
	}
}

void dae::MoveRight::Execute()
{
	_cmdInput = Input::Right;
}

