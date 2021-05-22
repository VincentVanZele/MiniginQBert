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
		void Update(float deltaTime) const;
		void Render() const;
		void Destroy();

		Scene* CreateScene(const std::string& name);
		
		void SetActiveScene(const std::string& sceneName);
		void SetActiveScene(Scene* pScene);
		
		Scene* GetScene(const std::string& sceneName) const;
		Scene* GetActiveScene() const
		{
			return m_pActiveScene;
		}

	private:
		Scene* m_pActiveScene = nullptr;
		std::vector<Scene*> m_pScenes{};
	};
}
