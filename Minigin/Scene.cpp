#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

dae::Scene::Scene(const std::string& name)
	: m_name(name)
{
	
}

void dae::Scene::Add(const std::shared_ptr<SceneObject>&object)
{
	m_objects.push_back(object);
}

void dae::Scene::Initialize()
{
	for (auto& object : m_objects)
	{
		object->Initialize();
	}
}

void dae::Scene::Update(float deltaTime)
{
	for (auto& object : m_objects)
	{
		object->Update(deltaTime);
	}
}

void dae::Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void dae::Scene::SetName(const std::string& name)
{
	m_name = name;
}