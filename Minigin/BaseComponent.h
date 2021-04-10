#pragma once
#include "GameObject.h"

namespace dae
{
	class GameObject;

	class BaseComponent
	{
		friend class GameObject;
	public:
		BaseComponent();
		virtual ~BaseComponent() = default;
		
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		void SetGameObject(GameObject* gO)
		{
			m_pGameObject = gO;
		}
		GameObject* GetGameObject() const
		{
			return m_pGameObject;
		}

	protected:
		GameObject* m_pGameObject;
	};
}


