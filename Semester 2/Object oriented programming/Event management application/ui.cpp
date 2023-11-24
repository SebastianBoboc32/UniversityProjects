#pragma once
#include "admin.h"
#include "user.h"
#include "repo.h"
#include "dynamicarray.h"
#include "event.h"
#include <iostream>
#include <vector>
#include "ui.h"
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <shellapi.h>
#include <limits>
#include <ios>
#include <algorithm>
#include <fstream>
#include "validator.h"
#include "custom_errors.h"
#include "csv_file_writer.h"
#include "file_writer.h"
#include <assert.h>

#define UNICODE
#define _UNICODE

UI::UI(Repo<Event>data, Administrator admin, User user,const std::string&file_name) :Data(data), Admin(admin), 
user(user), access_mode{ "" }, current_index{ 0 }, entities_file{ file_name } {
	
}
void UI::add_element(const Event& event) {
	this->Admin.add_element(event);
}
void UI::delete_element(int index) {
	this->Admin.delete_element(index);
	

}

void UI::read_from_file() {
	std::ifstream read(entities_file);
	Event read_ev;
	while (read >> read_ev)
	 {
		user.add_element(read_ev);
		Admin.add_element(read_ev);
		Data.add_element(read_ev);
	}
	read.close();
}
void UI::write_to_file() {
	std::ofstream write(entities_file);
	for (int i = 0;i<Data.get_size();++i)
		write << Data[i];
	write.close();
}
void UI::update_event(int index, const Event& updated_event) {
	this->Admin.update_event(index, updated_event);
}
void UI::print_all() {
	for (int i = 0; i < this->Data.get_size(); ++i)
		std::cout << this->Data[i].str();
}

bool cmp(const Event& ev1, const Event& ev2) {
	return ev1 < ev2;
}

std::vector<Event> UI::sort_based_on_month(std::string month) {
	std::vector<Event> output = this->user.show_based_on_month(month);
	std::sort(output.begin(), output.end(), cmp);
	return output;
}

void UI::add_to_user_list(const Event& event) {
	this->user.add_to_my_list(event);
}
void UI::delete_from_user_list(int index) {
	this->user.remove_from_my_list(index);
}
UI::~UI() {
	this->Admin.~Administrator();
	this->user.~User();
	this->Data.~Repo();
}

Administrator  UI::ADMIN() {
	return this->Admin;
}

User  UI::USER() {
	return this->user;
}

bool validate(std::string date_time) {
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


bool validate_a_number_as_string(std::string number) {
	for (int i = 0; i < number.size(); ++i)
		if (!strchr("0123456789", number[i]))
			return false;
	return true;
}

void UI::menu() {

	EventValidator event_validator;
	bool continue_program = true;
	FileWriter* file_writer = nullptr;
	while (continue_program) {
		std::cout << "Select a mode or exit:\n";
		std::cout << "1.Admin\n";
		std::cout << "2.User\n";
		std::cout << "0.Exit\n";
		int option;
		std::string optionStr;
		std::cout << ">";
		std::getline(std::cin, optionStr);
		try {
			std::stringstream optionStream(optionStr);
			optionStream.exceptions(std::ios_base::failbit); 
			optionStream >> option;
		}
		catch (const std::ios_base::failure& e) {
			std::cout << "It's not a number\n";
		}
		if (!option)continue_program = false;
		else if (option == 1) {
			bool continue_admin = true;
			while (continue_admin) {
				std::cout << "\n\n";
				std::cout << "Select an option:\n";
				std::cout << "1.Add an event to the repo\n";
				std::cout << "2.Update an event from the repo\n";
				std::cout << "3.Delete an event from the repo\n";
				std::cout << "4.Display all events\n";
				std::cout << "5.Go back to main menu\n";
				std::cout << "0.Exit\n";
				std::cout << "\n\n";
				int admin_option;
				std::cout << ">";
				std::string admin_option_str;
				std::getline(std::cin, admin_option_str);
				admin_option = std::stoi(admin_option_str);

				if (admin_option == 1) {
					Event to_be_added;
					std::cout << "Enter an event with the attributes in the following order:Number of people,link,date&time,title,description\n";
					std::cin >> to_be_added;
					try {
						event_validator.validate_event(to_be_added);
						try {
							user.add_element(to_be_added);
							this->add_element(to_be_added);
							this->Data.add_element(to_be_added);
							this->write_to_file();
						}
						catch (const RepoError& Re) {
							std::wcout << Re.what();
						}
					}
					catch (const ValueError& ve) {
						std::cout << ve.what();
					}

				}
				else if (admin_option == 4) {
					for (int i = 0; i < this->Data.get_size(); ++i)
						std::cout << this->Data[i].str();
				}
				else if (admin_option == 5) {
					continue_admin = false;
				}
				else if (admin_option == 0) {
					continue_admin = 0;
					continue_program = false;
				}
				else if (admin_option == 2) {

					int index;
					std::string type_of_change;
					std::cout << "Select the index where you'd like to update:\n";
					std::cout << ">";
					std::string index_as_str;
					std::getline(std::cin, index_as_str);
					index = std::stoi(index_as_str);
					if (index < 0 || index >= this->Admin.Data().get_size()) {
						std::cout << "Invalid index try again!\n";
					}
					else {
						Event e1 = this->Data[index];
						std::cout << "What you'd like to change at that index?\n";
						std::cout << ">";
						std::getline(std::cin, type_of_change);
						if (type_of_change == "title") {
							std::cout << "Select a new title\n";
							std::string new_title;
							std::getline(std::cin, new_title);
							this->Data.update_event(index, Event(e1.get_number_of_people(),
								e1.get_link(), e1.get_date_and_time(), new_title, e1.get_description()));
							this->user.update_event(index, Event(e1.get_number_of_people(),
								e1.get_link(), e1.get_date_and_time(), new_title, e1.get_description()));
							this->Admin.update_event(index, Event(e1.get_number_of_people(),
								e1.get_link(), e1.get_date_and_time(), new_title, e1.get_description()));
							this->write_to_file();
						}
						else if (type_of_change == "description") {
							std::cout << "Select a new description\n";
							std::string new_description;
							std::getline(std::cin, new_description);
							this->Data.update_event(index, Event(e1.get_number_of_people(),
								e1.get_link(), e1.get_date_and_time(), e1.get_title(), new_description));
							this->user.update_event(index, Event(e1.get_number_of_people(),
								e1.get_link(), e1.get_date_and_time(), e1.get_title(), new_description));
							this->Admin.update_event(index, Event(e1.get_number_of_people(),
								e1.get_link(), e1.get_date_and_time(), e1.get_title(), new_description));
							this->write_to_file();
						}
						else if (type_of_change == "number of people") {
							std::cout << "Select a new number of people\n";
							std::string new_number_of_people_str;
							std::getline(std::cin, new_number_of_people_str);
							if (!validate_a_number_as_string(new_number_of_people_str)) {
								std::cout << "Not a number,try again!\n";
							}
							else {
								int new_number_of_people = std::stoi(new_number_of_people_str);
								this->Data.update_event(index, Event(new_number_of_people,
									e1.get_link(), e1.get_date_and_time(), e1.get_title(), e1.get_description()));
								this->user.update_event(index, Event(new_number_of_people,
									e1.get_link(), e1.get_date_and_time(), e1.get_title(), e1.get_description()));
								this->Admin.update_event(index, Event(new_number_of_people,
									e1.get_link(), e1.get_date_and_time(), e1.get_title(), e1.get_description()));
								this->write_to_file();
							}
						}
						else if (type_of_change == "date and time") {
							std::cout << "Select a new date and time,format must be DD-MM-YYYY hh:mm \n";
							std::string new_date_and_time;
							std::getline(std::cin, new_date_and_time);
							if (!validate(new_date_and_time)) {
								std::cout << "Invalid date/time,try again!\n";
							}
							else {
								this->Data.update_event(index, Event(e1.get_number_of_people(),
									e1.get_link(), new_date_and_time, e1.get_title(), e1.get_description()));
								this->user.update_event(index, Event(e1.get_number_of_people(),
									e1.get_link(), new_date_and_time, e1.get_title(), e1.get_description()));
								this->Admin.update_event(index, Event(e1.get_number_of_people(),
									e1.get_link(), new_date_and_time, e1.get_title(), e1.get_description()));
								this->write_to_file();
							}
						}
						else if (type_of_change == "link") {
							std::cout << "Select a new link\n";
							std::string new_link;
							std::getline(std::cin, new_link);
							this->Data.update_event(index, Event(e1.get_number_of_people(),
								new_link, e1.get_date_and_time(), e1.get_title(), e1.get_description()));
							this->user.update_event(index, Event(e1.get_number_of_people(),
								new_link, e1.get_date_and_time(), e1.get_title(), e1.get_description()));
							this->Admin.update_event(index, Event(e1.get_number_of_people(),
								new_link, e1.get_date_and_time(), e1.get_title(), e1.get_description()));
							this->write_to_file();
						}
						else {
							std::cout << "Invalid request\n";
						}

					}

				}
				else if (admin_option == 3) {
					int index;
					std::cout << "Select the index where to delete\n";
					std::cout << ">";
					std::string index_as_str;
					std::getline(std::cin, index_as_str);
					index = std::stoi(index_as_str);
					if (index >= 0 && index < this->Data.get_size()) {
						this->Data.delete_element(index);
						this->Admin.delete_element(index);
						this->user.delete_element(index);
						this->write_to_file();
					}
					else {
						std::cout << "Invalid index try again\n";
					}


				}
				else {
					std::cout << "Invalid option,try again!\n";
				}
			}
		}
		else if (option == 2) {
			bool selected_file = false;
			while (!selected_file) {
				std::cout << "Select a type of file between CSV and HTML for storing your list\n";
				std::string option_for_storing;
				std::getline(std::cin, option_for_storing);
				if (option_for_storing == "HTML") {
					file_writer = new HTMLFileWriter("my_list.html");
					selected_file = true;
				}
				else if (option_for_storing == "CSV") {
					file_writer = new CSVFileWriter("my_list.csv");
					assert(file_writer->get_file_name() == "my_list.csv");
					selected_file = true;
				}
				else std::cout << "Invalid file type,try again\n";
			}
			bool continue_user = true;
				while (continue_user) {
					Repo<Event> output_for_file = user.display_my_list();
					if (output_for_file.get_size() != 0) {
						std::ofstream file("my_list.csv", std::ofstream::out | std::ofstream::trunc);
						file.close();
						std::ofstream file1("my_list.html", std::ofstream::out | std::ofstream::trunc);
						file1.close();
						file_writer->write_to_file(output_for_file);
					}
					std::cout << "\n\n";
					std::cout << "1. Display all my events\n";
					std::cout << "2. See the events in a specified month\n";
					std::cout << "3. Remove from my list\n";
					std::cout << "4. Go back to main menu\n";
					std::cout << "5.Open your list in the browser/excel(depending on the file type you chose)\n";
					std::cout << "0. Exit\n";
					std::cout << "\n\n";
					int users_option;
					std::string users_option_str;
					std::getline(std::cin, users_option_str);
					std::stringstream users_option_stream(users_option_str);
					users_option_stream >> users_option;
					if (users_option == 3) {
						std::cout << "Select the index of the event to delete\n";
						int index_of_del;
						std::string index_of_del_str;
						std::getline(std::cin, index_of_del_str);
						if (!validate_a_number_as_string(index_of_del_str))
							std::cout << "Not a number,try again!\n";
						else {
							//std::cin.ignore();
							index_of_del = std::stoi(index_of_del_str);
							if (index_of_del < 0 || index_of_del >= this->user.My_List().get_size())
								std::cout << "Invalid index,try again";
							else {
								this->user.remove_from_my_list(index_of_del);
								this->Data = this->user.Data();
								this->Admin = Administrator(this->Data);
							}
						}
					}
						else if (users_option == 1) {
							Repo<Event>output_my_list = this->user.display_my_list();
							if (output_my_list.get_size() == 0)
								std::cout << "There are no events in your list\n";
							else
								for (int i = 0; i < output_my_list.get_size(); ++i) {
									std::cout << output_my_list[i].str();
								}
						}
						else if (users_option == 5) {
							file_writer->execute_file();
						}
						else if (users_option == 4) {
							continue_user = false;
						}
						else if (users_option == 0) {
							continue_user = false;
							continue_program = false;
						}
						else if (users_option == 2) {
							std::string temp_month;
							std::cout << "Choose a month\n";
							std::getline(std::cin, temp_month);
							std::cout << temp_month;
							bool found = false;
							std::vector<std::string> Months{ "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12",""};
							for (auto const& i : Months)
								if (i == temp_month)
									found = true;
							if (!found)
								std::cout << "Invalid month \n";
							else {
								bool continue_option_2 = true;
								int current_index = 0;
								std::vector<Event>dyn_arr_event = this->user.show_based_on_month(temp_month);
								std::sort(dyn_arr_event.begin(), dyn_arr_event.end(), cmp);
								int size_of_arr_event = dyn_arr_event.size();
								while (continue_option_2) {
									if (current_index >= dyn_arr_event.size())
										current_index = 0;
									std::cout << dyn_arr_event[current_index].str();
									std::string temp_url = dyn_arr_event[current_index].get_link();
									ShellExecuteA(NULL, "open", temp_url.c_str(), NULL, NULL, SW_SHOWNORMAL);
									std::cout << "\n\n";
									std::cout << "1. Add to my list\n";
									std::cout << "2. Ignore\n";
									std::cout << "3. Exit\n";
									std::cout << "\n\n";
									int user_menu_token;
									std::string user_menu_token_str;
									std::getline(std::cin, user_menu_token_str);
									std::stringstream user_menu_token_stream(user_menu_token_str);
									user_menu_token_stream >> user_menu_token;
									if (user_menu_token == 1) {
										try {
											this->user.add_to_my_list(dyn_arr_event[current_index]);
											this->Data = this->user.Data();
											this->Admin = Administrator(this->Data);
										}
										catch (const RepoError& e) {
											std::cout << "Event already added";
										}
									}
									else if (user_menu_token == 3)continue_option_2 = false;
									else if (user_menu_token != 2)std::cout << "Invalid command,try again!\n";

									current_index++;
								}
							}
						}
						else {
							std::cout << "Invalid option,try again! \n";
						}
				}

		}
				else std::cout << "Invalid option,try again!";
	}

}

int main() {
	Repo<Event>repo(100);
	User user(repo);
	Administrator admin(repo);
	UI user_interface(repo, admin, user,"entities.txt");
	user_interface.read_from_file();
	user_interface.menu();
	system("pause");
	return 0;
}



