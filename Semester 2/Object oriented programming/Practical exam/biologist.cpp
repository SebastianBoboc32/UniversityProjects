#include "biologist.h"

Biologist::Biologist():name("")
{
}

Biologist::Biologist(const std::string& nm, std::vector<std::string>& sp_s)
:name(nm),species_studied(sp_s){
}

std::string Biologist::get_name() const
{
    return name;
}

std::vector<std::string> Biologist::get_species_studied() const
{
    return species_studied;
}

std::istream& operator>>(std::istream& is, Biologist& biog)
{
    std::string name_line;
    std::string species_line;
    std::string species;
    std::getline(is, name_line);
    std::getline(is, species_line);
    std::vector <std::string>species_stud;
    std::istringstream read_spec(species_line);
    while (read_spec >> species)
        species_stud.push_back(species);
    biog = Biologist(name_line, species_stud);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Biologist& biog)
{
    os << biog.name << "\n";
    for (auto it : biog.species_studied)
        os << it << " ";
    return os;
}
