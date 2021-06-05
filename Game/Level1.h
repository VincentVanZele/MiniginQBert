#pragma once
#include "Scene.h"

namespace dae
{
	class Enemy;
	class Eggs;
	class ScoreObserver;
	class TextComponent;
	class WorldGrid;
	class Player;

	class Level1 final : public dae::Scene
	{
	public:
		Level1();

		void Initialize() override;
		void Update() override;

	private:
		int m_numberTiles{}, m_numberDisks{ 2 };
		bool m_doOnce{ true };

		ScoreObserver* m_obs{ nullptr };
		TextComponent* m_score{ nullptr };
		WorldGrid* m_world{ nullptr };
		Player* m_player{ nullptr };
		Enemy* m_enemy{ nullptr };
		Eggs* m_eggP{ nullptr }, * m_eggR{ nullptr };
	};

}