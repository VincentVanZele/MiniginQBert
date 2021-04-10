#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

dae::SceneManager::SceneManager()
	: m_pActiveScene{ nullptr }
{}

void dae::SceneManager::Initialize()
{
	for (auto& scene : m_pScenes)
	{
		scene->Initialize();
	}
}

void dae::SceneManager::Update(float deltaTime) const 
{
	m_pActiveScene->Update(deltaTime);
}

void dae::SceneManager::Render() const 
{
	m_pActiveScene->Render();
}

void dae::SceneManager::Destroy()
{
	for (Scene* pScene : m_pScenes)
	{
		delete pScene;
		pScene = nullptr;
	}
	m_pActiveScene = nullptr;
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = new Scene(name);
	m_pScenes.push_back(scene);
	return scene;
}

void dae::SceneManager::SetActiveScene(const std::string& sceneName)
{
	Scene* pScene = GetScene(sceneName);
	if (pScene != nullptr)
	{
		m_pActiveScene = pScene;
	}
	else
		std::cout << "Invalid Scene : " << sceneName << '\n';
}

void dae::SceneManager::SetActiveScene(Scene* pScene)
{
	m_pActiveScene = pScene;
}

dae::Scene* dae::SceneManager::GetScene(const std::string& name) const
{
	for (Scene* pScene : m_pScenes)
	{
		if (pScene->GetName() == name)
		{
			return pScene;
		}
	}

	return nullptr;
}

