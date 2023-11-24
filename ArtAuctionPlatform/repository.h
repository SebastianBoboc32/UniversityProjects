#pragma once

#include "item.h"
#include <fstream>

class Repository {
private:
	std::vector<User>users;
	std::vector<Item>items;
	std::string users_file;
	std::string items_file;

public:
	Repository(const std::string&, const std::string&);
	void add_item(const std::string&,const std::string&,const int&);
	std::vector<Item>& get_all_items();
	std::vector<User>& get_all_users();
	void modify_an_item(const int&,const int&,const int&);
	void read_from_file();
	std::vector<std::string> get_all_categories();
	void write_to_file();
};