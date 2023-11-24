#pragma once
#include "biologist.h"


class Bacterium {
private:
	std::string name;
	std::string species;
	std::string size;
	std::vector<std::string>diseases;
public:
	Bacterium();
	Bacterium(const std::string& name, const std::string& species, const std::string& size,std::vector<std::string>& dis);
	std::string get_name()const;
	std::string get_species()const;
	std::string get_size()const;
	std::vector<std::string> get_diseases()const;
	void add_disease(const std::string&);
	void set_name(const std::string&);
	void set_species(const std::string&);
	bool operator==(const Bacterium& other) const;
	void set_diseases(std::vector<std::string>& dss);
	void set_size(const std::string&);
	friend std::istream& operator >>(std::istream& is, Bacterium& bct);
	friend std::ostream& operator <<(std::ostream& os, const Bacterium& bct);
	bool operator > (const Bacterium& other)const;
	bool operator < (const Bacterium& other)const;
	std::string to_str()const;
};