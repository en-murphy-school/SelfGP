#ifndef PLAYER_H
#define PLAYER_H
#include "Item.h"
#include "Location.h"
#include <string>
#include <vector>


class Player {
private:
    int money;
    string name;
    vector<Item*> items;
    Location currentLocation;

public:
    // Constructors and getters/setters
    Player();
    Player(int money, string name, vector<Item*>& items, Location currentLocation);

    string GetName() const;
    int GetMoney();
    // Item[] GetItemList();
    // Node* GetCurrentLocation();

    void SetName(string newName);
    void SetMoney(int newMoney);
    //void SetItemList(Item[]* newItemList);
    //void SetCurrentLocation(Node* newCurrentLocation);
};

#endif