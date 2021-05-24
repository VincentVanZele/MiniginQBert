#include "MiniginPCH.h"
#include "Commands.h"
#include <iostream>


#include "AudioSystem.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "ServiceLocator.h"

/*
dae::Die::Die(int ID, RequiredKeyState state, bool& hasDied)
	: BaseCommand(ID, state)
	, _hasDied(hasDied)
{
}

void dae::Die::Execute()
{
	_hasDied = true;
	std::cout << "Die !\n";
	ServiceLocator::GetAudioSystem().AddAudio("sound.wav", 1, true);
}

// test purposes
dae::ChangeTile::ChangeTile(int ID, RequiredKeyState state, bool& hasModified)
	: BaseCommand(ID, state)
	, _hasModified(hasModified)
{
}

void dae::ChangeTile::Execute()
{
	_hasModified = true;
	std::cout << "Tile Changed !\n";
	ServiceLocator::GetAudioSystem().AddAudio("sound.wav", 1, true);
}

dae::Kill::Kill(int ID, RequiredKeyState state, bool& hasKilled)
	: BaseCommand(ID, state)
	, _hasKilled(hasKilled)
{
}

void dae::Kill::Execute()
{
	_hasKilled = true;
	std::cout << "Killed Enemy !\n";
	ServiceLocator::GetAudioSystem().AddAudio("sound.wav", 1, true);
}*/
