#include <iostream>
#include <string>
#include "file_writer.h"

FileWriter::FileWriter(const std::string& file) :file_name(file){

}

std::string FileWriter::get_file_name() {
	return file_name;
}