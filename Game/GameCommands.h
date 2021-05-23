#pragma once
#include "BaseCommand.h"

// Replaces Commands.h
namespace dae
{
	class GameObject;
	class Player;
	
	class MoveUp : public BaseCommand
	{
	public:
		MoveUp(int ID, RequiredKeyState state, Player* gO);
		~MoveUp() = default;

		void Execute() override;

		Input _cmdInput;
	};

	class MoveDown : public BaseCommand
	{
	public:
		MoveDown(int ID, RequiredKeyState state, Player* gO);
		~MoveDown() = default;

		void Execute() override;

		Input _cmdInput;
	};

	class MoveLeft : public BaseCommand
	{
	public:
		MoveLeft(int ID, RequiredKeyState state, Player* gO);
		~MoveLeft() = default;

		void Execute() override;

		Input _cmdInput;
	};

	class MoveRight : public BaseCommand
	{
	public:
		MoveRight(int ID, RequiredKeyState state, Player* gO);
		~MoveRight() = default;

		void Execute() override;

		Input _cmdInput;
	};
}