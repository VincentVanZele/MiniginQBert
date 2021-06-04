#pragma once
#include "Scene.h"

namespace dae
{
	class WorldGrid;
	class Player;

	class Versus final : public dae::Scene
	{
	public:
		Versus();

		void Initialize() override;
		void Update() override;

	private:
		WorldGrid* m_world{ nullptr };
		Player* m_player{ nullptr };
		Player* m_player2{ nullptr };
	};

}