#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item {
private:
    int attack;
    int magic;
public:
    Weapon();
    Weapon(const string& name, const string& description, const int& cost,
        const bool& availability, const int& attack, const int& magic);
    int getAttack() const;
    void setAttack(const int& attack);
    int getMagic() const;
    void setMagic(const int& magic);
    void printItem() const;
};

#endif