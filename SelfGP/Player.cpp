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

vector<Item*> Player::GetItems() const {
    return this->items;
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

void Player::SetItems(vector<Item*> newItems) {
    items = newItems;
}



void Player::addItem(Item* newItem) {
    items.push_back(newItem);
}