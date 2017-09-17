#include "Task.h"

Task::Task(const std::vector<std::string>& oneLine) {
	if (oneLine.size() == 1) {
		name = oneLine[0];
	}
	else if (oneLine.size() == 2) {
		name = oneLine[0];
		slots = oneLine[1];
	}
	else if (oneLine.size() == 3)
	{
		name = oneLine[0];
		slots = oneLine[1];
		pass = oneLine[2];
	}
	else if (oneLine.size() == 4)
	{
		name = oneLine[0];
		slots = oneLine[1];
		pass = oneLine[2];
		fail = oneLine[3];
	}
}

const std::string & Task::getName() const {
	return name;
}

const std::string & Task::getPass() const {
	return pass;
}

const std::string & Task::getFail() const {
	return fail;
}

std::ostream & Task::print(std::ostream & o) const {
	o << std::setw(20) << getName() << std::setw(20) << slots << std::setw(20) << getPass() << std::setw(20) << getFail() << std::endl;
	return o;
}

std::ostream & Task::graph(std::ostream &o) const {
	if (getPass().empty() == false) o << '"' << getName() << "\" -> \"" << getPass() << "\" [color=green];\n";
	if (getFail().empty() == false) o << '"' << getName() << "\" -> \"" << getFail() << "\" [color=red];\n";
	if (getPass().empty() && getFail().empty()) o << '"' << getName() << '"' << " [shape=box];\n";

	return o;
}

bool Task::empty() const
{
	return getName().empty() && slots.empty() && getPass().empty() && getFail().empty();
}

TaskManager::TaskManager(std::vector<std::vector<std::string>> csvData) {
	for (auto row : csvData) {
		Task t(row);
		list.push_back(t);
	}
}

void TaskManager::genGraph(const char * gname) {
	std::ofstream file(gname, std::ofstream::out);
	file << "digraph task {\n";
	graph(file);
	file << "}";
	file.close();

#ifdef __unix
	std::string dot = "dot";
#else 
	std::string dot = "\"C:\\Program Files (x86)\\Graphviz2.38\\bin\\dot.exe\"";
#endif
	std::string f(gname), cmd;
	cmd = dot + " -Tpng " + f + " > " + f + ".png";
	system(cmd.c_str());
}

const Task * TaskManager::find(const std::string & name) const
{
	for (auto &t : list) {
		if (t.getName() == name) {
			return &t;
		}
	}
	return nullptr;
}

void TaskManager::check() const
{
	for (auto &t : list) {
		if (find(t.getPass()) == nullptr) {
			throw "No pass task";
		}
		if (find(t.getFail()) == nullptr) {
			throw "No fail task";
		}
	}
}
