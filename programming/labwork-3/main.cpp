#include "main.h"
#include "image.h"
#include <sstream>

int main (int argc, char* argv[]) {

    int max_iter;
    int freq;
    uint16_t width;
    uint16_t height;
    std :: string input;
    std :: string output;
    std :: string format = ".bmp";
    std :: string path;


    for (int i = 1; i < argc; i += 2) {

        std :: string first = std :: string(argv[i]);
        std :: string second = std :: string(argv[i + 1]);

        if (first == "-l" or first == "--length")
            height = stoi(second);
        if (first == "-w" or first == "--width")
            width = stoi(second);
        if (first == "-i" or first == "--input")
            input = second;
        if (first == "-o" or first == "--output")
            output = second;
        if (first == "-m" or first == "--max-iter")
            max_iter = stoi(second);
        if (first == "-f" or first == "--freq")
            freq = stoi(second);

    }

    std :: vector <std :: vector <uint64_t> > ASM(width, std :: vector <uint64_t> (height));
    ASM = parce(input, width, height);

    output += "image";
    int number_image = 0;

    while (!is_stable(ASM, width, height) && number_image < max_iter) {

        realization(ASM, width, height);
        if (number_image % freq == 0 and freq != 0) {
            path = output + std :: to_string(number_image / freq) + format;
            create (ASM, width, height, path);
        }

        number_image++;

    }

    path = output + std ::to_string(number_image / freq + 100) + format;
    create (ASM, width, height, path);

    std :: cout << "That's all!";

}