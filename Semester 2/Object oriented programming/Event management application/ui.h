#pragma once
#include "admin.h"
#include "user.h"
#include "repo.h"
#include "dynamicarray.h"
#include "event.h"
#include <iostream>
#include <vector>
#include "file_writer.h"
#include "csv_file_writer.h"
#include "html_file_writer.h"

#define UNICODE
#define _UNICODE

class UI {
private:
	Repo<Event>Data;
	Administrator Admin;
	User user;
	std::string access_mode;
	int current_index;
	std::string entities_file;
public:
	UI(Repo<Event>data, Administrator admin, User user, const std::string&);
	void add_element(const Event& event);
	void delete_element(int index);
	void update_event(int index, const Event& updated_event);
	void print_all();
	std::vector<Event> sort_based_on_month(std::string month);
	void add_to_user_list(const Event& event);
	void delete_from_user_list(int index);
	~UI();
	void read_from_file();
	void write_to_file();
	Administrator ADMIN();
	User USER();
	void menu();
};
