#pragma once
#include "driver.h"
#include <cmath>

class RoadReport {
private:
	std::string description;
	std::string reporter;
	std::pair<double, double>exact_location;
	bool validation_status;
public:
	RoadReport();
	RoadReport(const std::string& desc, const std::string& rep, const double& x, const double& y, bool valid_stat);
	float distanceFromDriver(const Driver& drv);
	std::string to_str()const;
	std::string get_description()const;
	std::string get_reporter()const;
	std::pair<double, double>get_location()const;
	bool get_valid_stat()const;
	void set_valid();
	friend std::istream& operator >>(std::istream& is, RoadReport& rrep);
	friend std::ostream& operator <<(std::ostream& os, const RoadReport& rrep);
};