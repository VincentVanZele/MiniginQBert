#pragma once
#include "BaseComponent.h"

namespace dae
{
	class FPSCounter;
	class TextComponent;

	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent() = default;
		virtual ~FPSComponent() = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;
		
		void Initialize() override;
		void Update() override;
		void Render() override;

	private:
		FPSCounter* m_pFPSCounter = nullptr;
		TextComponent* m_pTextComponent = nullptr;
		
		float m_refreshRate = 0.5f;
		float m_elapsedTime = 0;
	};

}