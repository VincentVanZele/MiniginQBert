#pragma once
#include "Scene.h"

namespace dae
{
	class Eggs;
	class ScoreObserver;
	class TextComponent;
	class WorldGrid;
	class Player;

	class TestScene final : public dae::Scene
	{
	public:
		TestScene();

		void Initialize() override;
		void Update() override;

	private:
		bool _isCoop = true;
		int m_numberTiles{}, m_numberDisks{ 2 };

		ScoreObserver* m_obs{ nullptr };
		TextComponent* m_score{ nullptr };
		WorldGrid* m_world{ nullptr };
		Player* m_player{ nullptr };
		Eggs* m_eggP{ nullptr }, * m_eggR{ nullptr };
	};

}