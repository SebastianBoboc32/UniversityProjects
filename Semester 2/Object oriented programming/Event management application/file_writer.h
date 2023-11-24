#pragma once
#include <iostream>
#include <string>
#include "event.h"
#include "repo.h"
#include <fstream>

class FileWriter {
protected:
	std::string file_name;
public:
	FileWriter(const std::string&);
	void virtual write_to_file(const Repo<Event>&)const = 0;
	std::string get_file_name();
	void virtual execute_file() const = 0;
};