#pragma once
#include "Observer.h"
#include <vector>

class Subject
{
public:
	void AddObserver(Observer* observer)
	{
		m_pObservers.push_back(observer);
	}

	void RemoveObserver(Observer* observer)
	{
		auto it = std::find(m_pObservers.begin(), m_pObservers.end(), observer);
		if (it != m_pObservers.end())
		{
			m_pObservers[it - m_pObservers.begin()] = m_pObservers.back();
			m_pObservers.pop_back();
		}
	}

protected:
	void Notify(Event event)
	{
		for (auto it = m_pObservers.begin(); it != m_pObservers.end(); ++it)
		{
			(*it)->OnNotify(event);
		}
	}

private:
	std::vector<Observer*> m_pObservers;
};
