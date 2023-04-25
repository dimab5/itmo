#pragma once

#include <cinttypes>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define maxsize 75
#define based 1000000000

struct uint2022_t {

    std::vector<uint32_t> dig;

    uint2022_t input(std::string s) {

        uint2022_t arr;
        int r = s.length() % 9;
        std::string temp = "";

        for (int i = 0; i < r; i++)
            temp += s[i];

        if (temp != "")
            arr.dig.push_back(stoi(temp));

        temp = "";

        for (int i = r; i < s.length(); i++) {
            temp += s[i];
            if ((i + 1 - r) % 9 == 0) {
                arr.dig.push_back(stoi(temp));
                temp = "";
            }
        }

        reverse(arr.dig.begin(), arr.dig.end());

        return arr;
    }

};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char *buff);

uint2022_t operator+(const uint2022_t &lhs, const uint2022_t &rhs);

uint2022_t operator-(const uint2022_t &lhs, const uint2022_t &rhs);

uint2022_t operator*(const uint2022_t &lhs, const uint2022_t &rhs);

bool operator==(const uint2022_t &lhs, const uint2022_t &rhs);

bool operator!=(const uint2022_t &lhs, const uint2022_t &rhs);

std::ostream &operator<<(std::ostream &stream, const uint2022_t &value);