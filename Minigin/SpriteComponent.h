#pragma once
#include"BaseComponent.h"
#include "Animation.h"
#include "Structs.h"

namespace dae
{
	class Texture2D;
	class Animation;

	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent();
		
		void Update(float deltaTime) override;
		void Render() override;

		void AddAnimation(std::shared_ptr<Animation> sprite);
		void RemoveAnimation(const std::string& name);
		void RemoveAllAnimations();

		void SetActiveAnimation(const std::string& name);
		Animation& GetActiveAnimation() const;
		bool CheckActiveAnimation(const std::string& name);

		void SetAnimDeltatime(float deltaT);
		float GetAnimDeltatime() const;

		void SetFrame(int frame);

	private:
		std::vector<std::shared_ptr<Animation>> m_vSprites;
		std::shared_ptr<Animation> m_ActiveSprite;

		float m_deltaTime;
	};
}
