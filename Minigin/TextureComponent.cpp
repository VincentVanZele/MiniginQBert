#include "MiniginPCH.h"
#include "TextureComponent.h"

#include "Structs.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Renderer.h"

dae::TextureComponent::TextureComponent()
	: BaseComponent()
	, m_pTexture2D(nullptr)
{
}

void dae::TextureComponent::Render()
{
	Float2 pos{ GetGameObject()->GetTransform()->GetPosition() };
	Renderer::GetInstance().RenderTexture(*m_pTexture2D, pos._x, pos._y);
}

dae::Texture2D& dae::TextureComponent::GetTexture() const
{
	return *m_pTexture2D;
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture2D = pTexture;
}
