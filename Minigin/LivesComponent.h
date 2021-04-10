#pragma once
#include "BaseComponent.h"

namespace dae
{
	class PlayerComponent;
	class TextComponent;

	class LivesComponent : public BaseComponent
	{
	public:
		LivesComponent(PlayerComponent* comp);
		virtual ~LivesComponent() = default;

		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) noexcept = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;

	private:
		TextComponent* m_pTextComponent = nullptr;
		PlayerComponent* m_pPlayerComponent = nullptr;

		float m_refreshRate = 0.5f;
		float m_elapsedTime = 0;
	};

}
