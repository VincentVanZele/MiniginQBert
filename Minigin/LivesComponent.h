#pragma once
#include "BaseComponent.h"

namespace dae
{
	class DieObserver;
	class TextComponent;

	class LivesComponent : public BaseComponent
	{
	public:
		LivesComponent(DieObserver* comp);
		~LivesComponent();

		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) noexcept = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() override;

	private:
		int m_lives{};
		
		TextComponent* m_pTextComponent = nullptr;
		DieObserver* m_pDieObserver = nullptr;

	};

}
