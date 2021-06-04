#pragma once
#include "Singleton.h"
#include <vector>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		SceneManager();
		~SceneManager() = default;

		SceneManager(const SceneManager& other) = delete;
		SceneManager(SceneManager&& other) noexcept = delete;
		SceneManager& operator=(const SceneManager& other) = delete;
		SceneManager& operator=(SceneManager&& other) noexcept = delete;

		void Initialize();
		void Update() const;
		void Render() const;
		void Destroy();

		void AddScene(std::shared_ptr<Scene> scene);
		void DeleteScene(const std::string& name);
		std::shared_ptr<Scene> CreateScene(const std::string& name);
		
		void SetActiveScene(const std::string& sceneName);
		void SetActiveScene(std::shared_ptr<Scene> pScene);
		
		std::shared_ptr<Scene> GetScene(const std::string& sceneName) const;
		std::shared_ptr<Scene> GetActiveScene() const
		{
			return m_pActiveScene;
		}

	private:
		std::shared_ptr<Scene> m_pActiveScene = nullptr;
		std::vector<std::shared_ptr<Scene>> m_pScenes{};
	};
}
