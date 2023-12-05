#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>

struct Predmet {
    std::string name_predmet;
    std::string type;
    std::string name_teacher;
    std::string audience;
    int number;
};

struct Interval {
    int start_h;
    int start_m;
    int end_h;
    int end_m;
    std::string key;
};

void outpredmet(std::vector<Predmet> predmett) {
    std::ifstream file("predmet.txt");

    std::string name_predmet1;
    std::string type1;
    std::string name_teacher1;
    std::string audience1;
    int number1;

    while (file >> name_predmet1 >> type1 >> name_teacher1 >> audience1 >> number1) {
        predmett.push_back({ name_predmet1, type1, name_teacher1, audience1, number1 });
    }
}

void now_Time() {
    setlocale(LC_ALL, "Russian");

    time_t now = time(0);

    tm* ltm = localtime(&now);

    int hours = ltm->tm_hour;
    int minuts = ltm->tm_min;
    /*int hours = 14;
    int minuts = 10;*/

    std::vector<Interval> intervals;
    

    intervals = {
        {8, 0, 9, 30, "Первая пара"},
        {9, 50, 11, 20, "Вторая пара"},
        {11, 30, 13, 0, "Третья пара"},
        {13, 20, 14, 50, "Четвертая пара"},
        {15, 0, 16, 30, "Пятая пара"}
    };
    std::string curent_type = "перерыв";
    for (const auto& elem : intervals) {
        /*if ((hours >= elem.start_h && minuts >= elem.start_m) &&
            (hours < elem.end_h && minuts < elem.end_m)) {
            curent_type = elem.key;
        }*/
        if ((hours > elem.start_h || (hours == elem.start_h && minuts >= elem.start_m)) &&
            (hours < elem.end_h || (hours == elem.end_h && minuts < elem.end_m))) {
            curent_type = elem.key;
        }
    }
    std::vector<Predmet> predmett;
    outpredmet(predmett);
    if (hours >= 17) {
        curent_type = "пары закончились :)";
    }
    std::cout << curent_type<<'\n';

    for (const Predmet& elem : predmett) {
        std::cout << elem.name_predmet << '\n';
    }
}
