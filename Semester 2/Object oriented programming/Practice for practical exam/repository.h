#pragma once
#include "road_report.h"
#include "subject.h"
#include <vector>
#include <fstream>

class Repository:public Subject {
private:
	std::string drivers_file;
	std::string messages_file;
	std::string reports_file;
	std::vector<Observer*>observers;
	std::vector<std::string>messages;
	std::vector<RoadReport>reports;
	std::vector<Driver>drivers;
	void read_from_files();
	void write_to_files();
public:
	Repository(const std::string& df, const std::string& rf, const std::string& mf);
	void add_observer(Observer* obs)override;
	void add_a_message(const std::string& msg);
	void add_a_report(const RoadReport& repp);
	void raise_drivers_score(const int& index);
	void validate_a_report(const int& index);
	void notify()override;
	std::vector<std::string>& get_messages();
	std::vector<RoadReport>& get_reports();
	std::vector<Driver>& get_drivers();
};