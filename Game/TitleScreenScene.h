#pragma once
#include <Structs.h>

#include "Scene.h"
#include "Structs.h"

namespace dae
{
	class SpriteComponent;

	enum Button
	{
		ButtonSolo,
		ButtonMultiplayer,
		ButtonExit
	};

	class TitleScreenScene final : public dae::Scene
	{
	public:
		TitleScreenScene();

		void Initialize() override;
		void Update() override;

		void ButtonClicked(Button button);
	
	private:
		Button m_selectedButton;

		Float2 m_soloPos{}, m_coopPos{}, m_exitPos{};
		std::shared_ptr<GameObject> m_spSelection;
		SpriteComponent* m_selectionComp;
	};

}