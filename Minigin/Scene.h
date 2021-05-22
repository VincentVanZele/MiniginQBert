#pragma once
#include "SceneManager.h"

namespace dae
{
	class SceneObject;
	
	class Scene
	{
	public:
		Scene(const std::string& name);
		virtual ~Scene() = default;

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Initialize();
		void Update(float deltaTime);
		void Render() const;

		void Add(const std::shared_ptr<SceneObject>& object);

		void SetName(const std::string& name);
		std::string GetName() const
		{
			return m_name;
		}
		
		std::vector<std::shared_ptr<SceneObject>> GetSceneObjects() const
		{
			return m_objects;
		}

	private:
		std::string m_name;
		std::vector<std::shared_ptr<SceneObject>> m_objects{};
	};

}
