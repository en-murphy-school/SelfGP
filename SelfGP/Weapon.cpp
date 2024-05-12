#include "Weapon.h"

Weapon::Weapon() {
    (*this).name = "Default Name";
    (*this).description = "Default Description";
    (*this).cost = 0;
    (*this).availability = false;
    (*this).attack = 0;
    (*this).magic = 0;

}

Weapon::Weapon(const string& name, const string& description, const int& cost,
    const bool& availability, const int& attack, const int& magic) {
    (*this).name = name;
    (*this).description = description;
    (*this).cost = cost;
    (*this).availability = availability;
    (*this).attack = attack;
    (*this).magic = magic;
}

int Weapon::getAttack() const {
    return (*this).attack;
}

void Weapon::setAttack(const int& attack) {
    (*this).attack = attack;
}

int Weapon::getMagic() const {
    return (*this).magic;
}

void Weapon::setMagic(const int& magic) {
    (*this).magic = magic;
}

void Weapon::printItem() const {
    cout << "Name: " << (*this).getItemName() << "\n"
        << "Description: " << (*this).getItemDescription() << "\n"
        << "Cost: " << (*this).getItemCost() << "\n"
        << "Availability: " << (*this).checkAvailability() << "\n"
        << "Attack: " << (*this).getAttack() << "\n"
        << "Magic: " << (*this).getMagic() << endl;
}