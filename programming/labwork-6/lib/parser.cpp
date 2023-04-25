#include "parser.h"

using namespace omfl;


OMFL_Parser &parse(const std::string &string) {

    Array.clear();
    OMFL_Parser *Parser = new OMFL_Parser;
    Parser->sec = "";
    if (string.empty()) {
        is_valid = true;
        return *Parser;
    }
    std::string str = "";
    for (int i = 0; i < string.length(); i++) {
        if (string[i] != '\n') str += string[i];
        else Parser->strings.push_back(str), str = "", i += 8;
    }
    Parser->strings.push_back(str);

    std::string key = "";
    std::string val = "";
    std::string cur_section;

    for (int l = 0; l < Parser->strings.size(); l++) {
        str = Parser->strings[l];
        if (Parser->is_section(str)) {
            cur_section = str.substr(str.find('[') + 1, str.find(']') - str.find('[') - 1);
            Parser->is_sec = true;
        }
        if (str.find('=') != std::string::npos) {
            int i = 0, j = str.find('=') - 1;
            Parser->del(str, i, j);
            key = str.substr(i, j + 1 - i);
            //проверка на корректность key
            is_valid = Parser->is_key(key);
            if (!cur_section.empty()) key = cur_section + '.' + key;
            i = str.find('=') + 1, j = str.length() - 1;
            Parser->del(str, i, j);
            val = str.substr(i, j + 1 - i);
            if (!Parser->values[key].empty()) {
                is_valid = false;
                return *Parser;
            } else Parser->values[key] = val;
            if (Parser->is_array(val)) Array_Parse(val);
            //проверка на корректность value
            is_value["string"] = Parser->is_string(val);
            is_value["int"] = Parser->is_int(val);
            is_value["float"] = Parser->is_float(val);
            is_value["bool"] = Parser->is_bool(val);
            is_value["array"] = Parser->is_array(val);
            if (!is_value["string"] && !is_value["int"] && !is_value["float"] && !is_value["bool"] &&
                !is_value["array"])
                is_valid = false;
        } else {
            is_value["section"] = Parser->is_section(str);
            if (str.find('#') != std::string::npos)
                is_value["comment"] = Parser->is_comment(str.substr(str.find('#') + 1, str.length()));
            if (!is_value["section"] && !is_value["comment"])
                is_valid = false;
        }

    }

    P = Parser;
    return *Parser;
}

bool OMFL_Parser::valid() const {
    return is_valid;
}

//delete ' '
void OMFL_Parser::del(const std::string &str, int &i, int &j) {
    while (str[i] == ' ') i++;
    if (str.find('#') != std::string::npos && j > str.find('#')) j = str.find('#') - 1;
    while (str[j] == ' ') j--;
}

//проверка на корректность key
bool OMFL_Parser::is_key(const std::string &str) {
    std::string key = "";
    for (int i = 0; i < str.length(); i++)
        if (str[i] != ' ')
            key += str[i];
    if (key.length() == 0)
        return false;
    for (int i = 0; i < key.length(); i++)
        if (!((key[i] >= '1' && key[i] <= '9') || (key[i] >= 'A' && key[i] <= 'Z') ||
              (key[i] >= 'a' && key[i] <= 'z') || key[i] == '-' || key[i] == '_'))
            return false;
    return true;
}

//проверка на корректность значения string
bool OMFL_Parser::is_string(const std::string &str) {
    int i = 0;
    int j = str.length() - 1;
    del(str, i, j);
    if (j - i > 0 && str.substr(i + 1, j - i - 1).find('\"') != std::string::npos) return false;
    if (str[i] == '\"' && str[j] == '\"') return true;
    return false;
}

//проверка на корректность значения int
bool OMFL_Parser::is_int(const std::string &str) {
    int i = 0;
    int j = str.length() - 1;
    del(str, i, j);
    if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '+' || str[i] == '-') ||
        (str[i] == '+' || str[i] == '-') && i == j)
        return false;
    for (int l = i + 1; l <= j; l++)
        if (!(str[l] >= '0' && str[l] <= '9')) return false;
    return true;
}

//проверка на корректность значения float
bool OMFL_Parser::is_float(const std::string &str) {
    int i = 0;
    int j = str.length() - 1;
    del(str, i, j);
    if (str.find('.') == std::string::npos) return false;
    if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '+' || str[i] == '-') ||
        (str[i] == '+' || str[i] == '-') && i == j)
        return false;
    if (str[j] == '.' || str[j] == '+' || str[j] == '-' ||
        ((str[i] == '-' || str[i] == '+') && str[i + 1] == '.'))
        return false;
    for (int l = i + 1; l <= j; l++)
        if (!((str[l] >= '0' && str[l] <= '9') || str[l] == '.')) return false;
    return true;
}

//проверка на корректность значения bool
bool OMFL_Parser::is_bool(const std::string &str) {
    int i = 0;
    int j = str.length() - 1;
    del(str, i, j);
    std::string tmp = "";
    for (int l = i; l <= j; l++)
        tmp += str[l];
    if (tmp == "true" || tmp == "false") return true;
    return false;
}

//проверка на корректность array
bool OMFL_Parser::is_array(const std::string &str) {
    int i = 0;
    int j = str.length() - 1;
    del(str, i, j);
    if (str[i] != '[' || str[j] != ']') return false;
    if (std::count(str.begin(), str.end(), '[') != std::count(str.begin(), str.end(), ']')) return false;
    if (str.find(';') != std::string::npos) return false;
    std::string tmp = "";
    return true;
}

//проверка на корректность section
bool OMFL_Parser::is_section(const std::string &str) {
    int i = 0;
    int j = str.length() - 1;
    del(str, i, j);
    if (str[i] != '[' || str[j] != ']' || i == j - 1) return false;
    std::string tmp = "";
    for (int l = i + 1; l < j; l++) {
        if (str[l] != '.') tmp += str[l];
        else if (!is_key(tmp)) return false;
        else tmp = "";
    }
    if (!is_key(tmp)) return false;
    return true;
}

//проверка на comment
bool OMFL_Parser::is_comment(const std::string &str) {
    if (str.find('\n') != std::string::npos) return false;
    return true;
}

//метод Get получения значения по ключу
OMFL_Parser &OMFL_Parser::Get(const std::string &str) const {
    Array_Parse(str);
    if (str.find('.') == std::string::npos && P->is_sec) {
        if (!P->sec.empty()) P->sec = P->sec + '.' + str;
        else P->sec = P->sec + str;
        if (!P->values[P->sec].empty()) P->value = P->values[P->sec];
    }
    else P->value = P->values[str];
    return *P;
}

bool OMFL_Parser::IsInt() const {
    return (P->is_int(P->value));
}

int OMFL_Parser::AsInt() const {
    return stoi(P->value);
}

int OMFL_Parser::AsIntOrDefault(int key) {
    P->value = std::to_string(key);
    return stoi(P->value);
}

bool OMFL_Parser::IsFloat() const {
    return (P->is_float(P->value));
}

float OMFL_Parser::AsFloat() const {
    return atof(P->value.c_str());
}

bool OMFL_Parser::IsBool() const {
    return P->is_bool(P->value);
}

float OMFL_Parser::AsFloatOrDefault(float key) {
    P->value = std::to_string(key);
    return atof(P->value.c_str());
}

bool OMFL_Parser::IsString() const {
    return P->is_string(P->value);
}

std::string OMFL_Parser::AsString() const {
    return P->value.substr(P->value.find('\"') + 1, P->value.rfind('\"') - P->value.find('\"') - 1);
}

std::string OMFL_Parser::AsStringOrDefault(const std::string &key) {
    P->value = key;
    return P->value;
}

bool OMFL_Parser::AsBool() const {
    return P->value.find("true") != std::string::npos;
}

bool OMFL_Parser::IsArray() const {
    return P->is_array(P->value);
}

OMFL_Parser &OMFL_Parser::operator[](int pos) {
    if (pos < Array.size()) P->value = Array[pos];
    return *P;
}

void Array_Parse(const std::string &str) {
    if (P->is_array(str)) {
        int cnt1 = 0;
        int cnt2 = 0;
        std::string val = "";
        for (int i = 1; i < str.length() - 1; i++) {
            if (str[i] == '[') cnt1 += 1;
            if (str[i] == ']') cnt2 += 1;
            if (str[i] != ',') val += str[i];
            else {
                Array.push_back(val);
                val = "";
            }
        }
        if (!val.empty()) Array.push_back(val);
    }
}

void Massiv_parse(const std::string& str) {

}