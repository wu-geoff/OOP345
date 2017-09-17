#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Task.h"

std::vector<std::vector<std::string> > getData(std::ifstream& is, std::vector<std::vector<std::string> > temp, char delim);

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << argv[0] << ": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << " file_name delimiter\n";
		return 1;
	}

	std::vector<std::vector<std::string> > data;
	std::ifstream ifs;
	ifs.open(argv[1]);
	if (ifs.fail()) {
		std::cout << "Fail to open file: " << argv[1];
	}
	else {
		data = getData(ifs, data, argv[2][0]);
	}

	for (auto line : data) {
		for (auto field : line) {
			std::cout << field << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	for (int line = 0; line < data.size(); line++) {
		for (int field = 0; field < data[line].size(); field++) {
			std::cout << data[line][field] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";

	for (auto line = data.begin(); line < data.end(); line++) {
		for (auto field = line->begin(); field < line->end(); field++) {
			std::cout << *field << " ";
		}
		std::cout << "\n";
	}

	try {
		TaskManager tman(data);
		//tman.check();
		tman.print(std::cout);
		tman.graph(std::cout);
		tman.genGraph((std::string(argv[1]) + ".gv").c_str());
	}
	catch(const char* msg){
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
