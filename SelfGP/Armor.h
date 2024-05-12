#pragma once
#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"

class Armor : public Item
{
    private:
        int defense;
        int evasion;
    public:
        Armor();
        Armor(const string& name, const string& description, const int& cost,
            const bool& availability, const int& defense, const int& evasion);
        int getDefense() const;
        void setDefense(const int& defense);
        int getEvasion() const;
        void setEvasion(const int& evasion);
        void printItem() const;


};

#endif