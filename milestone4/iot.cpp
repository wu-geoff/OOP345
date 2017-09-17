#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "i.h"
#include "t.h"
#include "o.h"

std::vector<std::vector<std::string> > getData(std::ifstream& is, std::vector<std::vector<std::string> > temp, char delim);

int main(int argc, char* argv[]) {
	if (argc != 5) {
		std::cerr << argv[0] << ": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << " file_name delimiter\n";
		return 1;
	}

	// argv[1] -- taskfile
	std::ifstream task(argv[1]), item(argv[2]), order(argv[3]);
	// argument 2 -- itemfile
	// arg3 - customerorder
	// arg4 - delimiter
	char delim = argv[4][0];

	std::vector<std::vector<std::string> > taskData, itemData, orderData;

	taskData = getData(task, taskData, delim);
	itemData = getData(item, itemData, delim);
	orderData = getData(order, orderData, delim);


	try {
		TaskManager tman(taskData);
		ItemManager iman(itemData);
		OrderManager oman(orderData);
		tman.check();
		iman.check(tman);
		oman.check(iman);
		tman.print(std::cout);
		iman.print(std::cout);
		oman.print(std::cout);
		//tman.genGraph((std::string(argv[1]) + ".gv").c_str());
	}
	catch (const std::string msg) {
		std::cout << msg << std::endl;
	}

	return 0;
}

std::vector<std::vector<std::string> > getData(std::ifstream & is, std::vector<std::vector<std::string> > data, char delim) {
	std::string buffer;
	while (std::getline(is, buffer, '\n')) {
		std::istringstream line(buffer);
		std::vector<std::string> rec;
		std::string field;
		while (std::getline(line, field, delim)) {
			field = field.erase(0, field.find_first_not_of(" \t\n\r\f\v"));
			field = field.erase(field.find_last_not_of(" \t\n\r\f\v") + 1);
			if (!field.empty()) rec.push_back(field);
		}
		if (rec.size() != 0) {
			data.push_back(rec);
		}
	}

	return data;
}
