#pragma once
#include "Scene.h"

namespace dae
{
	class Eggs;
	class ScoreObserver;
	class TextComponent;
	class WorldGrid;
	class Player;

	class Level2 final : public dae::Scene
	{
	public:
		Level2();

		void Initialize() override;
		void Update() override;

	private:
		int m_numberTiles{}, m_numberDisks{ 2 };

		ScoreObserver* m_obs{ nullptr };
		TextComponent* m_score{ nullptr };
		WorldGrid* m_world{ nullptr };
		Player* m_player{ nullptr };
		Eggs* m_eggP{ nullptr }, * m_eggR{ nullptr };
	};

}
