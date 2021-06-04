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

void dae::SceneManager::Update() const 
{
	m_pActiveScene->Update();
}

void dae::SceneManager::Render() const 
{
	m_pActiveScene->Render();
}

void dae::SceneManager::Destroy()
{

}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> scene)
{
	m_pScenes.push_back(scene);
}

void dae::SceneManager::SetActiveScene(const std::string& sceneName)
{
	auto pScene = GetScene(sceneName);
	if (pScene != nullptr)
	{
		m_pActiveScene = pScene;
	}
	else
		std::cout << "Invalid Scene : " << sceneName << '\n';
}

void dae::SceneManager::DeleteScene(const std::string& sceneName)
{
	for (int i{ 0 }; i < m_pScenes.size(); i++)
	{
		if(m_pScenes[i]->GetName() == sceneName)
		{
			m_pScenes.erase(m_pScenes.begin()+i);
		}
	}
}

void dae::SceneManager::SetActiveScene(std::shared_ptr<Scene> pScene)
{
	m_pActiveScene = pScene;
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(const std::string& name) const
{
	for (auto pScene : m_pScenes)
	{
		if (pScene->GetName() == name)
		{
			return pScene;
		}
	}

	return nullptr;
}

