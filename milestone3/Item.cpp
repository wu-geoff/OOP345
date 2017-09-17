#include "Item.h"
#include "Task.h"

Item::Item(const std::vector<std::string>& oneLine){
	if (oneLine.size() == 1) {
		name = oneLine[0];
	}
	else if (oneLine.size() == 2) {
		name = oneLine[0];
		installer = oneLine[1];
	}
	else if (oneLine.size() == 3)
	{
		name = oneLine[0];
		installer = oneLine[1];
		remover = oneLine[2];
	}
	else if (oneLine.size() == 4)
	{
		name = oneLine[0];
		installer = oneLine[1];
		remover = oneLine[2];
		sequentialCode = oneLine[3];
	}
	else if (oneLine.size() == 5)
	{
		name = oneLine[0];
		installer = oneLine[1];
		remover = oneLine[2];
		sequentialCode = oneLine[3];
		description = oneLine[4];
	}
}

const std::string & Item::getName() const
{
	return name;
}

const std::string & Item::getInstaller() const
{
	return installer;
}

const std::string & Item::getRemover() const
{
	return remover;
}

std::ostream & Item::print(std::ostream & o) const
{
	o << std::setw(20) << getName() << std::setw(20) << getInstaller() << std::setw(20) << getRemover() << std::setw(20) << sequentialCode << std::setw(20) << description << std::endl;
	return o;
}

bool Item::empty() const
{
	return getName().empty() && getInstaller().empty() && getRemover().empty() && sequentialCode.empty() && description.empty();
}

ItemManager::ItemManager(std::vector<std::vector<std::string>> csvData)
{
	for (auto row : csvData) {
		Item i(row);
		list.push_back(i);
	}
}

void ItemManager::check(const TaskManager & T) const
{
	for (auto item : list) {
		if (T.find(item.getInstaller()) == false) {
			throw "installer not exists";
		}
		if (T.find(item.getRemover()) == false) {
			throw "remover not exists";
		}
	}
}

const std::vector<Item>& ItemManager::getList() const
{
	return list;
}
