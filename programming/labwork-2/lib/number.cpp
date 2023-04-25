#include "number.h"

uint2022_t from_uint(uint32_t j) {

    std::string s = std::to_string(j);
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


uint2022_t from_string(const char *buff) {

    std::string s = buff;
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

uint2022_t operator+(const uint2022_t &lhs, const uint2022_t &rhs) {

    uint2022_t arr;
    int temp = 0;
    int n = lhs.dig.size();
    int m = rhs.dig.size();

    for (int i = 0; i < std::max(n, m); i++)
        arr.dig.push_back(0);

    for (int i = 0; i < std::max(n, m); i++) {
        if (i < n)
            temp += lhs.dig[i];
        if (i < m)
            temp += rhs.dig[i];

        if (temp >= based and i != std::max(n, m) - 1) {
            arr.dig[i + 1]++;
            temp -= based;
        }

        arr.dig[i] += temp;
        temp = 0;
    }

    return arr;
}

uint2022_t operator-(const uint2022_t &lhs, const uint2022_t &rhs) {

    uint2022_t arr;
    int temp = 0;
    int n = lhs.dig.size();
    int m = rhs.dig.size();

    for (int i = 0; i < std::max(n, m); i++)
        arr.dig.push_back(0);

    if (n > m or (n == m and lhs.dig[n - 1] >= rhs.dig[m - 1])) {
        for (int i = 0; i < std::max(n, m); i++) {
            temp = lhs.dig[i];
            if (i < m)
                temp -= rhs.dig[i];

            if (temp < 0 and i != std::max(n, m) - 1) {
                temp += based;
                arr.dig[i + 1]--;
            }

            arr.dig[i] += temp;
            temp = 0;
        }

    } else {
        arr.dig[std::max(n, m) - 1] = -1;
        return arr;
    }

    return arr;
}

uint2022_t operator*(const uint2022_t &lhs, const uint2022_t &rhs) {

    uint2022_t arr;
    int n = lhs.dig.size();
    int m = rhs.dig.size();

    arr.dig.resize(n + m);

    for (size_t i = 0; i < n; ++i) {
        int digit = 0;
        for (size_t j = 0; j < m || digit != 0; ++j) {
            long long temp = digit;
            if (j < m)
                temp += arr.dig[i + j] + lhs.dig[i] * (long long) rhs.dig[j];
            arr.dig[i + j] = temp % based;
            digit = temp / based;
        }
    }

    int i = arr.dig.size() - 1;
    while (arr.dig[i] == 0 and arr.dig.size() != 1) {
        arr.dig.erase(arr.dig.begin() + i);
        i--;
    }

    return arr;
}

bool operator==(const uint2022_t &lhs, const uint2022_t &rhs) {
    if (lhs.dig == rhs.dig)
        return true;
    return false;
}

bool operator!=(const uint2022_t &lhs, const uint2022_t &rhs) {
    if (lhs.dig != rhs.dig)
        return true;
    return false;
}

std::ostream &operator<<(std::ostream &stream, const uint2022_t &value) {

    int n = value.dig.size();

    if (n <= maxsize and value.dig[n - 1] != -1) {
        for (int i = n - 1; i > -1; i--) {
            std::string temp = std::to_string(value.dig[i]);
            int cnt = 9 - temp.length();

            while ((i != n - 1) and cnt-- != 0)
                stream << 0;
            stream << value.dig[i];
        }
    } else
        stream << "Undefined Behavior";

    return stream;
}