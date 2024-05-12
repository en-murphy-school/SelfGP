#include "Armor.h"

Armor::Armor() {
    (*this).name = "Default Name";
    (*this).description = "Default Description";
    (*this).cost = 0;
    (*this).availability = false;
    (*this).defense = 0;
    (*this).evasion = 0;
}

Armor::Armor(const string& name, const string& description, const int& cost,
    const bool& availability, const int& defense, const int& evasion) {
    (*this).name = name;
    (*this).description = description;
    (*this).cost = cost;
    (*this).availability = availability;
    (*this).defense = defense;
    (*this).evasion = evasion;
}

int Armor::getDefense() const {
    return (*this).defense;
}

void Armor::setDefense(const int& defense) {
    (*this).defense = defense;
}

int Armor::getEvasion() const {
    return (*this).evasion;
}

void Armor::setEvasion(const int& evasion) {
    (*this).evasion = evasion;
}

void Armor::printItem() const {
    cout << "Name: " << (*this).getItemName() << "\n"
        << "Description: " << (*this).getItemDescription() << "\n"
        << "Cost: " << (*this).getItemCost() << "\n"
        << "Availability: " << (*this).checkAvailability() << "\n"
        << "Defense: " << (*this).getDefense() << "\n"
        << "Evasion: " << (*this).getEvasion() << endl;
}