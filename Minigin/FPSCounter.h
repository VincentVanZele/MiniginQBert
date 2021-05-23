#pragma once
#include "BaseComponent.h"

namespace dae
{
	class FPSCounter : public dae::BaseComponent
	{
	public:
		FPSCounter() = default;
		~FPSCounter() = default;
		
		FPSCounter(const FPSCounter& other) = delete;
		FPSCounter(FPSCounter&& other) noexcept = delete;
		FPSCounter& operator=(const FPSCounter& other) = delete;
		FPSCounter& operator=(FPSCounter&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() override;

		int GetFPS() const
		{
			return static_cast<int>(m_FPS);
		}
		void SetActive(bool active)
		{
			m_active = active;
		}
	
	private:
		bool m_active = true;
		
		int m_FPS = 0;
		int m_counter = 0;
		
		float m_timer = 0.f;
	};
}
