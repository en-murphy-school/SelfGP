#ifndef PLAYER_H
#define PLAYER_H
#include "Item.h"
#include <string>
#include <vector>


class Player {
private:
    int money;
    string name;
    vector<Item*> items;

public:
    // Constructors and getters/setters
    Player();
    Player(int money, string name);

    string GetName() const;
    int GetMoney();
    vector<Item*> GetItems() const;

    void SetName(string newName);
    void SetMoney(int newMoney);
    void SetItems(vector<Item*> newItems);
    

    void addItem(Item* newItem);
};

#endif