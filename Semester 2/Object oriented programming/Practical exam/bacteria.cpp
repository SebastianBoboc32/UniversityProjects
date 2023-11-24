#include "bacteria.h"

Bacterium::Bacterium():name(""),species(""),size("")
{
}

Bacterium::Bacterium(const std::string& name, const std::string& species, const std::string& size,std::vector<std::string>
&dis):name(name),species(species),size(size),diseases(dis)
{
}

std::string Bacterium::get_name() const
{
    return name;
}

std::string Bacterium::get_species() const
{
    return species;
}

std::string Bacterium::get_size() const
{
    return size;
}

std::vector<std::string> Bacterium::get_diseases()const
{
    return diseases;
}

void Bacterium::add_disease(const std::string&ds)
{
    diseases.push_back(ds);
}

void Bacterium::set_name(const std::string&new_name)
{
    name = new_name;
}

void Bacterium::set_species(const std::string&spc)
{
    species = spc;
}

void Bacterium::set_diseases(std::vector<std::string>& dss)
{
    diseases = dss;
}

void Bacterium::set_size(const std::string&new_val)
{
    size = new_val;
}

bool Bacterium::operator>(const Bacterium& other) const
{
    return name > other.get_name();
}

bool Bacterium::operator<(const Bacterium& other) const
{
    return name < other.get_name();
}

std::string Bacterium::to_str() const
{
    std::string result;
    result += "Name: " + name + " ";
    result += "Species: " + species + " ";
    result += "Size: " +size + " ";
    result += "Diseases: ";
    for (const auto& disease : diseases)
    {
        result += "- " + disease + " ";
    }
    return result;
}

std::istream& operator>>(std::istream& is, Bacterium& bct)
{
    std::string name;
    std::string species;
    std::getline(is, name);
    std::getline(is, species);
    std::string line_for_size;
    std::getline(is, line_for_size);
   // int size = std::stoi(line_for_size);
    std::string line_for_dis;
    std::vector < std::string>diseases;
    while (std::getline(is, line_for_dis)) {
        if (line_for_dis.empty())
            break;
        diseases.push_back(line_for_dis);
    }
    bct = Bacterium(name, species, line_for_size, diseases);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Bacterium& bct)
{
    os << bct.name << "\n";
    os << bct.species << "\n";
    os << bct.size << "\n";
    for (auto it : bct.diseases)
        os << it << "\n";
    os << "\n";
    return os;
}

bool Bacterium::operator==(const Bacterium& other) const
{
    // Implement the logic to compare two Bacterium objects
    // and return true if they are equal, false otherwise
    // For example:
    return (name == other.name && species == other.species && diseases == other.diseases && size == other.size);
}
