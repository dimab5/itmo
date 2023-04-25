#pragma once

#include <filesystem>
#include <iostream>
#include <map>
#include <fstream>


namespace omfl {

    class OMFL_Parser {

    public:
        bool valid() const;
        OMFL_Parser& Get(const std::string& str) const;
        void del(const std::string &str, int& i, int& j);
        bool is_key(const std::string &str);
        bool is_string(const std::string &str);
        bool is_int(const std::string &str);
        bool is_float(const std::string &str);
        bool is_bool(const std::string &str);
        bool is_array(const std::string &str);
        bool is_section(const std::string &str);
        bool is_comment(const std::string &str);
        std::vector <std::string> strings;
        std::string value;
        bool IsInt() const;
        int AsInt() const;
        int AsIntOrDefault(int key);
        bool IsFloat() const;
        float AsFloat() const;
        float AsFloatOrDefault(float key);
        bool IsString() const;
        std::string AsString() const;
        std::string AsStringOrDefault(const std::string &key);
        bool IsBool() const;
        bool AsBool () const;
        bool IsArray() const;
        std::vector <std::string> sections;
        std::string Section;
        std::map <std::string, std::string> values;
        std::string sec = "";
        bool is_sec = false;
        OMFL_Parser& operator[](int pos);
//        struct massiv {
//            std::map <int, int> Int;
//            std::map <int, std::string> String;
//            std::map <int, float> Float;
//            std::map <int, bool> Bool;
//            std::map <int, massiv> Massiv;
//        };
//        massiv Values;

    };

}

static omfl::OMFL_Parser* P;
static bool is_valid = true;
static std::map <std::string, bool> is_value;
omfl::OMFL_Parser& parse(const std::string &string);
static std::vector <std::string> Array;
void Array_Parse(const std::string &str);
void Massiv_Parse(const std::string& str);
//omfl::OMFL_Parser& parse(const std::filesystem::path &path);
