#pragma once
#include "BaseCommand.h"

namespace dae
{
	class GameObject;
	class Player;
	
	class MoveUp : public BaseCommand
	{
	public:
		MoveUp(int ID, RequiredKeyState state, Player* gO);
		~MoveUp() override = default;

		MoveUp(MoveUp const& other) = delete;
		MoveUp(MoveUp&& other) = delete;
		MoveUp& operator=(MoveUp const& rhs) = delete;
		MoveUp& operator=(MoveUp&& rhs) = delete;

		void Execute() override;
	};

	class MoveDown : public BaseCommand
	{
	public:
		MoveDown(int ID, RequiredKeyState state, Player* gO);
		~MoveDown() override = default;

		MoveDown(MoveDown const& other) = delete;
		MoveDown(MoveDown&& other) = delete;
		MoveDown& operator=(MoveDown const& rhs) = delete;
		MoveDown& operator=(MoveDown&& rhs) = delete;

		void Execute() override;
	};

	class MoveLeft : public BaseCommand
	{
	public:
		MoveLeft(int ID, RequiredKeyState state, Player* gO);
		~MoveLeft() override = default;

		MoveLeft(MoveLeft const& other) = delete;
		MoveLeft(MoveLeft&& other) = delete;
		MoveLeft& operator=(MoveLeft const& rhs) = delete;
		MoveLeft& operator=(MoveLeft&& rhs) = delete;

		void Execute() override;

	};

	class MoveRight : public BaseCommand
	{
	public:
		MoveRight(int ID, RequiredKeyState state, Player* gO);
		~MoveRight() override = default;

		MoveRight(MoveRight const& other) = delete;
		MoveRight(MoveRight&& other) = delete;
		MoveRight& operator=(MoveRight const& rhs) = delete;
		MoveRight& operator=(MoveRight&& rhs) = delete;

		void Execute() override;
	};
}