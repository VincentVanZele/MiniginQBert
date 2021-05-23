#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "BaseComponent.h"
#include "Renderer.h"
#include "SceneObject.h"
#include <memory>
#include <algorithm>

dae::GameObject::GameObject(const Float2& pos, float rot, const Float2& sca)
	: m_pParentObject(nullptr)
	, m_pTransform(nullptr)
{
	auto trans = new TransformComponent();

	trans->SetPosition(pos);
	trans->SetRotation(rot);
	trans->SetScale(sca);

	m_pTransform = trans;
}

dae::GameObject::~GameObject()
{
	DestroyObject();
}

std::shared_ptr<dae::GameObject> dae::GameObject::NewGameObject()
{
	auto go = std::make_shared<GameObject>();
	return go;
}

void dae::GameObject::AddComponent(BaseComponent* pComp)
{
	for (auto component : m_pComponents)
	{
		if (component == pComp)
		{
			std::cout << "GameObject::AddComponent > GameObject already contains this component!";
			return;
		}
	}

	m_pComponents.push_back(pComp);
	pComp->m_pGameObject = shared_from_this();
}

void dae::GameObject::RemoveComponent(BaseComponent* pComp)
{
	auto comp = find(m_pComponents.begin(), m_pComponents.end(), pComp);

	if (comp == m_pComponents.end())
	{
		std::cout << "GameObject::RemoveComponent > Component is not attached to this GameObject!";
		return;
	}

	m_pComponents.erase(comp);
	pComp->m_pGameObject.reset();
}

std::vector<dae::BaseComponent*> dae::GameObject::GetComponents() const
{
	return m_pComponents;
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_pChildren.push_back(child);

	child->SetParent(shared_from_this());
	child->m_pScene = m_pScene;

	if (m_IsInitialized)
	{
		child->Initialize();
	}
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent)
{
	m_pParentObject = parent;
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetParent()
{
	return m_pParentObject;
}

void dae::GameObject::SetActive(bool active)
{
	if (m_IsActive != active)
	{
		m_IsActive = active;

		for (auto pComp : m_pComponents)
		{
			pComp->SetActive(active);
		}
	}
}

bool dae::GameObject::GetActive() const
{
	return m_IsActive;
}

void dae::GameObject::Initialize()
{
	if (m_IsInitialized)
	{
		return;
	}

	for (auto pComp : m_pComponents)
	{
		pComp->Initialize();
	}

	for (auto pChild : m_pChildren)
	{
		for (auto pChildComp : pChild->GetComponents())
		{
			if (pChildComp->GetActive())
			{
				pChildComp->Initialize();
			}
		}
	}

	m_IsInitialized = true;
}

void dae::GameObject::Update()
{
	for (auto pComp : m_pComponents)
	{
		if (pComp->GetActive())
		{
			if (!pComp->m_IsInitialized)
			{
				pComp->Initialize();
				pComp->m_IsInitialized = true;
			}

			pComp->Update();
		}
	}

	for (auto pChild : m_pChildren)
	{
		for (auto pChildComp : pChild->GetComponents())
		{
			if (pChildComp->GetActive())
			{
				if (!pChildComp->m_IsInitialized)
				{
					pChildComp->Initialize();
					pChildComp->m_IsInitialized = true;
				}

				pChildComp->Update();
			}
		}
	}
}

void dae::GameObject::Render() const
{
	for (auto pComp : m_pComponents)
	{
		pComp->Render();
	}

	for (auto pChild : m_pChildren)
	{
		for (auto pChildComp : pChild->GetComponents())
		{
			pChildComp->Render();
		}
	}

}

void dae::GameObject::Destroy()
{
	for (auto pComp : m_pComponents)
	{
		pComp->Destroy();
	}
}

void dae::GameObject::DestroyObject()
{
	delete m_pTransform;

	for (auto comps : m_pComponents)
	{
		delete comps;
	}
}



