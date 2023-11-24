#pragma once
#include <iostream>
#include <string>
#include "file_writer.h"
#include <windows.h>
#include <shellapi.h>
#include <limits>
#include <ios>
#include <fstream>

class CSVFileWriter :public FileWriter {
public:
	CSVFileWriter(const std::string&);
	void write_to_file( const Repo<Event>&)const override;
	void execute_file() const override;
};