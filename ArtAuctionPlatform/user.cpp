#include "user.h"

User::User():name{""},id{0},type{""}
{
}

User::User(const std::string&a, const int&b, const std::string&c):name{a},id{b},type{c}
{
}

std::string User::get_name() const
{
    return name;
}

int User::get_id() const
{
    return id;
}

std::string User::get_type() const
{
    return type;
}

std::istream& operator>>(std::istream&is, User&user)
{
    std::string line;
    std::getline(is, line);
    std::istringstream read(line);
    std::string nm, tp;
    int idd;
    read >> nm >> idd >> tp;
    user.id = idd;
    user.name = nm;
    user.type = tp;
    return is;
}
