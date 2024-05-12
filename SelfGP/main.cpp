#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>


#include "Weapon.h"
#include "Armor.h"
#include "LinkedList.h"
#include "Player.h"

using namespace std;


Item* items[100];
int itemCount = 0;
LinkedList locationsList;
Player user;
Node* currentNode;
Location* currentLocation;
bool finalLevel = false;

void sP(string text) {

    for (int i = 0; i < text[i]; i++) {

        cout << text[i];

        Sleep(50);
    }
    cout << endl;
}

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
        itemName = formatName(itemName);
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
    string explore;
    string choice;
    string storeItems;
    string hiddenItems;
    bool tf;

    while (inputFile >> name >> description >> explore >> choice >> storeItems >> hiddenItems) {

        if (choice == "true")
        {
            tf = true;
        }
        else {
            tf = false;
        }

        description = formatDescription(description);
        explore = formatDescription(explore);
        storeItems = formatDescription(storeItems);
        hiddenItems = formatDescription(hiddenItems);
        vector<Item*> storeList = getItemList(storeItems);
        vector<Item*> hiddenList = getItemList(hiddenItems);

        Location* testLoc = new Location(name, description, explore, tf, storeList, hiddenList);
        Node* newNode = new Node(testLoc);
        locationsList.pushBack(newNode);
        cout << "Location Made" << endl;
    }
}

void generatePlayer() {
    string name;
    int difficulty;
    int money;
    
    //sP("Welcome message here!");
    //sP("What is your name traveler?");

    cout << "Welcome message here!" << endl;
    cout << "What is your name traveler?" << endl;
    
    cin >> name;
    cout << "Chatter message here" << endl << endl;
    while (true)
    {
        cout << "What difficulty would you like to play on?" << endl << "Easy(1), Medium(2), Hard(3)" << endl;
        cout << "Enter your Choice: ";
        cin >> difficulty;
        cout << endl;
        
        if (difficulty >= 1 && difficulty <= 3) {
            break;
        } else {
            cout << "Please choose from the selectable options" << endl;
        }
    }

    if (difficulty == 1) {
        money = 2000;
    } else if (difficulty == 2) {
        money = 1000;
    }
    else {
        money = 500;
    }

    user.SetName(name);
    user.SetMoney(money);

}


void getOptions() {

}

void explore() {

}

void shop() {

}

void viewInventory() {

}

void leaveTown() {
    int option = 0;
    while (option != 1 && option != 2) {
        cout << "Are you sure you would like ot leave town? ( 1:yes, 2:no )" << endl;
        cin >> option;
    }

    if (option == 1) {
        currentNode = currentNode->getNext();
        if (currentNode != nullptr) {
            currentLocation = currentNode->getData();
            cout << currentLocation->getLocationDescription();
        }
        else {
            //************************************************************************* Create final level from here
            cout << "You have left the last location." << endl;
            finalLevel = true;
        }
    }
    else {
        cout << "No current location set." << endl;
    }
}


int main() {
    
    char choice;

    generateItems();
    generateLocations();

    generatePlayer();

    currentNode = locationsList.getHead();

    cout << user.GetName() << ": " << user.GetMoney() << endl;


    

    while (finalLevel == false) {
        getOptions();
        cout << "pick a choice" << endl;
        cin >> choice;
        switch (choice) {
        case '1':
            explore();
            break;
        case '2':

            break;
        case '3':
            
            break;
        case '4':
            leaveTown();
            break;
        default:
            
            continue;
        }
    }

   
    cout << "start final battle here" << endl;
   

    return 0;
}