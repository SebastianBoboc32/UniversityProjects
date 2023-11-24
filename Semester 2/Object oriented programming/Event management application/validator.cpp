#include <iostream>
#include "validator.h"
#include <string>
#include <sstream>


bool EventValidator::validate_date_and_time(const std::string& date_time) {
	int day, month, year, hour, minute;
	char delimiter1, delimiter2, delimiter3, delimiter4;

	std::istringstream dateTimeStream(date_time);
	dateTimeStream >> day >> delimiter1 >> month >> delimiter2 >> year;
	dateTimeStream >> hour >> delimiter3 >> minute >> delimiter4;

	if (!dateTimeStream.eof()) {
		return false;
	}

	if (year < 2023 || month < 1 || month > 12 || day < 1 || day > 31 || hour < 0 || hour > 23 || minute < 0 || minute > 59) {
		return false;
	}

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31) {
		return false;
	}

	if (month == 2) {
		bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
		if (day > 29 || (day == 29 && !isLeapYear)) {
			return false;
		}
	}

	return true;

}

void EventValidator::validate_event(const Event&ev) {
	if(!validate_date_and_time(ev.get_date_and_time()))
		throw ValueError("Invalid date and time,try again!\n");
	std::string link_begin = "https://";
	size_t found = ev.get_link().find(link_begin);
	if (found == std::string::npos)
		throw ValueError("Link should start with https://\n");
}