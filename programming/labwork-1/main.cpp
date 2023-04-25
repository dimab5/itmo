#include <iostream>
#include <fstream>
#include <string>

int countStr(const std :: string& fileName) {
    //считаем строки
    std :: ifstream fileStr(fileName);
    std :: string line;
    int count = 0;
    while(getline(fileStr, line)) {
        count++;
    }
    return count;
}

int countSize(const std :: string& fileName) {
    //считаем размер файла (в байтах)
    std :: ifstream fileSize(fileName);
    fileSize.seekg(0, std :: ios :: end);
    std :: streamoff size = fileSize.tellg();
    return size;
}

int countWord(const std :: string& fileName) {
    //считаем количество слов в файле
    std :: ifstream fileWord(fileName);
    int countWord = 0;
    std :: string s;
    while (fileWord >> s)
        countWord++;
    return countWord;
}

int AverageBytes(const std :: string& fileName) {
    std :: ifstream file(fileName);
    std :: string temp;
    int size = 0;
    int cnt = 0;
    while (file >> temp) {
        size += temp.length();
        cnt++;
    }
    return (size / cnt);
}

int main(int argc, char** argv) {
    std :: string path;
    bool opt[3] = {false, false, false};
    for (int i = 0; i < argc; i++) {
    	std :: cout << argv[i] << " ";
        std :: string str = std :: string(argv[i]);
        if (long(str.find(".txt")) > -1)
            path = str;
        else if (str == "--lines")
            opt[0] = true;
        else if (str == "--bytes")
            opt[1] = true;
        else if (str == "--words")	
            opt[2] = true;
        else if (str[1] != '-') {
            for (int i = 1; i < str.length(); i++) {
                switch(str[i]) {
                    case 'l':
                        opt[0] = true;
                        break;
                    case 'c':
                        opt[1] = true;
                        break;
                    case 'w':
                        opt[2] = true;
                        break;
                    default:
                        std :: cout << "wrong input";
                        exit(1);
                }
            }
        }
    }
    if (opt[0])
        std :: cout << "lines: " << countStr(path) << std :: endl;
    if (opt[1]) {
        std :: cout << "bytes: " << countSize(path) << std::endl;
        std :: cout << "average number of bytes: " << AverageBytes(path) << std :: endl;
    }
    if (opt[2])
        std :: cout << "words: " << countWord(path) << std :: endl;
    if (opt[0] == 0 and opt[1] == 0 and opt[2] == 0) {
        std :: cout << "lines: " << countStr(path) << std :: endl;
        std :: cout << "bytes: " << countSize(path) << std :: endl;
        std :: cout << "words: " << countWord(path) << std :: endl;
    }

    std :: cout << path;

    return 0;
}