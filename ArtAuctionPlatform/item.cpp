#include "item.h"

Item::Item() :name{ "" }, category{ "" }, current_price{ 0 }
{
    list_of_offers = std::vector < std::tuple<int, std::string, int> >();
}

Item::Item(const std::string&a, const std::string&b, const int&c):name{a},category{b},current_price{c}
{
    list_of_offers = std::vector < std::tuple<int, std::string, int> >();
}

std::string Item::get_name() const
{
    return name;
}

void Item::add_new_offer(const int&a, const std::string&b, const int&c)
{
    std::tuple<int, std::string, int> elem(a, b, c);
    list_of_offers.push_back(elem);
}

std::string Item::get_category() const
{
    return category;
}

int Item::get_current_price() const
{
    return current_price;
}

std::vector<std::tuple<int, std::string, int>>& Item::get_list_of_offers()
{
    return list_of_offers;
}

void Item::set_current_price(const int&pr)
{
    current_price = pr;
}

std::string Item::to_str() const
{
    return name + " " + category + " " + std::to_string(current_price);
}

std::istream& operator>>(std::istream& is, Item& itm)
{
    std::string line;
    std::getline(is, line);
    std::istringstream read(line);
    std::string nm, cat;
    int curr_pr;
    read >> nm >> cat >> curr_pr;
    itm.name = nm;
    itm.category = cat;
    itm.current_price = curr_pr;

    std::string offerLine;
    while (std::getline(is, offerLine)) {
        if (offerLine.empty())
            break;
        std::istringstream read_tuple(offerLine);
        int user_id, offered_sum;
        std::string date;
        read_tuple >> user_id >> date >> offered_sum;
        std::tuple<int, std::string, int> offer(user_id, date, offered_sum);
        itm.list_of_offers.push_back(offer);
    }

    return is;
}
std::ostream& operator<<(std::ostream&os, const Item&itm)
{
    os << itm.name << " " << itm.category << " " << itm.current_price << "\n";
    for (auto it : itm.list_of_offers)
        os << std::get<0>(it) << " " << std::get<1>(it) << " " << std::get<2>(it) << "\n";
    return os;
}
