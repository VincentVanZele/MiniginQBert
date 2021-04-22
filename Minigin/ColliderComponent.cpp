#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "Utils.h"
#include "SDL.h"

dae::ColliderComponent::ColliderComponent(std::vector<std::weak_ptr<GameObject>>* pGameObjects, SDL_Rect rect)
	: m_pColliderGameObjects{ pGameObjects }
	, m_Rect{ rect }
{
}

void dae::ColliderComponent::Initialize()
{
	m_Center = Elite::FVector2(m_Rect.x + (m_Rect.w * 0.5f), (m_Rect.y - (m_Rect.h * 0.5f)));
}

void dae::ColliderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (m_pColliderGameObjects->empty())
	{
		return;
	}

	
	m_IsOverlapping = false;

	for (std::weak_ptr<GameObject>& go : *m_pColliderGameObjects)
	{
		if (!go.expired())
		{
			auto sGo = go.lock();
			if (sGo)
			{
				auto pos = sGo->GetPosition();
				
				Elite::FPoint2 point1 = Elite::FPoint2(pos._x,pos._y);
				Elite::FPoint2 point2 = Elite::FPoint2(GetGameObject()->GetPosition()._x, GetGameObject()->GetPosition()._y);
				
				if (Elite::SqrDistance(point1, point2) < Elite::Square(m_MinDistance))
				{		
					ColliderComponent* rect = sGo->GetComponent<ColliderComponent>();
					
					if (rect != nullptr)
					{
						Float4 leftRect = rect->GetRect();
						Float4 rightRight = GetRect();
						
						if (DoRectsOverlap(leftRect, rightRight))
						{
							m_IsOverlapping = true;
						}
					}
				}
			}

		}
	}
}

void dae::ColliderComponent::Render()
{

}
