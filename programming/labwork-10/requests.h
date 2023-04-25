#include <vector>
#include <fstream>
#include <cpr/cpr.h>
#include "json.hpp"

using json = nlohmann::json;


std::vector<std::string> Get_List_City(const std::string &config);

size_t Get_Update_Frequency(const std::string &config);

size_t Get_Days_Count(const std::string &config);

std::pair<float, float> City_Request(const std::string &city);

std::string Weather_Request(std::pair<float, float> Coordinats);

std::string Get_Current_Time(std::pair<float, float> Coordinats);