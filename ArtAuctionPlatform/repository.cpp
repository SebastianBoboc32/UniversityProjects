#include "repository.h"

Repository::Repository(const std::string&a, const std::string&b):users_file{a},items_file{b}
{
    read_from_file();
}

void Repository::add_item(const std::string&nm, const std::string&cat, const int&prc)
{
    Item itm1{ nm,cat,prc };
    items.push_back(itm1);
}

std::vector<Item>& Repository::get_all_items()
{
    return items;
}

std::vector<User>& Repository::get_all_users()
{
    return users;
}

void Repository::modify_an_item(const int&index, const int&offered_sum,const int& user_id)
{
    items[index].set_current_price(offered_sum);
    items[index].add_new_offer(user_id, "29.06.2023", offered_sum);
}

void Repository::read_from_file()
{
    std::ifstream read_users(users_file);
    User usr;
    while (read_users >> usr)
        users.push_back(usr);
    read_users.close();
    Item itm;
    std::ifstream read_items(items_file);
    while (read_items >> itm)
        items.push_back(itm);
    read_items.close();
}

std::vector<std::string> Repository::get_all_categories()
{
    std::vector<std::string>output = std::vector<std::string>();
    output.push_back("");
    for (auto it : items) {
        bool found = false;
        for (auto itt : output)
            if (itt == it.get_category())
                found - true;
        if (!found)
            output.push_back(it.get_category());
    }
    return output;
}

void Repository::write_to_file()
{
    std::ofstream write_items(items_file);
    for (auto it : items)
        write_items << it;
    write_items.close();
}
