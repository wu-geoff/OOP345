#ifndef O_H
#define O_H

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>

class ItemManager;

class Order {
private:
	std::string customer, product;
	std::vector<std::string> items;
public:
	Order(const std::vector<std::string>& oneLine);
	const std::string& getCustomer() const;
	const std::string& getProduct() const;
	std::ostream & print(std::ostream &o) const;
	//std::ostream & graph(std::ostream &o) const;
	bool empty() const;
	const std::vector<std::string> getItems() const;
};

class OrderManager {
public:
	OrderManager(std::vector< std::vector<std::string> > csvData);
	void print(std::ostream &o) { for (auto i : list) { i.print(o); } }
	//void graph(std::ostream& o) { for (auto t : list) { t.graph(o); } }
	//void genGraph(const char *gname);
	const Order* find(const std::string& name) const;
	void check(const ItemManager &I) const;
private:
	std::vector<Order> list;
};

#endif 