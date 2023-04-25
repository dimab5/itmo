#include "requests.h"

using json = nlohmann::json;


std::vector<std::string> Get_List_City(const std::string &config) {
    std::vector<std::string> list_city;
    std::ifstream file(config);
    json data = json::parse(file);
    for (size_t i = 0; i < data[0]["cities"].size(); i++) {
        list_city.push_back(data[0]["cities"][i]);
    }
    return list_city;
}

size_t Get_Update_Frequency(const std::string &config) {
    std::ifstream file(config);
    json data = json::parse(file);
    return data[0]["frequency"];
}

size_t Get_Days_Count(const std::string &config) {
    std::ifstream file(config);
    json data = json::parse(file);
    return data[0]["days"];
}

std::pair<float, float> City_Request(const std::string &city) {
    cpr::Response response = cpr::Get(cpr::Url{"https://api.api-ninjas.com/v1/city?name=" + city},
                                      cpr::Authentication{"dimanb555@gmail.com", "1010555678", cpr::AuthMode::BASIC},
                                      cpr::Header{ {"X-Api-Key", "35NDgZ/Li7h0yhtUtE+1pw==w6AdwdCI0MdJnnJq"} });
    json data = json::parse(response.text);
    return std::make_pair(data[0]["latitude"], data[0]["longitude"]);
}

std::string Weather_Request(std::pair<float, float> Coordinats) {
    std::stringstream stream1;
    stream1.precision(2);
    stream1 << std::fixed;
    stream1 << Coordinats.first;
    std::string latitude  = stream1.str();
    std::stringstream stream2;
    stream2.precision(2);
    stream2 << std::fixed;
    stream2 << Coordinats.second;
    std::string longitude  = stream2.str();
    cpr::Response weather = cpr::Get(cpr::Url {"https://api.open-meteo.com/v1/forecast?latitude=" + latitude + "&longitude=" + longitude +
    "&hourly=temperature_2m,relativehumidity_2m,apparent_temperature,weathercode,windspeed_10m,winddirection_10m&current_weather=true&forecast_days=15"});
    return weather.text;
}

std::string Get_Current_Time(std::pair<float, float> Coordinats) {
    std::stringstream stream1;
    stream1.precision(2);
    stream1 << std::fixed;
    stream1 << Coordinats.first;
    std::string latitude  = stream1.str();
    std::stringstream stream2;
    stream2.precision(2);
    stream2 << std::fixed;
    stream2 << Coordinats.second;
    std::string longitude  = stream2.str();
    cpr::Response response = cpr::Get(cpr::Url
                                              {"https://www.timeapi.io/api/Time/current/coordinate?latitude=" + latitude + "&longitude=" + longitude});
    json data = json::parse(response.text);
    return data["dateTime"];
}