#pragma once
#include "Scene.h"
#include "Structs.h"

namespace dae
{
	class WorldGrid;
	class Player;

	class TitleScreenScene final : public dae::Scene
	{
	public:
		TitleScreenScene();

		void Initialize() override;
		void Update() override;
		//virtual void Draw() const override;
	private:
		bool _isCoop = true;

		std::shared_ptr<GameObject> yep;
		WorldGrid* m_world{ nullptr };
		Player* m_player{ nullptr };
	};

}