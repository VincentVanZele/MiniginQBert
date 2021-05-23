#pragma once
#include "SceneObject.h"
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextObject final : public SceneObject
	{
	public:
		TextObject(const std::string& text, const std::shared_ptr<Font>& font);
		virtual ~TextObject() = default;

		TextObject(const TextObject & other) = delete;
		TextObject(TextObject && other) = delete;
		TextObject& operator=(const TextObject & other) = delete;
		TextObject& operator=(TextObject && other) = delete;
		
		void Initialize() override;
		void Update() override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

	private:
		std::string m_text;
		Transform m_transform;
		
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_texture;

		bool m_dirtyFlag;
	};
}
