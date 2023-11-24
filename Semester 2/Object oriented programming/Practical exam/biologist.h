#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Biologist {
private:
	std::string name;
	std::vector<std::string>species_studied;
public:
	Biologist();
	Biologist(const std::string& nm, std::vector<std::string>& sp_s);
	std::string get_name()const;
	std::vector<std::string>get_species_studied()const;
	friend std::istream& operator >>(std::istream& is, Biologist& biog);
	friend std::ostream& operator <<(std::ostream& os, const Biologist& biog);
};