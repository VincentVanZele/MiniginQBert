#pragma once
enum class Event;

namespace dae
{
	class GameObject;
	class Observer;

	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

		void RemoveAllObservers();
		void DeleteAllObservers();

		void Notify(GameObject* gameObject, Event event);

	private:
		std::vector<Observer*> m_Observers{};
	};
}
