#include "repository.h"

void Repository::read_from_files()
{
    std::ifstream read_bio(bilogists_file);
    Biologist biol;
    while (read_bio >> biol)
        biologists.push_back(biol);
    read_bio.close();
    std::ifstream read_bact(bacteria_file);
    Bacterium bct;
    while (read_bact >> bct)
        bacteria.push_back(bct);
    read_bact.close();
}

Repository::Repository(const std::string& file_1, const std::string& file_2)
:bilogists_file(file_1),bacteria_file(file_2){
    read_from_files();
}

void Repository::write_to_file()
{
    std::ofstream write_bact(bacteria_file);
    for (auto it : bacteria)
        write_bact << it;
    write_bact.close();
}

void Repository::add_bacteria(const Bacterium& bct)
{
    bacteria.push_back(bct);
}

int Repository::get_size_bact() const
{
    return bacteria.size();
}

int Repository::get_size_biog() const
{
    return biologists.size();
}

std::vector<Bacterium>& Repository::get_bacteria()
{
    return bacteria;
}

std::vector<Biologist>& Repository::get_biologists()
{
    return biologists;
}
