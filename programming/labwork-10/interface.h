#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <map>
#include <cpr/cpr.h>
#include "json.hpp"

using json = nlohmann::json;


std::string Get_Time(const std::string& date);

std::string Get_Date(const std::string& date);

std::string Define_Weather_Code(unsigned int code);


struct Section {
    std::string time;
    float temperature;
    float apparent_temperature;
    float wind_speed;
    std::string weather_code;
    size_t humidity;
    int wind_direction;
    std::string city;

    Section Parse_Current_Weather(const std::string &weather_json, const std::string &c, std::pair<float, float> Coordinats);
    Section Parse_Weather(const std::string &weather_json, const std::string &c, size_t num, const std::string &section);
};


struct Day {
    size_t num;
    std::string date;
    Section morning;
    Section day;
    Section evening;
    Section night;

    Day Fill_Day(size_t n, const std::string &weather_json, const std::string &city);
};


std::vector<Day> Realization(const std::string &weather_json, const std::string &city);

void All_Request(const std::string &s, std::map<std::string, std::vector<Day>>& Data, std::map<std::string, Section>& Current);

std::string plus(float x);

void Visualisation(std::map<std::string, std::vector<Day>> Data, std::map<std::string,
                   Section> Current, const std::string &city, size_t cnt_days);