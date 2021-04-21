#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "Utils.h"
#include "SDL.h"

dae::ColliderComponent::ColliderComponent(std::vector<std::weak_ptr<GameObject>>* pDynamicGameObjects, SDL_Rect rect, bool isStatic)
	: m_pDynamicGameObjects{ pDynamicGameObjects }
	, m_Rect{ rect }
	, m_IsStatic{ isStatic }
{
	m_Center = Elite::FVector2(rect.x + (rect.w * 0.5f), (rect.y - (rect.h * 0.5f)));
}

dae::ColliderComponent::~ColliderComponent()
{
}

std::vector<dae::Float2> dae::ColliderComponent::GetDAERectCornerPoints() const
{
	std::vector<Float2> points;
	points.push_back(Float2((float)m_Rect.x, (float)m_Rect.y));
	points.push_back(Float2((float)(m_Rect.x + m_Rect.w), (float)m_Rect.y));
	points.push_back(Float2((float)(m_Rect.x + m_Rect.w), (float)(m_Rect.y + m_Rect.h)));
	points.push_back(Float2((float)m_Rect.x, (float)(m_Rect.y + m_Rect.h)));

	return points;
}

void dae::ColliderComponent::Initialize()
{

}

void dae::ColliderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (m_pDynamicGameObjects->empty())
		return;
	m_IsOverlapping = false;

	for (std::weak_ptr<GameObject>& wGameObject : *m_pDynamicGameObjects)
	{
		if (!wGameObject.expired())
		{
			auto sGameObject = wGameObject.lock();
			if (sGameObject)
			{
				auto pos = sGameObject->GetPosition();
				Elite::FPoint2 point1 = Elite::FPoint2(pos._x,pos._y);
				Elite::FPoint2 point2 = Elite::FPoint2(GetGameObject()->GetPosition()._x, GetGameObject()->GetPosition()._y);
				if (Elite::SqrDistance(point1, point2) < Elite::Square(m_MinDistance))
				{		
					ColliderComponent* pBox = sGameObject->GetComponent<ColliderComponent>();
					
					if (pBox != nullptr)
					{
						Float4 dynamicRectf = pBox->GetDAERect();
					
						Float4 staticRectf = GetDAERect();
						
						if (DoRectsOverlap(dynamicRectf, staticRectf))
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
