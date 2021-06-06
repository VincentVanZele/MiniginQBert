#pragma once
#include <Structs.h>

#include "Scene.h"

namespace dae
{
	class SpriteComponent;
	
	class EndScreen final : public dae::Scene
	{
	public:
		EndScreen();
		EndScreen(int player);

		void Initialize() override;
		void Update() override;

		void ButtonClicked(Button button);

	private:
		Button m_button;

		Float2 m_lv1Pos{};
		std::shared_ptr<GameObject> m_spSelection, m_spSelection2;
		SpriteComponent* m_selectionComp, * m_selectionComp2;
	};
}
