#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (BaseComponent* pComp : m_pComponents)
	{
		if (pComp != nullptr)
		{
			delete(pComp);
			pComp = nullptr;
		}
	}
};

void dae::GameObject::Initialize()
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Initialize();
	}
}

void dae::GameObject::Update(float deltaTime)
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Render();
	}

	if (m_pTexture)
	{
		const auto& pos = m_transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos._x, pos._y);
	}

}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

dae::Float3 dae::GameObject::GetPosition() const
{
	return m_transform.GetPosition();
}

void dae::GameObject::AddComponent(BaseComponent* pComp)
{
	for (BaseComponent* component : m_pComponents)
	{
		if (component == pComp)
		{
			std::cout << "Already has this component\n";
			return;
		}
	}

	m_pComponents.push_back(pComp);
	pComp->m_pGameObject = this;

}

void dae::GameObject::RemoveComponent(BaseComponent* pComp)
{
	const auto it = find(m_pComponents.begin(), m_pComponents.end(), pComp);

	if (it == m_pComponents.end())
	{
		std::cout << "No such Component\n";
		return;
	}

	m_pComponents.erase(it);
	pComp->m_pGameObject = nullptr;
}
