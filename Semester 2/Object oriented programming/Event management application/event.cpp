#include <iostream>
#include "event.h"

Event::Event() : number_of_people{ 0 }, link{ "" }, date_and_time{ "" }, title{ "" }, description{ "" }
{

}

std::ostream& operator<<(std::ostream& os, const Event&ev) {
	os << ev.number_of_people << "\n";
	os << ev.link << "\n";
	os << ev.date_and_time << "\n";
	os << ev.title << "\n";
	os << ev.description << "\n";
	return os;
}
std::istream& operator>>(std::istream& is, Event& ev) {
	is >> ev.number_of_people;
	is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(is, ev.link);
	std::getline(is, ev.date_and_time);
	std::getline(is, ev.title);
	std::getline(is, ev.description);
	return is;
}

Event::Event(const int& nr_of_people, const std::string& link, const std::string& date_time,
	const std::string& title, const std::string& description) :number_of_people{ nr_of_people }, link{ link },
	date_and_time{ date_time }, title{ title }, description{ description }
{

}

Event::Event(const Event& event):date_and_time(event.date_and_time),description(event.description),
link(event.link),number_of_people(event.number_of_people),title(event.title){

}

int  Event:: get_number_of_people()const {
	return this->number_of_people;
}

std::string Event:: get_link()const {
	return this->link;
}

std::string Event::get_description()const {
	return this->description;
}

std::string Event:: get_title()const {
	return this->title;
}

std::string Event:: get_date_and_time()const {
	return this->date_and_time;
}

void Event:: set_number_of_people(const int new_nr) {
	this->number_of_people = new_nr;
}

void Event:: set_link(const std::string str) {
	this->link = str;
}

void Event:: set_description(const std::string desc) {
	this->description = desc;
}

void Event:: set_date_and_time(const std::string date_time) {
	this->date_and_time = date_time;
}

void Event:: set_title(const std::string title) {
	this->title = title;
}

std::string Event:: str()const {
	auto nr_of_people = std::to_string(this->number_of_people);
	return "\n\nTitle: " + this->title + "\nNumber of people: " + nr_of_people + "\nDescription: " + this->description
		+ "\nDate&Time: " + this->date_and_time + "\nURL: " + this->link + "\n\n";
}

Event:: ~Event() = default;

Event& Event:: operator = (const Event& event) {
	if (this == &event)
		return *this;
	this->date_and_time = event.date_and_time;
	this->description = event.description;
	this->link = event.link;
	this->number_of_people = event.number_of_people;
	this->title = event.title;
	return *this;
}

bool Event:: operator == (const Event& event) const {
	if (this->title == event.title)
		return true;
	return this->link == event.link;
}

bool Event::operator< (const Event& event)const {
	std::string date_event_1 = this->date_and_time;
	std::string date_event_2 = event.date_and_time;
	std::string day_1 = date_event_1.substr(0, 2);
	std::string day_2 = date_event_2.substr(0, 2);
	std::string month_1 = date_event_1.substr(3, 2);
	std::string month_2 = date_event_2.substr(3, 2);
	std::string year_1 = date_event_1.substr(6, 4);
	std::string year_2 = date_event_2.substr(6, 4);
	std::string hour_1 = date_event_1.substr(11, 2);
	std::string hour_2 = date_event_2.substr(11, 2);
	std::string minutes_1 = date_event_1.substr(14, 2);
	std::string minutes_2 = date_event_2.substr(14, 2);
	if (year_1 < year_2)
		return true;
	else if (year_1 == year_2 && month_1 < month_2)
		return true;
	else if (year_1 == year_2 && month_1 == month_2 && day_1 < day_2)
		return true;
	else if (year_1 == year_2 && month_1 == month_2 && day_1 == day_2 && hour_1 < hour_2)
		return true;
	else if (year_1 == year_2 && month_1 == month_2 && day_1 == day_2 && hour_1 == hour_2 && minutes_1 < minutes_2)
		return true;
	return false;
}
