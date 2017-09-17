#include "Order.h"
#include "Item.h"

Order::Order(const std::vector<std::string>& oneLine)
{
	if (oneLine.size() == 1) {
		customer = oneLine[0];
	}
	else if (oneLine.size() == 2) {
		customer = oneLine[0];
		product = oneLine[1];
	}
	else if (oneLine.size() >= 3)
	{
		customer = oneLine[0];
		product = oneLine[1];
		for (int i = 2; i < oneLine.size(); i++)
			items.push_back(oneLine[i]);
	}
}

const std::string & Order::getCustomer() const
{
	return customer;
}

const std::string & Order::getProduct() const
{
	return product;
}


std::ostream & Order::print(std::ostream & o) const
{
	o << std::setw(20) << getCustomer() << std::setw(20) << getProduct();
	for (int i = 0; i < items.size(); i++) {
		o << std::setw(20) << items[i];
	}
	o << std::endl;
	return o;
}

bool Order::empty() const
{
	return getCustomer().empty() && getProduct().empty() ;
}

const std::vector<std::string> Order::getItems() const
{
	return items;
}

OrderManager::OrderManager(std::vector<std::vector<std::string>> csvData)
{
	for (auto row : csvData) {
		Order ord(row);
		list.push_back(ord);
	}
}

void OrderManager::check(const ItemManager & I) const
{
	for (auto o : list) {
		for (auto i : o.getItems()) {
			for (auto j : I.getList()) {
				if (i != j.getName()) {
					throw "Item not exists";
				}
			}
		}
	}
}
