#include "repository.h"

void Repository::read_from_files()
{
    std::string msg;
    std::ifstream read_messages(messages_file);
    while (std::getline(read_messages,msg))
        messages.push_back(msg);
    read_messages.close();
    Driver drv;
    std::ifstream read_drivers(drivers_file);
    while (read_drivers >>std::ws>> drv)
        drivers.push_back(drv);
    read_drivers.close();
    RoadReport repp;
    std::ifstream read_reports(reports_file);
    while (read_reports>>std::ws >> repp)
        reports.push_back(repp);
    read_reports.close();
}

void Repository::write_to_files()
{
    std::ofstream write_messages(messages_file);
    for (auto it : messages)
        write_messages << it<<"\n";
    write_messages.close();
    std::ofstream write_drivers(drivers_file);
    for (auto it : drivers)
        write_drivers << it;
    write_drivers.close();
    std::ofstream write_reports(reports_file);
    for (auto it : reports)
        write_reports << it;
    write_reports.close();
}

Repository::Repository(const std::string& df, const std::string& rf, const std::string& mf)
:drivers_file(df),reports_file(rf),messages_file(mf){
    read_from_files();
}

void Repository::add_observer(Observer* obs)
{
    observers.push_back(obs);
}

void Repository::add_a_message(const std::string& msg)
{
    messages.push_back(msg);
    notify();
}

void Repository::add_a_report(const RoadReport& repp)
{
    reports.push_back(repp);
    notify();
}

void Repository::raise_drivers_score(const int& index)
{
    drivers[index].raise_score();
    notify();
}

void Repository::validate_a_report(const int& index)
{
    reports[index].set_valid();
    notify();
}

void Repository::notify()
{
    write_to_files();
    for (auto obs : observers)
        obs->update();
    
}

std::vector<std::string>& Repository::get_messages()
{
    return messages;
}

std::vector<RoadReport>& Repository::get_reports()
{
    return reports;
}

std::vector<Driver>& Repository::get_drivers()
{
    return drivers;
}
