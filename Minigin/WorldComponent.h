#pragma once
#include "BaseComponent.h"


namespace dae
{
	class Subject;
	class Observer;

	class WorldComponent : public BaseComponent
	{
	public:
		WorldComponent();
		~WorldComponent();

		WorldComponent(const WorldComponent& other) = delete;
		WorldComponent(WorldComponent&& other) noexcept = delete;
		WorldComponent& operator=(const WorldComponent& other) = delete;
		WorldComponent& operator=(WorldComponent&& other) noexcept = delete;

		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

		void Initialize() override;
		void Update() override;
		void Render() override;

		bool m_hasChangedTile = false;
	
	private:

		Subject* m_pSubject = nullptr;		
	};
}