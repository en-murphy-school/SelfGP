#pragma once

#ifndef ITEM_H
#define ITEM_H

#include<iostream>
#include <string>
using namespace std;

class Item {
protected:
	string name;
	string description;
	int cost;
	bool availability;
public:
	Item();
	Item(const string& name, const string& description, const int& cost, const bool& availability);
	string getItemName() const;
	void setItemName(const string& name);
	string getItemDescription() const;
	void setItemDescription(const string& description);
	int getItemCost() const;
	void setItemCost(const int& cost);
	bool checkAvailability() const;
	void setAvailability(const bool& availability);
	virtual void printItem() const = 0;
};

#endif
