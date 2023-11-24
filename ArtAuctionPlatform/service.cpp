#include "service.h"

Service::Service(User&user, Repository&repp):user{user},repo{repp}
{
}

std::vector<Item> Service::get_all_items_sorted()
{
    std::vector<Item> output = repo.get_all_items();
    std::sort(output.begin(), output.end(), [&](Item A, Item B) {
        return A.get_current_price() > B.get_current_price();
        });
    return output;
}

std::vector<Item> Service::filter_by_category(const std::string&cat)
{
    std::vector<Item> items = repo.get_all_items();
    std::vector<Item>output = std::vector<Item>();
    std::copy_if(items.begin(), items.end(), std::back_inserter(output), [&]
    (Item A) {return A.get_category() == cat; });
    return output;
}

void Service::add_item(const std::string&a, const std::string&b, const int&c)
{
    repo.add_item(a, b, c);
}

std::vector<std::tuple<int, std::string, int> > Service::get_all_offers(const int& index)
{
    std::vector < std::tuple<int, std::string, int> >output = std::vector<std::tuple<int, std::string, int> >();
    std::vector<Item> input = get_all_items_sorted();
    return input[index].get_list_of_offers();
}

std::vector<std::string> Service::all_categories()
{
    return repo.get_all_categories();
}

void Service::bid_for_item(const int&index, const int&offered_sum)
{
    repo.modify_an_item(index, offered_sum, user.get_id());
}
