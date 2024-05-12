#include "Location.h"

Location::Location() {
    (*this).name = "Default Name";
    (*this).description = "Default Description";
}

Location::Location(const string& name, const string& description, vector<Item*>& storeItems) {
    (*this).name = name;
    (*this).description = description;
    (*this).storeItems = storeItems;
}

Location::Location(const string& name, const string& description, const string& explore, bool choice, vector<Item*>& storeItems, vector<Item*> hiddenItems) {
    (*this).name = name;
    (*this).description = description;
    (*this).explore = explore;
    (*this).choice = choice;
    (*this).storeItems = storeItems;
    (*this).hiddenItems = hiddenItems;
}

string Location::getLocationExplore() {
    return (*this).explore;
}

void Location::setLocationExplore(const string& newExplore) {
    (*this).explore = newExplore;
}

bool Location::getLocationChoice()  {
    return (*this).choice;
}

void Location::setLocationChoice(const bool& newChoice) {
    (*this).choice = newChoice;
}

string Location::getLocationName() const {
    return (*this).name;
}

void Location::setLocationName(const string& name) {
    (*this).name = name;
}

string Location::getLocationDescription() const {
    return (*this).description;
}

void Location::setLocationDescription(const string& description) {
    (*this).description = description;
}

vector<Item*> Location::getStoreItems() const {
    if ((*this).storeItems.size() == 0) {
        cout << "There are no items in this store!" << endl;
    }

    return (*this).storeItems;
}

void Location::addStoreItem(Item* item) {
    (*this).storeItems.push_back(item);
}

void Location::removeStoreItem(Item* item) {
    for (vector<Item*>::iterator it = storeItems.begin(); it != storeItems.end(); it++) {
        if ((*it)->getItemName() == item->getItemName()) {
            delete* it;
            storeItems.erase(it);
            return;
        }
    }
}

bool Location::findItem(const string& itemName) const {
    for (vector<Item*>::const_iterator it = (*this).storeItems.begin(); it != (*this).storeItems.end(); it++) {
        if ((*it)->getItemName() == itemName) {
            return true;
        }
    }
    return false;
}

vector<Item*> Location::getHiddentItem() const {
    return (*this).hiddenItems;
}

void Location::addHiddenItems(Item* item) {
    (*this).hiddenItems.push_back(item);
}

void Location::removeHiddenItem(Item* item) {
    for (vector<Item*>::iterator it = hiddenItems.begin(); it != hiddenItems.end(); it++) {
        if ((*it)->getItemName() == item->getItemName()) {
            delete* it;
            hiddenItems.erase(it);
            return;
        }
    }
}



void Location::printStoreItems() {
    for (int i = 0; i < storeItems.size(); i++) {
        storeItems.at(i)->printItem();
        cout << endl;
    }
}

void Location::printHiddenItems() {
    for (int i = 0; i < hiddenItems.size(); i++) {
        hiddenItems.at(i)->printItem();
        cout << endl;
    }
}



