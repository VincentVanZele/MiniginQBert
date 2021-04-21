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
		ColliderComponent(std::vector<std::weak_ptr<GameObject>>* pDynamicGameObjects, SDL_Rect rect, bool isStatic = true);
		~ColliderComponent() override;
		
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) noexcept = delete;
		ColliderComponent& operator=(const ColliderComponent& other) = delete;
		ColliderComponent& operator=(ColliderComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;

		void UpdatePosition(int x, int y) { m_Rect.x = x; m_Rect.y = y; }
		
		SDL_Rect GetSDLRect() const { return m_Rect; }
		Float4 GetDAERect() const { return Float4((float)m_Rect.x, (float)(m_Rect.y + m_Rect.h), (float)m_Rect.w, (float)m_Rect.h); }
		std::vector<Float2> GetDAERectCornerPoints() const;
		
		bool IsOverlapping() { return m_IsOverlapping; }
		std::vector<std::weak_ptr<GameObject>> GetOverlappingGameObjects() { return m_pWeakOverlappingGameObjects; }
	
	private:
		SDL_Rect m_Rect{};
		
		bool m_IsOverlapping = false;
		bool m_IsStatic = true;
		
		const float m_Gravity = 9.81f;
		const float m_MinDistance = 25;
		
		Elite::FVector2 m_Center{};
		
		std::vector<std::weak_ptr<GameObject>>* m_pDynamicGameObjects;
		std::vector<std::weak_ptr<GameObject>> m_pWeakOverlappingGameObjects{};
	};

}