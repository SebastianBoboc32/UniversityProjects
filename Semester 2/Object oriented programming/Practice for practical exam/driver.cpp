#include "driver.h"

Driver::Driver():name(""),score(0)
{
    current_location = std::make_pair(0, 0);
    bonus_points = 0;
}

Driver::Driver(const std::string& name, const double& first, const double& second, const int& sc)
:name(name),score(sc){
    current_location = std::make_pair(first, second);
    bonus_points = 0;
}

std::string Driver::get_name() const
{
    return name;
}

std::pair<double, double> Driver::get_current_location() const
{
    return current_location;
}

int Driver::get_score() const
{
    return score;
}

int Driver::get_bonus_points() const
{
    return bonus_points;
}

void Driver::raise_bonus_points()
{
    bonus_points++;
}

void Driver::raise_score()
{
    score++;
}

std::istream& operator>>(std::istream& is, Driver& drv)
{
    std::string line_name;
    std::string line_coord;
    std::string line_score;
    std::getline(is, line_name);
    std::getline(is, line_coord);
    std::istringstream read_coords(line_coord);
    double X, Y;
    read_coords >> X >> Y;
    std::getline(is, line_score);
    if (!line_score.empty() && line_score[line_score.length() - 1] == '\n') {
        line_score.erase(line_score.length() - 1);
    }
    int scr = 5;
    std::istringstream get_val(line_score);
    get_val >> scr;
    drv = Driver(line_name, X, Y, scr);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Driver& drv)
{
    os << drv.name << "\n";
    os << drv.current_location.first << " " << drv.current_location.second << "\n";
    os << drv.score << "\n";
    return os;
}
