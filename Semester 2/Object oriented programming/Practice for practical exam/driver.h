#pragma once
#include <iostream>
#include <string>
#include <sstream>

class Driver {
private:
	std::string name;
	std::pair<double, double>current_location;
	int score;
	int bonus_points;
public:
	Driver();
	Driver(const std::string& name, const double& first, const double& second, const int& sc);
	std::string get_name()const;
	std::pair<double, double>get_current_location()const;
	int get_score()const;
	int get_bonus_points()const;
	void raise_bonus_points();
	void raise_score();
	friend std::istream& operator >>(std::istream& is, Driver& drv);
	friend std::ostream& operator <<(std::ostream& os, const Driver& drv);
};