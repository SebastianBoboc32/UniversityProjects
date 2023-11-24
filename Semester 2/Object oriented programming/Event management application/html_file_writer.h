#pragma once
#include <iostream>
#include <string>
#include "file_writer.h"
#include <fstream>
#include <windows.h>
#include <shellapi.h>
#include <limits>
#include <ios>

class HTMLFileWriter :public FileWriter {
public:
	HTMLFileWriter(const std::string&);
	void write_to_file(const Repo<Event>&)const override;
	void execute_file() const override;
};