#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Weapon.h"
#include "Armor.h"
#include "LinkedList.h"


using namespace std;

Item* items[100];
int itemCount = 0;
LinkedList locationsList;

string formatName(const string& inputName) {
    string formattedName;
    for (char c : inputName)
    {
        if (isupper(c))
        {
            formattedName += ' ';
        }
        formattedName += c;
    }
    return formattedName;
}

string formatDescription(const string& inputDescription) {
    string formattedDescription;
    for (char c : inputDescription) 
    {
        if (c == '-') 
        {
            formattedDescription += ' '; 
        }
        else {
            formattedDescription += c;
        }
    }
    return formattedDescription;
}


vector<Item*> getItemList(string list) {
    vector<Item*> finalList;

    vector<Item*> itemList;

    size_t start = 0, end;
    while ((end = list.find(" ", start)) != string::npos) 
    {
        string itemName = list.substr(start, end - start);
        for (int i = 0; i < 100; ++i) 
        {
            if (items[i] != nullptr && items[i]->getItemName() == itemName) 
            {
                itemList.push_back(items[i]);
                break; 
            }
        }
        start = end + 1; 
    }

    if (start < list.length()) 
    {
        string itemName = list.substr(start);
        for (int i = 0; i < 100; ++i) 
        {
            if (items[i] != nullptr && items[i]->getItemName() == itemName) 
            {
                itemList.push_back(items[i]);
                break;
            }
        }
    }
    return itemList;
}

void generateItems() {
    ifstream inputFile("items.txt");

    if (!inputFile) 
    {
        cerr << "Failed to open file." << endl;
        return;
    }

    string type;
    string name;
    string description;
    int cost;
    string available;
    int value1, value2;
    bool tf;

    while (inputFile >> type >> name >> description >> cost >> available >> value1 >> value2) 
    {

        if (available == "true")
        {
            tf = true;
        }
        else {
            tf = false;
        }

        if (type == "WEAPON") 
        {
            name = formatName(name);
            description = formatDescription(description);
            Weapon* newWeapon = new Weapon(name, description, cost, tf, value1, value2);
            cout << "Weapon Made" << endl;
            items[itemCount] = newWeapon;
            itemCount++;
        } else if (type == "ARMOR") {
            name = formatName(name);
            description = formatDescription(description);
            Armor* newArmor = new Armor(name, description, cost, tf, value1, value2);
            cout << "Armor Made" << endl;
            items[itemCount] = newArmor;
            itemCount++;
        }
    }
    cout << endl;
    inputFile.close();
}

void generateLocations() {

    ifstream inputFile("locations.txt");

    if (!inputFile)
    {
        cerr << "Failed to open file." << endl;
        return;
    }

    string name;
    string description;
    string storeItems;
    string hiddenItems;

    while (inputFile >> name >> description >> storeItems >> hiddenItems) {

        description = formatDescription(description);
        storeItems = formatDescription(storeItems);
        hiddenItems = formatDescription(hiddenItems);
        vector<Item*> storeList = getItemList(storeItems);
        vector<Item*> hiddenList = getItemList(hiddenItems);

        Location* testLoc = new Location(name, description, storeList, hiddenList);
        locationsList.pushBack(testLoc);
    }

   





}




int main() {

    generateItems();
    generateLocations();

    cout << "hi" << endl;


    for (int i = 0; i < itemCount; ++i) {
        Item* currentItem = items[i];

        if (Armor* armorItem = dynamic_cast<Armor*>(currentItem)) {
            cout << armorItem->getItemName() << ": ";
            cout << "Defense: " << armorItem->getDefense() << endl;
        }
    }


    cout << endl;

    Node* current = locationsList.getHead();
    while (current != nullptr) {
        Location* location = current->getData();
        cout << "Location Name: " << location->getLocationName() << endl;
        cout << "Description: " << location->getLocationDescription() << endl;
        current = current->getNext();
    }

   


    return 0;
}