#include "interface.h"
#include "requests.h"

using json = nlohmann::json;


std::string Get_Time(const std::string& date) {
    return date.substr(11, 5);
}

std::string Get_Date(const std::string& date) {
    return date.substr(0, 10);
}

std::string Define_Weather_Code(unsigned int code) {
    switch (code) {
        case 0: return "Clear sky";
        case 1: return "Mainly clear";
        case 2: return "Partly cloudy";
        case 3: return "Overcast";
        case 45: return "Fog";
        case 46: return "Depositing rime fog";
        case 51: return "Light intensity drizzle";
        case 53: return "Moderate intensity drizzle";
        case 55: return "Denze intensity drizzle";
        case 56: return "Light freezing drizzle";
        case 57: return "Denze freezing drizzle";
        case 61: return "Slight rain";
        case 63: return "Moderate rain";
        case 65: return "Heavy rain";
        case 66: return "Light intensity freezing rain";
        case 67: return "Heavy intensity freezing rain";
        case 71: return "Slight intensity snow fall";
        case 73: return "Moderate intensity snow fall";
        case 75: return "Heavy intensity snow fall";
        case 77: return "Snow grains";
        case 80: return "Slight rain showers";
        case 81: return "Moderate rain showers";
        case 82: return "Violent rain showers";
        case 85: return "Slight snow showers";
        case 86: return "Heavy snow showers";
        case 95: return "Thunderstorm";
        case 96: return "Thunderstorm with slight hail";
        case 99: return "Thunderstorm with heavy hail";
    }
}



Section Section::Parse_Current_Weather(const std::string &weather_json, const std::string &c, std::pair<float, float> Coordinats) {
    json data = json::parse(weather_json);
    try {
        this->time = Get_Current_Time(Coordinats);
        std::ofstream file("current_time_" + c + ".txt");
        file << this->time;
    }
    catch(nlohmann::detail::parse_error) {
        std::ifstream file("current_time_" + c + ".txt");
        file >> this->time;
    }
    this->temperature = data["current_weather"]["temperature"];
    this->wind_speed = data["current_weather"]["windspeed"];
    this->wind_direction = data["current_weather"]["winddirection"];
    this->weather_code = Define_Weather_Code(data["current_weather"]["weathercode"]);
    this->city = c;
    return *this;
}

Section Section::Parse_Weather(const std::string &weather_json, const std::string &c, size_t num, const std::string &section) {
    json data = json::parse(weather_json);
    this->time = section;
    size_t tmp = 0;
    if (section == "Morning") tmp = 9;
    if (section == "Day") tmp = 15;
    if (section == "Evening") tmp = 21;
    if (section == "Night") tmp = 3;
    this->temperature = data["hourly"]["temperature_2m"][24 * (num - 1) + tmp];
    this->apparent_temperature = data["hourly"]["apparent_temperature"][24 * (num - 1) + tmp];
    this->city = c;
    this->weather_code = Define_Weather_Code(data["hourly"]["weathercode"][24 * (num - 1) + tmp]);
    this->wind_speed = data["hourly"]["windspeed_10m"][24 * (num - 1) + tmp];
    this->wind_direction = data["hourly"]["winddirection_10m"][24 * (num - 1) + tmp];
    this->humidity = data["hourly"]["relativehumidity_2m"][24 * (num - 1) + tmp];
    return *this;
}


Day Day::Fill_Day(size_t n, const std::string &weather_json, const std::string &city) {
    this->num = n;
    Section tmp;
    this->morning = tmp.Parse_Weather(weather_json, city, num, "Morning");
    this->day = tmp.Parse_Weather(weather_json, city, num, "Day");
    this->evening = tmp.Parse_Weather(weather_json, city, num, "Evening");
    this->night = tmp.Parse_Weather(weather_json, city, num, "Night");
    this->date = Get_Date(json::parse(weather_json)["hourly"]["time"][24 * (n - 1) + 1]);
    return *this;
}


std::vector<Day> Realization(const std::string &weather_json, const std::string &city) {
    std::vector<Day> ans;
    std::string name = "last_data_" + city +".txt";
    std::ofstream file(name);
    file << weather_json;
    for (size_t i = 1; i <= 15; i++) {
        Day tmp;
        ans.push_back(tmp.Fill_Day(i, weather_json, city));
    }
    return ans;
}

void All_Request(const std::string &s, std::map<std::string, std::vector<Day>>& Data, std::map<std::string, Section>& Current) {
    std::string weather_json;
    std::pair<float, float> p;
    try {
        p = City_Request(s);
        weather_json = Weather_Request(p);
    }
    catch(nlohmann::detail::parse_error) {
        std::ifstream file("last_data_" + s +".txt");
        std::ostringstream str;
        str << file.rdbuf();
        weather_json = str.str();
    }
    Data[s] = Realization(weather_json, s);
    Section current;
    Current[s] = current.Parse_Current_Weather(weather_json, s, p);
}

std::string plus(float x) {
    if (x > 0) return "+";
    return "";
}

void Visualisation(std::map<std::string, std::vector<Day>> Data, std::map<std::string,
        Section> Current, const std::string &city, size_t cnt_days) {
    std::cout << std::setw(12) << city << ":\n";
    std::cout << "Current weather(" << Get_Date(Current[city].time) << ' ' << Get_Time(Current[city].time) << ")\n";
    (Current[city].temperature > 0) ? std::cout << '+' << Current[city].temperature : std::cout << Current[city].temperature;
    std::cout << "\n";
    std::cout << Current[city].wind_speed << " km/h\n";
    std::cout << Current[city].weather_code << '\n';

    for (int i = 0; i < cnt_days; i++) {
//        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//        SetConsoleTextAttribute(hConsole, 4);
        std::cout << '\n' << std::setw(65) << Data[city][i].date << '\n';
        std::cout << std::setw(25) << "Night:" << std::setw(30) << "Morning:" << std::setw(30) <<  "Day:" << std::setw(30) << "Evening:\n";
        std::cout << std::setw(24);
        (Data[city][i].night.temperature > 0) ? std::cout << "+" + std::to_string(Data[city][i].night.temperature).substr(0, 4) : std::cout << Data[city][i].night.temperature;
        std::cout << std::setw(30);
        (Data[city][i].morning.temperature > 0) ? std::cout << "+" + std::to_string(Data[city][i].morning.temperature).substr(0, 4) : std::cout << Data[city][i].morning.temperature;
        std::cout << std::setw(30);
        (Data[city][i].day.temperature > 0) ? std::cout << "+" + std::to_string(Data[city][i].day.temperature).substr(0, 4) : std::cout << Data[city][i].day.temperature;
        std::cout << std::setw(29);
        (Data[city][i].evening.temperature > 0) ? std::cout << "+" + std::to_string(Data[city][i].evening.temperature).substr(0, 4) : std::cout << Data[city][i].evening.temperature;
        std::cout << '\n';
        std::cout << std::setw(24) << std::to_string(Data[city][i].night.wind_speed).substr(0, 4) + " km/h" << std::setw(30) <<
                  std::to_string(Data[city][i].morning.wind_speed).substr(0, 4) + " km/h" << std::setw(30) <<
                  std::to_string(Data[city][i].day.wind_speed).substr(0, 4) + " km/h" << std::setw(30) <<
                  std::to_string(Data[city][i].evening.wind_speed).substr(0, 4) + " km/h\n";
        std::cout << std::setw(24) << std::to_string(Data[city][i].night.humidity) + "%" <<
                  std::setw(30) << std::to_string(Data[city][i].morning.humidity) + "%" <<
                  std::setw(30) << std::to_string(Data[city][i].day.humidity) + "%" <<
                  std::setw(29) << std::to_string(Data[city][i].evening.humidity) + "%" << '\n';
        std::cout << std::setw(24) << Data[city][i].night.weather_code << std::setw(30) << Data[city][i].morning.weather_code <<
                  std::setw(30) << Data[city][i].day.weather_code << std::setw(29) << Data[city][i].evening.weather_code << '\n';
    }
}
