#include <iostream>
#include "user.h"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <numeric>

User::User() : data{ 100 }, my_list{ 100 } {

}

User::User(const Repo<Event>& repo) :data(repo), my_list{ 100 } {

}

std::vector<Event> User::show_based_on_month(const std::string month) {
	if (month == "") {
		return this->Data().return_data();
	}else {
		bool found = false;
		std::vector<std::string> Months{ "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };
		for (auto const& i : Months)
			if (i == month)
				found = true;
		if (!found)
			throw std::invalid_argument("The input is not a valid month");
		else {
			std::vector<Event> result;
			//result.reserve(this->Data().return_data().capacity());
			std::vector<Event> data = this->Data().return_data();
			std::copy_if(data.begin(), data.end(),
				std::back_inserter(result), [&](Event X) { return X.get_date_and_time().substr(3, 2) == month; });
			return result;
		}
	}
}

void User::add_to_my_list(const Event& event) {
	
	std::vector<Event> temp = this->data.return_data();
	auto iterator = std::find_if(temp.begin(), temp.end(),
		[&](Event& X) {return X == event; });
	if (iterator != temp.end()) {
		int i =  iterator- temp.begin();
		int nr_people = this->data[i].get_number_of_people();
		++nr_people;
		std::string name = this->data[i].get_title();
		std::string link = this->data[i].get_link();
		std::string desc = this->data[i].get_description();
		std::string date_time = this->data[i].get_date_and_time();
		this->data.update_event(i, Event(nr_people, link, date_time, name, desc));
		this->my_list.add_element(Event(nr_people, link, date_time, name, desc));
	}

}

Repo<Event> User:: display_my_list() {
	return this->my_list;
}

void User::remove_from_my_list(int index) {

	Event target_event = this->my_list[index];
	std::string target_name = target_event.get_title();
	std::string target_link = target_event.get_link();
	std::string target_desc = target_event.get_description();
	std::string target_date_time = target_event.get_date_and_time();

	std::vector<Event> temp = this->data.return_data();
	auto iterator = std::find_if(temp.begin(), temp.end(),
		[&](Event X) {return X == target_event; });
	if (iterator != temp.end()) {
		int i = iterator - temp.begin();
		int nr_people = this->data[i].get_number_of_people();
		--nr_people;
		this->data.update_event(i, Event(nr_people, target_link, target_date_time, target_name, target_desc));
	}
	this->my_list.delete_element(index);
}
User::~User() {
	this->data.~Repo();
	this->my_list.~Repo();
}

int User::data_size() {
	return this->data.get_size();
}

Repo<Event> User::Data() {
	return this->data;
}

Repo<Event> User::My_List() {
	return this->my_list;
}

void User::add_element(const Event& event) {
	this->data.add_element(event);
}

void User::delete_element(int index) {
	this->data.delete_element(index);
}
void User::update_event(int index, const Event& event) {
	this->data.update_event(index, event);
}