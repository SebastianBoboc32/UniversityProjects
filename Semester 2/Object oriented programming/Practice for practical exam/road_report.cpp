#include "road_report.h"

RoadReport::RoadReport():description(""),reporter(""),validation_status(false)
{
    exact_location = std::make_pair(0, 0);
}

RoadReport::RoadReport(const std::string& desc, const std::string& rep, const double& x, const double& y, bool valid_stat)
:description(desc),reporter(rep),validation_status(valid_stat){
    exact_location = std::make_pair(x, y);
}

float RoadReport::distanceFromDriver(const Driver& drv)
{
    double xA = drv.get_current_location().first;
    double yA = drv.get_current_location().second;
    double xB = exact_location.first;
    double yB = exact_location.second;
    return static_cast<float>(sqrt((yB - yA) * (yB - yA) + (xB - xA)*(xB - xA)));
}

std::string RoadReport::to_str() const
{
    return description + " "+reporter + " " + std::to_string(exact_location.first)
        +" "+std::to_string(exact_location.second) + " " + std::to_string(validation_status);
}

std::string RoadReport::get_description() const
{
    return description;
}

std::string RoadReport::get_reporter() const
{
    return reporter;
}

std::pair<double, double> RoadReport::get_location() const
{
    return exact_location;
}

bool RoadReport::get_valid_stat() const
{
    return validation_status;
}

void RoadReport::set_valid()
{
    validation_status = true;
}

std::istream& operator>>(std::istream& is, RoadReport& rrep)
{
    std::string line_desc;
    std::string line_rep;
    std::string line_loc;
    std::string line_status;
    std:getline(is, line_desc);
    std::getline(is, line_rep);
    std::getline(is, line_loc);
    std::istringstream read_coords(line_loc);
    double X, Y;
    read_coords >> X >> Y;
    std::getline(is, line_status);
    bool valid = false;
    if (line_status == "0")
        valid = false;
    else if (line_status == "1")
        valid = true;
    rrep = RoadReport(line_desc, line_rep, X, Y, valid);
    return is;
}

std::ostream& operator<<(std::ostream& os, const RoadReport& rrep)
{
    os << rrep.description << "\n";
    os << rrep.reporter << "\n";
    os << rrep.exact_location.first << " " << rrep.exact_location.second << "\n";
    if (rrep.validation_status)os << "0" << "\n";
    else os << "1" << "\n";
    return os;
}
