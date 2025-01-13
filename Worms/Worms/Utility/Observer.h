#pragma once

class Observer : public Singleton<Observer>
{
private:
	friend Singleton;
	Observer();
	~Observer();

public:
	void AddIntEvent(std::string key, IntEvent event) { intEvents[key] = event; }
	void ExcuteIntEvent(std::string key, int param) { intEvents[key](param); }

private:
	std::map<std::string, IntEvent> intEvents;

};