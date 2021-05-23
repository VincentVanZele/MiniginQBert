#include "MiniginPCH.h"
#include "TransformComponent.h"

#include "Structs.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent()
	: BaseComponent()
	, m_pChild(nullptr)

{
}

void dae::TransformComponent::SetChildObject(std::shared_ptr<GameObject> pGO)
{
	m_pChild = pGO;
}

void dae::TransformComponent::SetPosition(Float2 pos)
{
	m_Position = pos;
}

dae::Float2 dae::TransformComponent::GetPosition() const
{
	return m_Position;
}

void dae::TransformComponent::SetObjectPosition(Float2 pos)
{
	Translate(Float2(pos._x - GetObjectPosition()._x, pos._y - GetObjectPosition()._y));
}

dae::Float2 dae::TransformComponent::GetObjectPosition() const
{
	Float2 temp{};
	std::shared_ptr<GameObject> tempObj{ m_pChild };

	while (tempObj)
	{
		temp._x += tempObj->GetTransform()->GetPosition()._x;
		temp._y += tempObj->GetTransform()->GetPosition()._y;

		tempObj = tempObj->GetParent();
	}

	return temp;
}

void dae::TransformComponent::SetRotation(float rot)
{
	m_Rotation = rot;
}

float dae::TransformComponent::GetRotation() const
{
	return m_Rotation;
}

void dae::TransformComponent::SetObjectRotation(float rot)
{
	Rotate(rot - m_Rotation);
}

float dae::TransformComponent::GetObjectRotation() const
{
	float temp{};
	std::shared_ptr<GameObject> tempObj{ m_pChild };

	while (tempObj)
	{
		temp += tempObj->GetTransform()->GetRotation();

		tempObj = tempObj->GetParent();
	}

	return temp;
}

void dae::TransformComponent::SetScale(Float2 sca)
{
	m_Scale = sca;
}

dae::Float2 dae::TransformComponent::GetScale() const
{
	return m_Scale;
}

void dae::TransformComponent::SetObjectScale(Float2 sca)
{
	Scale(Float2(sca._x - m_Scale._x, sca._y - m_Scale._y));
}

dae::Float2 dae::TransformComponent::GetObjectScale() const
{
	Float2 temp{};
	std::shared_ptr<GameObject> tempObj{ m_pChild };

	while (tempObj)
	{
		temp._x *= tempObj->GetTransform()->GetScale()._x;
		temp._y *= tempObj->GetTransform()->GetScale()._y;

		tempObj = tempObj->GetParent();
	}

	return temp;
}

void dae::TransformComponent::Translate(const Float2& pos)
{
	m_Position._x += pos._x;
	m_Position._y += pos._y;
}

void dae::TransformComponent::Rotate(float rot)
{
	m_Rotation += rot;
}

void dae::TransformComponent::Scale(const Float2& sca)
{
	m_Scale._x += sca._x;
	m_Scale._y += sca._y;
}