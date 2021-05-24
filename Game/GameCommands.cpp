#include "pch.h"
#include "GameCommands.h"
#include "GameObject.h"
#include "GridTile.h"
#include "Player.h"

dae::MoveUp::MoveUp(int ID, RequiredKeyState state, Player* gO)
	: BaseCommand(ID, state, gO)
{
	if (gO == nullptr)
	{
		std::cout << "MoveUp Command: GameObject has no PlayerController component.\n";
	}
}

void dae::MoveUp::Execute()
{
	if (!m_player->GetMoveRestriction())
	{
		m_player->MoveTo(TileConnections::Up);
	}
}

dae::MoveDown::MoveDown(int ID, RequiredKeyState state, Player* gO)
	: BaseCommand(ID, state, gO)
{
	if (gO == nullptr)
	{
		std::cout << "MoveDown Command: GameObject has no PlayerController component.\n";
	}
}

void dae::MoveDown::Execute()
{
	if (!m_player->GetMoveRestriction())
	{
		m_player->MoveTo(TileConnections::Down);
	}
}

dae::MoveLeft::MoveLeft(int ID, RequiredKeyState state, Player* gO)
	: BaseCommand(ID, state, gO)
{
	if (gO == nullptr)
	{
		std::cout << "MoveLeft Command: GameObject has no PlayerController component.\n";
	}
}

void dae::MoveLeft::Execute()
{
	if (!m_player->GetMoveRestriction())
	{
		m_player->MoveTo(TileConnections::Left);
	}
}

dae::MoveRight::MoveRight(int ID, RequiredKeyState state, Player* gO)
	: BaseCommand(ID, state, gO)
{
	if (gO == nullptr)
	{
		std::cout << "MoveRight Command: GameObject has no PlayerController component.\n";
	}
}

void dae::MoveRight::Execute()
{
	if (!m_player->GetMoveRestriction())
	{
		m_player->MoveTo(TileConnections::Right);
	}
}

