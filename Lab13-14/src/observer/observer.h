#pragma once

/*
Abstract class
update method need to be implemented by observers
*/
class Observer {
public:
	virtual void update() = 0;
};

/*
Observable or Subject - class that notify changes in it's state
Derive from this class if you want to provide notifications
*/
#include <vector>
#include <algorithm>
class Observable {
private:
	std::vector<Observer*> __observers;
public:

	void addObserver(Observer* obs) {
		this->__observers.push_back(obs);
	}

	void removeObserver(Observer* obs) {
		this->__observers.erase(std::remove(this->__observers.begin(), this->__observers.end(), obs), this->__observers.end());
	}

	void notify() {
		for (auto obs : this->__observers) {
			obs->update();
		}
	}
};