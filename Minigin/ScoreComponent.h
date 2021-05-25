#pragma once
#include "BaseComponent.h"
#include "Structs.h"

namespace dae
{
	class Subject;
	class Observer;
	class ScoreObserver;
	class TextComponent;
	
	class ScoreComponent : public BaseComponent
	{
	public:
		ScoreComponent(ScoreObserver* scoreObs);
		~ScoreComponent();

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) noexcept = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update() override;
		void Render() override;
	
	private:
		int m_Score{};
		
		ScoreObserver* m_pScoreObs = nullptr;
		TextComponent* m_pTextComp = nullptr;
	};
}
