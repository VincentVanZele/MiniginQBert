#pragma once
#include <Structs.h>
#include "Scene.h"


namespace dae
{
	class SpriteComponent;

	class TitleScreenScene final : public dae::Scene
	{
	public:
		TitleScreenScene();

		void Initialize() override;
		void Update() override;

		void ButtonClicked(Button button);
	
	private:
		Button m_selectedButton;

		Float2 m_lv1Pos{}, m_lv2Pos{}, m_lv3Pos{}, m_vsPos{};
		std::shared_ptr<GameObject> m_spSelection, m_spSelection2;
		SpriteComponent* m_selectionComp, *m_selectionComp2;
	};

}