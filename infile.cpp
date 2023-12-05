
#define _CRT_SECURE_NO_WARNINGS
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include "json.hpp"
#include <ctime>
#include <algorithm>
#include <windows.h>;


using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;
using json = nlohmann::json;

struct Predmet {
	std::string name_predmet;
	std::string type;
	std::string name_teacher;
	std::string audience;
	int number;
};

//функция удаления кавыек
std::string quotes(std::string pre) {
	std::string prech;
	for (const char& ele : pre) {
		if (ele != '"') {
			prech.push_back(ele);
		}
	}
	return prech;

};

std::string to_day(int day_i, std::string day_d1) {
	std::string dayy;
	switch (day_i) {
	case 1:
		dayy = "Monday";
		break;
	case 2:
		dayy = "Tuesday";
		break;
	case 3:
		dayy = "Wednesday";
		break;
	case 4:
		dayy = "Thursday";
		break;
	case 5:
		dayy = "Friday";
	}
	return dayy;
}

void PredmetInfile(std::vector<Predmet> predmett) {
	std::ofstream predMet("predmet.txt");
	for (const Predmet& predmed : predmett) {
		predMet << predmed.name_predmet << " " << predmed.type << " " 
			<< predmed.name_teacher << " " << predmed.audience <<" " <<predmed.number<< '\n';
	}
	predMet.close();
}


void InFile() {
	//setlocale(LC_ALL, "RU");
	SetConsoleOutputCP(65001);

	//просто важная строка
	mongocxx::instance inst{};

	const auto uri = mongocxx::uri{ "mongodb+srv://mongo_user:LXkEj4dJLpY19PT0@cluster0.6yzdyrb.mongodb.net/" };
	//conect to base
	mongocxx::client connection{ uri };
	//connect to new
	auto db = connection["new"];
	//conect to collection
	auto collection = db["one"];

	std::ofstream file("file1.json");

	std::vector<std::string> infile;
	auto cursor = collection.find({});
	for (auto& doc : cursor) {
		//std::cout << bsoncxx::to_json(doc) << '\n';
		file << bsoncxx::to_json(doc);
	}
	file.close();

	
	//parsing
	std::ifstream input_file("file1.json");
	json json_data;

	input_file >> json_data;
	
	//ctime
	time_t now = time(0);
	tm* ltm = localtime(&now);

	int day_i = ltm->tm_wday;
	

	

	//перебор расписания на день

	std::string day_d1, group_d, week_d, ParaN, day_d;
	std::cin >> week_d >> group_d >> day_d1;
	ParaN = "ParaN";
	//распределение на сегодня завтра
	if (day_d1 == "today") {
		day_d = to_day(day_i, day_d1);

	}
	else if (day_d1 == "tomorrow") {
		day_d = to_day(day_i + 1, day_d1);
	}
	else {
		day_d = day_d1;
	}

	//вложение расписания в структуру
	std::vector<Predmet> predmett;

	for (int n = 1; n < 7; n++) {
		Predmet predmet;
		ParaN = "ParaN" + std::to_string(n);
		predmet.audience = json_data[week_d][group_d][day_d][ParaN]["Audience"].dump();
		predmet.name_predmet = json_data[week_d][group_d][day_d][ParaN]["Lesson"].dump();
		predmet.name_teacher = json_data[week_d][group_d][day_d][ParaN]["Teacher"].dump();
		predmet.type = json_data[week_d][group_d][day_d][ParaN]["Type_of_lesson"].dump();
		predmet.number = n;
		predmett.push_back(predmet);
	}
	//запись в файл вектора
	PredmetInfile(predmett);

	int i_0 = 1;
	for (const auto& elem_0 : predmett) {
		if (elem_0.name_predmet != "null") {
			std::cout << i_0 << '\t' << elem_0.type << '\t' << elem_0.name_predmet << '\n';
		}
		i_0++;
	}
	std::cin.get();
}