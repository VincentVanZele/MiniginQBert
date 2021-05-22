#pragma once
#include "Scene.h"

namespace dae
{
	class WorldGrid;
	class Player;
	
	class GameScene final : public dae::Scene
	{
	public:
		GameScene();
		~GameScene() = default;

		void Initialize();
	private:

		WorldGrid* m_world{ nullptr };
		Player* m_player{nullptr};
	};

}