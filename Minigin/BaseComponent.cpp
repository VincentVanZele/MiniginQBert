#include "MiniginPCH.h"
#include "BaseComponent.h"

#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

#include "GameObject.h"


dae::BaseComponent::BaseComponent()
	:m_pGameObject{}
{
}

void dae::BaseComponent::SetGameObject(std::shared_ptr<GameObject> pGO)
{
	m_pGameObject = pGO;
}

void dae::BaseComponent::SetActive(bool active)
{
	m_IsActive = active;

	if (!m_IsActive)
	{
		bool allInactive = true;

		for (auto pComp : GetGameObject()->m_pComponents)
		{
			if (pComp->GetActive())
			{
				allInactive = false;
				break;
			}
		}
		if (allInactive)
		{
			GetGameObject()->m_IsActive = false;
		}
	}
	else
	{
		GetGameObject()->m_IsActive = true;
	}
}

bool dae::BaseComponent::GetActive() const
{
	return m_IsActive;
}

dae::TransformComponent* dae::BaseComponent::GetTransform() const
{
	// TODO: insert return statement here
#if _DEBUG
	if (GetGameObject() == nullptr)
	{
		std::cout << "BaseComponent::GetTransform() > Failed to retrieve the TransformComponent. GameObject is NULL." << '\n';
	}
#endif

	return GetGameObject()->GetTransform();
}

void dae::BaseComponent::AddComponent(BaseComponent* pComp)
{
	GetGameObject()->AddComponent(pComp);
}

void dae::BaseComponent::RemoveComponent(BaseComponent* pComp)
{
	GetGameObject()->RemoveComponent(pComp);
}

void dae::BaseComponent::DestroyGameObject()
{
	GetGameObject()->DestroyObject();
}

void dae::BaseComponent::AddChild(std::shared_ptr<GameObject> child)
{
	GetGameObject()->AddChild(child);
}







