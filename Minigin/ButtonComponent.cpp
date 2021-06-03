#include "MiniginPCH.h"
#include "ButtonComponent.h"

#include "Utils.h"
#include "ServiceLocator.h"

#include "TransformComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"

#include "ResourceManager.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Event.h"
#include "Listener.h"


dae::ButtonComponent::ButtonComponent(std::shared_ptr<Texture2D> texture, float width, float height)
	: BaseComponent()
	, m_spTexture{ texture }
	, m_dimensionRect{ width,height }
{
	// event 
	listener = std::make_shared<Listener>();
	m_spClick = std::make_shared<Event>();
}


void dae::ButtonComponent::Render()
{
	Float2 position = GetTransform()->GetPosition();

	ServiceLocator::GetRenderer()->GetInstance().RenderTexture(*m_spTexture, position._x, position._y, m_dimensionRect._x, m_dimensionRect._y);
}

void dae::ButtonComponent::MouseClickedEvent()
{
	m_spClick->CallNotify();
}

void dae::ButtonComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_spTexture = texture;
}

std::shared_ptr<dae::Texture2D> dae::ButtonComponent::GetTexture() const
{
	return m_spTexture;
}

void dae::ButtonComponent::SetDimensionRect(Float2& dimension)
{
	m_dimensionRect = dimension;
}

dae::Float2 dae::ButtonComponent::GetDimensionRect() const
{
	return m_dimensionRect;
}

std::shared_ptr<dae::Event> dae::ButtonComponent::GetEvent() const
{
	return m_spClick;
}
