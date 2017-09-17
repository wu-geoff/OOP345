#ifndef T_H
#define T_H

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

class Task {
private:
	std::string name, slots, pass, fail;
public:
	Task(const std::vector<std::string>& oneLine);
	const std::string& getName() const;
	const std::string& getPass() const;
	const std::string& getFail() const;
	std::ostream & print(std::ostream &o) const;
	std::ostream & graph(std::ostream &o) const;
	bool empty() const;
};

class TaskManager {
public:
	TaskManager(std::vector< std::vector<std::string> > csvData);
	void print(std::ostream &o) { for (auto t : list) { t.print(o); } }
	void graph(std::ostream& o) { for (auto t : list) { t.graph(o); } }
	void genGraph(const char *gname);
	const Task* find(const std::string& name) const;
	void check() const;
private:
	std::vector<Task> list;
};

#endif 
