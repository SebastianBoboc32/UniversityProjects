#pragma once
#include "bacteria.h"
#include "biologist.h"
#include <fstream>

class Repository {
private:
	std::vector<Bacterium>bacteria;
	std::vector<Biologist>biologists;
	std::string bacteria_file;
	std::string bilogists_file;
public:
	void read_from_files();
	Repository(const std::string& file_1, const std::string& file_2);
	void write_to_file();
	void add_bacteria(const Bacterium& bct);
	int get_size_bact()const;
	int get_size_biog()const;
	std::vector<Bacterium>& get_bacteria();
	std::vector<Biologist>& get_biologists();

};