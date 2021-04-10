#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"

#include <string>
#include <memory>
#include <vector>

namespace dae
{
	class BaseComponent;
	class Texture2D;
	
	class GameObject final : public SceneObject
	{
	public:
		GameObject() = default;
		virtual ~GameObject();
		
		GameObject(const GameObject & other) = delete;
		GameObject(GameObject && other) = delete;
		GameObject& operator=(const GameObject & other) = delete;
		GameObject& operator=(GameObject && other) = delete;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		Float3 GetPosition() const;

		void AddComponent(BaseComponent* pComp);
		void RemoveComponent(BaseComponent* pComp);

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

	private:
		Transform m_transform{};

		std::shared_ptr<Texture2D> m_pTexture{};
		std::vector<BaseComponent*> m_pComponents{};
	};
}
