#include <iostream>
#include <chrono>
#include <conio.h>
#include "requests.h"
#include "interface.h"


int main() {
    std::map<std::string, std::vector<Day>> Data;
    std::map<std::string, Section> Current;
    std::vector<std::string> Cities = Get_List_City("config.txt");

    for (auto& s : Cities) {
        All_Request(s, Data, Current);
    }

    int num_city = 0;
    int cnt_days = Get_Days_Count("config.txt");
    int frequency = Get_Update_Frequency("config.txt");
    system("cls");
    Visualisation(Data, Current, Cities[num_city], cnt_days);

    auto start = std::chrono::system_clock::now();

    while(true) {
        while (_kbhit()) {
            int input;
            input = getch();
        }

        bool l = false;

        while (!_kbhit()) {
            auto end = std::chrono::system_clock::now();
            std::chrono::duration<double> dur = end - start;
            if (dur.count() >= frequency) {
                std::cout << "\nReloading... Please wait!\n";
                for (auto &s: Cities) {
                    All_Request(s, Data, Current);
                }
                system("cls");
                Visualisation(Data, Current, Cities[num_city], cnt_days);
                start = std::chrono::system_clock::now();
                l = true;
            }
        }

        if (l) {
            while (_kbhit()) {
                int input;
                input = getch();
            }
        }

        int input;
        input = getch();
        switch (input) {
            case 'p':
                if (num_city > 0) {
                    system("cls");
                    Visualisation(Data, Current, Cities[--num_city], cnt_days);
                }
                break;
            case 'n':
                if (num_city < Cities.size() - 1) {
                    system("cls");
                    Visualisation(Data, Current, Cities[++num_city], cnt_days);
                }
                break;
            case '=':
                if (cnt_days < 16) {
                    system("cls");
                    Visualisation(Data, Current, Cities[num_city], ++cnt_days);
                }
                break;
            case '-':
                if (cnt_days > 0) {
                    system("cls");
                    Visualisation(Data, Current, Cities[num_city], --cnt_days);
                }
                break;
            case 27:
                exit(0);
            default:
                continue;
        }
    }
}

