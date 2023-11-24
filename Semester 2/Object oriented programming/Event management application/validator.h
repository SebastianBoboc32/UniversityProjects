#pragma once
#include <iostream>
#include "event.h"
#include "custom_errors.h"

class EventValidator {
public:
	void validate_event(const Event&);
	bool validate_date_and_time(const std::string&);
};