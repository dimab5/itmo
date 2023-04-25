#include "main.h"


std::vector<std::vector<uint64_t> > parce(const std::string &path, uint16_t width, uint16_t height) {

    std::ifstream file_input(path);
    std::vector<std::vector<uint64_t> > input(width, std::vector<uint64_t>(height, 0));

    std::string s;

    while (!file_input.eof()) {

        uint16_t x;
        uint16_t y;
        uint64_t val;
        file_input >> s;
        x = stoi(s);
        file_input >> s;
        y = stoi(s);
        file_input >> s;
        val = stoi(s);
        input[x][y] = val;

    }

    return input;

}

void realization(std::vector<std::vector<uint64_t> > &ASM, uint16_t width, uint16_t height) {

    for (uint16_t i = 0; i < width; i++) {
        for (uint16_t j = 0; j < height; j++) {

            if (ASM[i][j] > 3) {

                ASM[i][j] -= 4;

                if (i != width - 1)
                    ASM[i + 1][j] += 1;
                if (i != 0)
                    ASM[i - 1][j] += 1;
                if (j != height - 1)
                    ASM[i][j + 1] += 1;
                if (j != 0)
                    ASM[i][j - 1] += 1;

            }

        }
    }

}

bool is_stable(std::vector<std::vector<uint64_t> > &ASM, uint16_t width, uint16_t height) {

    for (uint16_t i = 0; i < width; i++) {
        for (uint16_t j = 0; j < height; j++) {

            if (ASM[i][j] > 3)
                return false;

        }
    }

    return true;

}

