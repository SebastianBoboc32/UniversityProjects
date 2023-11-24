#pragma once
#include "observer.h"

class Subject {
public:
	virtual void notify() = 0;
	virtual void add_observer(Observer* obs) = 0;
};