#pragma once
#include "BaseComponent.h"
#include <SDL.h>
#include "SceneManager.h"
#include <memory>
#include "EMath.h"
#include <vector>
#include "Structs.h"

namespace dae
{
	class ColliderComponent : public dae::BaseComponent
	{
	public:
		ColliderComponent(std::vector<std::weak_ptr<GameObject>>* pGo, SDL_Rect rect);
		~ColliderComponent() override = default;
		
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) noexcept = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;

		void UpdatePosition(int x, int y)
		{
			m_Rect.x = x; m_Rect.y = y;
		}

		Float4 GetRect() const
		{
			return { (float)m_Rect.x, (float)(m_Rect.y + m_Rect.h), (float)m_Rect.w, (float)m_Rect.h };
		}

		void SetSDLRect(SDL_Rect rect)
		{
			m_Rect = rect;
		}
		SDL_Rect GetSDLRect() const
		{
			return m_Rect;
		}
		
		bool IsOverlapping() const
		{
			return m_IsOverlapping;
		}
	
	private:
		SDL_Rect m_Rect{};
		
		bool m_IsOverlapping = false;
		
		const float m_MinDistance = 25;
		
		Elite::FVector2 m_Center{};
		
		std::vector<std::weak_ptr<GameObject>>* m_pColliderGameObjects;
	};

}