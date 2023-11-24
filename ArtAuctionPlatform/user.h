#pragma once
#include <iostream>
#include <string>
#include <sstream>

class User {
private:
	std::string name;
	int id;
	std::string type;
public:
	User();
	User(const std::string&, const int&, const std::string&);
	std::string get_name()const;
	int get_id()const;
	std::string get_type()const;
	friend std::istream& operator >>(std::istream&,User&);
};