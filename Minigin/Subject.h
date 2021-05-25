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

		void Notify(Event event);

		// Template
		template <class T>
		T* GetObserver()
		{
			const type_info& ti = typeid(T);
			for (Observer* obs : m_Observers)
			{
				if (obs && typeid(*obs) == ti)
					return static_cast<T*>(obs);
			}
			return nullptr;
		}

	private:
		std::vector<Observer*> m_Observers{};
	};
}
