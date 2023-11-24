#include <iostream>
#include <string>
#include "csv_file_writer.h"


CSVFileWriter::CSVFileWriter(const std::string&file):FileWriter(file) {

}
void CSVFileWriter::write_to_file( const Repo<Event>& ev)const {
	
	std::ofstream out(file_name,std::ios::app);
	for(int i = 0 ;i<ev.get_size();++i)
	out << ev[i].get_date_and_time() << "," << ev[i].get_description() << "," << ev[i].get_number_of_people() << "," << ev[i].get_title()<<"," << ev[i].get_link() << "\n";
	out.close();

}

void CSVFileWriter::execute_file() const {
	ShellExecuteA(NULL, "open", file_name.c_str(), NULL, NULL, SW_SHOWNORMAL);
}