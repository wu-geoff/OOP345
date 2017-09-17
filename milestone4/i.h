#ifndef I_H
#define I_H

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

class TaskManager;

class Item {
private:
	std::string name, installer, remover, sequentialCode, description;
public:
	Item(const std::vector<std::string>& oneLine);
	const std::string& getName() const;
	const std::string& getInstaller() const;
	const std::string& getRemover() const;
	std::ostream & print(std::ostream &o) const;
	//std::ostream & graph(std::ostream &o) const;
	bool empty() const;
};

class ItemManager {
public:
	ItemManager(std::vector< std::vector<std::string> > csvData);
	void print(std::ostream &o) { for (auto i : list) { i.print(o); } }
	//void graph(std::ostream& o) { for (auto t : list) { t.graph(o); } }
	//void genGraph(const char *gname);
	void check(const TaskManager &T) const;
	const std::vector<Item>& getList() const;
private:
	std::vector<Item> list;
};

#endif 
