#include "Item.h"

Item::Item() {
    (*this).name = "Default Name";
    (*this).description = "Default Description ";
    (*this).cost = 0;
    (*this).availability = false;
}

Item::Item(const string& name, const string& description, const int& cost, const bool& availability) {
    (*this).name = name;
    (*this).description = description;
    (*this).cost = cost;
    (*this).availability = availability;
}

string Item::getItemName() const {
    return (*this).name;
}

void Item::setItemName(const string& name) {
    (*this).name = name;
}

string Item::getItemDescription() const {
    return (*this).description;
}

void Item::setItemDescription(const string& description) {
    (*this).description = description;
}

int Item::getItemCost() const {
    return (*this).cost;
}

void Item::setItemCost(const int& cost) {
    (*this).cost = cost;
}

bool Item::checkAvailability() const {
    return (*this).availability;
}

void Item::setAvailability(const bool& availability) {
    (*this).availability = availability;
}

