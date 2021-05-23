#pragma once
#include "BaseComponent.h"
#include "Structs.h"

namespace dae
{
	class GameObject;
	
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent();

		std::shared_ptr<GameObject> GetChildObject() const { return m_pChild; }
		void SetChildObject(std::shared_ptr<GameObject> pGO);

		void Translate(const Float2& pos);
		void Rotate(float rot);
		void Scale(const Float2& sca);

		void SetPosition(Float2 pos);
		Float2 GetPosition() const;
		void SetObjectPosition(Float2 pos);
		Float2 GetObjectPosition() const;

		void SetRotation(float rot);
		float GetRotation() const;
		void SetObjectRotation(float rot);
		float GetObjectRotation() const;

		void SetScale(Float2 sca);
		Float2 GetScale() const;
		void SetObjectScale(Float2 sca);
		Float2 GetObjectScale() const;

	private:
		std::shared_ptr<GameObject> m_pChild;

		Float2 m_Position, m_Scale;
		float m_Rotation;
	};
}

