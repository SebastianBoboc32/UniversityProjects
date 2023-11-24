#pragma once
#include <tuple>
#include "user.h"
#include <vector>
class Item {
private:
	std::string name;
	std::string category;
	int current_price;
	std::vector<std::tuple<int, std::string, int> >list_of_offers;
public:
	Item();
	Item(const std::string&,const std::string&, const int&);
	std::string get_name()const;
	void add_new_offer(const int&, const std::string&,const int&);
	std::string get_category()const;
	int get_current_price()const;
	std::vector<std::tuple<int, std::string, int> >& get_list_of_offers();
	void set_current_price(const int&);
	friend std::istream & operator >>(std::istream&, Item&);
	friend std::ostream& operator <<(std::ostream&, const Item&);
	std::string to_str()const;
};