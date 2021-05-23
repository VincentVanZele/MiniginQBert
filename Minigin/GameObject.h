#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"

#include <string>
#include <memory>
#include <vector>
#include "Scene.h"

namespace dae
{
	class Texture2D;
	class TransformComponent;
	
	class GameObject final : public std::enable_shared_from_this<GameObject>
	{
		friend class BaseComponent;
	public:

		GameObject(const Float2& pos = { 0.f, 0.f }, float rot = 0.0f, const Float2& sca = { 1.f, 1.f });
		virtual ~GameObject();

		void Initialize();
		void Update();
		void Render() const;
		void Destroy();

		void DestroyObject();

		static std::shared_ptr<GameObject> NewGameObject();

		TransformComponent* GetTransform() const { return m_pTransform; }

		void AddComponent(BaseComponent* pComp);
		void RemoveComponent(BaseComponent* pComp);
		std::vector<BaseComponent*> GetComponents() const;

		// Template
		template <class T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (BaseComponent* component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}
			return nullptr;
		}


		void AddChild(std::shared_ptr<GameObject> child);

		void SetParent(std::shared_ptr<GameObject> parent);
		std::shared_ptr<GameObject> GetParent();

		void SetActive(bool active);
		bool GetActive() const;

	protected:
	private:
		bool m_IsInitialized = false;
		bool m_IsActive = true;

		TransformComponent* m_pTransform;
		std::vector<BaseComponent*> m_pComponents;

		std::shared_ptr<GameObject> m_pParentObject;
		Scene* m_pScene = nullptr;

		std::vector<std::shared_ptr<GameObject>> m_pChildren;
	};

}
