#include <iostream>
#include "admin.h"
#include <vector>

Administrator::Administrator() :data{ 100 } {
}
void Administrator::delete_element(int index) {
	this->data.delete_element(index);
	

}
void Administrator::add_element(Event elem) {
	this->data.add_element(elem);
}
void Administrator::update_event(int index, const Event& updated_event) {
	this->data.update_event(index, updated_event);

}
Administrator::~Administrator() {
	this->data.~Repo();
}
std::string Administrator::list_all() {
	std::vector<Event>input = this->data.return_data();
	std::string output = "";
	for (auto const& it : input) { 
		output += it.str();
		output += "\n";
	}
	return output;
}

Administrator::Administrator(const Repo<Event>& repo): data(repo) {

}

Repo<Event> Administrator::Data() {
	return this->data;
}

