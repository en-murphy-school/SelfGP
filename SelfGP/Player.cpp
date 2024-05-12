#include "Player.h"
#include <string>
#include <iostream>
using namespace std;



Player::Player() {
    int money = 0;
    string name = "";
    vector<Item*> items;
}

Player::Player(int money, string name) {
    this->money = money;
    this->name = name;
    vector<Item*> items;
}

string Player::GetName() const {
    return this->name;
}
void Player::SetName(string newName) {
    this->name = newName;
}

int Player::GetMoney() {
    return money;
}

void Player::SetMoney(int newMoney) {
    money = newMoney;
}


/*
Item[] Player::GetItemList() {
    return itemList;
}

void SetItemList(Item[]* newItemList) {
    itemList = newItemList;
}

Node* GetCurrentLocation() {
    return currentLocation;
}

void SetCurrentLocation(Node* newCurrentLocation) {
    currentLocation = newCurrentLocation;
}
*/

