#include <iostream>
#include <string>
#include "file_writer.h"
#include <fstream>
#include "html_file_writer.h"

HTMLFileWriter::HTMLFileWriter(const std::string&file_name):FileWriter(file_name) {

}

void HTMLFileWriter::write_to_file(const Repo<Event>& ev)const{
    std::ofstream out(file_name, std::ios::app);
    out << "<!DOCTYPE html>\n";
    out << "<html>\n";
    out << "<head>\n";
    out << "<title>Event</title>\n";
    out << "</head>\n";
    out << " <body>\n";
    out << "<table border = \"1\">\n";
    out << "<tr>\n";
    out << "<td>Date&time</td>\n";
    out << "<td>Description</td>\n";
    out << "<td>Number of people</td>\n";
    out << "<td>Title</td>\n";
    out << "<td>Link</td>\n";
    out << "</tr>\n";
    for (int i = 0; i < ev.get_size(); ++i) {
        out << "<tr>\n";
        out << "<td>" << ev[i].get_date_and_time() << "</td>\n";
        out << "<td>" << ev[i].get_description() << "</td>\n";
        out << "<td>" << ev[i].get_number_of_people() << "</td>\n";
        out << "<td>" << ev[i].get_title() << "</td>\n";
        out << "<td> <a href = " << ev[i].get_link() << ">Link</a></td>\n";
        out << "</tr>\n";
    }
    out << "</table>\n";
    out << "</body>\n";
    out << "</html>\n";
    out.close();
}

void HTMLFileWriter::execute_file() const {
    ShellExecuteA(NULL, "open", file_name.c_str(), NULL, NULL, SW_SHOWNORMAL);
}