#pragma once
#include "repository.h"
#include <algorithm>

class Service {
private:
	User user;
	Repository& repo;
public:
	Service(User&, Repository&);
	std::vector<Item> get_all_items_sorted();
	std::vector<Item> filter_by_category(const std::string&);
	void add_item(const std::string&, const std::string&, const int&);
	std::vector<std::tuple<int, std::string, int> > get_all_offers(const int&);
	std::vector<std::string> all_categories();
	void bid_for_item(const int&,const int&);
};