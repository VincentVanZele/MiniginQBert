#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include "Transform.h"

namespace dae
{
	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(const std::shared_ptr<Font>& font, const std::string& text = "-", const Float3 color = { 255,255,255});
		
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;

		void SetColor(Float3 color);
		Float3 GetColor() const
		{
			return m_Color;
		}

		void SetText(const std::string& text);
		std::string GetText() const
		{
			return m_text;
		}
		
		void SetTextSize(unsigned int size);

	private:
		std::string m_text;
		Float3 m_Color;
		Transform m_transform;
		
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_texture;

		bool m_dirtyFlag;
	};
}
