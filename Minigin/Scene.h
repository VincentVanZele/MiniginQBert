#pragma once
#include "SceneManager.h"
#include "SceneObject.h"

namespace dae
{
	class GameObject;
	class Scene 
	{			
	public:
		explicit Scene(const std::string& name);
		virtual ~Scene() = default;

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		virtual void Initialize() = 0;
		virtual void Update();
		virtual void Render() const;

		void Add(const std::shared_ptr<GameObject>& object);

		void SetName(const std::string& name);
		std::string GetName() const
		{
			return m_name;
		};

		void SetInitialized(bool init);
		bool GetInitialized() const;
	protected:
		bool m_IsInitialized;

	private:
		std::string m_name{};
		std::vector<std::shared_ptr<GameObject>> m_objects{};

		static unsigned int idCounter;
	};

}
