#pragma once
// Implement 4 commands(for example "Fire", "Duck", "Jump" and “Fart")
#include "BaseCommand.h"

namespace dae
{
	class GameObject;

	class Die : public BaseCommand
	{
	public:
		// bool will be state machine
		Die(int ID, RequiredKeyState state, bool& hasDied);
		~Die() = default;

		void Execute() override;
		bool& _hasDied;
	};

	// test purposes
	class ChangeTile : public BaseCommand
	{
	public:
		ChangeTile(int ID, RequiredKeyState state, bool& hasModified);
		~ChangeTile() = default;

		void Execute() override;
		bool& _hasModified;
	};

	class Kill : public BaseCommand
	{
	public:
		Kill(int ID, RequiredKeyState state, bool& hasKilled);
		~Kill() = default;

		void Execute() override;
		bool& _hasKilled;
	};
}