#pragma once
#include <functional>

namespace dae
{
	class Listener
	{
		friend class Event;
	public:
		Listener();

		void SetNotifyFunction(std::function<void()> notifyFunc);

		void Notify() const;

		size_t GetListenerId() const;
		bool CompareId(const Listener& listener);

		void StopListening();

		// variable
		Event* m_pEvent;

	private:
		int m_currId;
		static int m_idCounter;

		std::function<void()> m_NotifyFunction;
	};
}