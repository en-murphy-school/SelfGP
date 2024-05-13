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

void readLongText(string text) {
    for (char c : text)
    {
        if (c == '|') {
            cout << endl;
        }
        else {
            cout << c;
        }
    }
    cout << endl;
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

    cout << "_______________________________________________________________________________" << endl;
    cout << "_______________________________________________________________________________" << endl;
    cout << endl;
    cout << "   _____                      _        _______                  _           " << endl;
    cout << "  / ____|                    | |      |__   __|                | |          " << endl;
    cout << " | |     ___  _ __  ___  ___ | | ___     | |_ __ __ ___   _____| | ___ _ __ " << endl;
    cout << " | |    / _ \\| '_ \\/ __|/ _ \\| |/ _ \\    | | '__/ _` \\ \\ / / _ \\ |/ _ \\ '__|" << endl;
    cout << " | |___| (_) | | | \\__ \\ (_) | |  __/    | | | | (_| |\\ V /  __/ |  __/ |   " << endl;
    cout << "  \\_____\\___/|_| |_|___/\\___/|_|\\___|    |_|_|  \\__,_| \\_/ \\___|_|\\___|_|   " << endl;
    cout << "                                                                            " << endl;
    cout << "_______________________________________________________________________________" << endl;
    cout << "_______________________________________________________________________________" << endl;
    cout << endl;




    
    //sP("Welcome message here!");
    //sP("What is your name traveler?");

    cout << "Welcome dear Traveler to our humble kingdom of Cline. A kingdom reaching as far \nas the eye can see. A kingdom which has a wide variety of scenery and towns." << endl;
    cout << endl;
    cout << "Ah, who am I kidding. I know you aren't into any of that. Only looking for rough \nand tough adventure. I get it, I used to feel the same when I was young. \n\nNow tell me, what is your name?" << endl;
    
    cin >> name;
    user.SetName(name);
    cout << endl;
    cout << "Alright " << user.GetName() << " the 'Eventual' great. Let me get you situated for your journey." << endl << endl;
    while (true)
    {
        cout << "Which of the bounties would you like to try and take on?" << endl << "Easy(1), Medium(2), Hard(3)" << endl;
        cout << "Enter your Choice: ";
        if (!(cin >> difficulty)) {
            cout << endl;
            cout << "Letters are not difficulties." << endl;
            cout << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
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
    user.SetMoney(money);

}

void addItem(Item* item) {
    user.addItem(item);
}


void firstIntro() {
    
    cout << endl;
    cout << user.GetName() << "...     Are you sure you're ready to take this quest? It looks like a tough one." << endl;
    cout << "" << endl;
    cout << "Either way, if it's adventure you want, you are sure to get it." << endl;
    cout << "Here, take some gold. Im sure it will help you during your travels." << endl;
    cout << endl;
    cout << "*** You gained " << user.GetMoney() << " gold." << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "Your adventure begins in " << currentLocation->getLocationName() << endl;
    cout << currentLocation->getLocationDescription() << endl;
    cout << "" << endl;
}

void getOptions() {
    cout << "**************************************" << endl;
    cout << "What would you like to do?" << endl;
    cout << "1. Explore " << currentLocation->getLocationName() << "." << endl;
    cout << "2. Enter " << currentLocation->getLocationName() << "'s shop." << endl;
    cout << "3. View your Inventory." << endl;
    cout << "4. Leave " << currentLocation->getLocationName() << "." << endl;
    cout << "**************************************" << endl;
    cout << endl;
}

void explore() {
    int choice;
    bool tf;
    vector<Item*> itemList = currentLocation->getHiddentItem();

    cout << endl;
    readLongText(currentLocation->getLocationExplore());
    cout << endl;
    cin >> choice;
    if (choice == 1) 
    {
        tf = true;
    }
    else if (choice == 2) {
        tf = false;
    }
    else {
        return;
    }

    if (tf == true && currentLocation->getLocationChoice() == true)
    {
        for (Item* item : itemList) {
            if (item->checkAvailability())
            {
                addItem(item);
                cout << endl;
                cout << "*** You obtained: " << item->getItemName() << endl;
                cout << endl;
                item->setAvailability(false);
            }
            else {
                cout << endl;
                cout << "You've already gathered all you can." << endl;
                cout << endl;
            }
        }
    }
    else if (tf == false && currentLocation->getLocationChoice() == false)
    {
        for (Item* item : itemList) {
            if (item->checkAvailability())
            {
                addItem(item);
                cout << endl;
                cout << "*** You obtained: " << item->getItemName() << endl;
                cout << endl;
                item->setAvailability(false);
            }
            else {
                cout << endl;
                cout << "You've already gathered all you can." << endl;
                cout << endl;
            }
        }
    }

}

void shop() {
    vector<Item*> stock = currentLocation->getStoreItems();
    int counter = 1;
    int choice;

    cout << endl;
    cout << "Welcome to " << currentLocation->getLocationName() << "'s shop." << endl;
    while (true) {
        cout << "---------------------------------------------------------------" << endl;

        for (Item* item : stock) {
            cout << counter << ". " << item->getItemName() << ": " << item->getItemDescription() << endl;
            cout << "Cost: " << item->getItemCost() << " gold." << endl;
            cout << "---------------------------------------------------------------" << endl;
            counter++;
        }
        cout << endl;
        cout << "Select the number that corresponds to the item you would like to buy. Or, press '0' to leave." << endl;
        if (!(cin >> choice)) {
            cout << endl;
            cout << "Letters are not numbers." << endl;
            cout << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        if (choice == 0) {
            cout << endl;
            cout << "You left the shop." << endl;
            cout << endl;
            break;
        }
        if (choice >= 1 && choice <= stock.size()) {
            addItem(stock[choice-1]);
            user.SetMoney(user.GetMoney() - stock[choice - 1]->getItemCost());
            cout << endl;
            cout << "*** You bought: " << stock[choice - 1]->getItemName() << ". " << endl;
            cout << endl;
            cout << "Thank you for shopping! Come back soon!" << endl;
            cout << endl;
            break;
        }
        else {
            cout << "Please choose from the selectable options" << endl;
        }
    }

}

void viewInventory() {
    cout << endl;
    vector<Item*> inventory = user.GetItems();

    cout << endl;
    cout << "_______________________________________________________________" << endl;
    cout << "You have " << user.GetMoney() << " gold." << endl;
    cout << endl;

    if (inventory.empty()) {
        cout << "Your inventory is empty... Womp Womp" << endl;
        cout << endl;
    }
    else {
        cout << "Inventory: " << endl;
        cout << "---------------------------------------------------------------" << endl;
        for (Item* item : inventory) {
            cout << "Name: " << item->getItemName() << "." << endl;
            cout << "Description: " << item->getItemDescription() << "." << endl;
            cout << endl;
            cout << "---------------------------------------------------------------" << endl;
        }
        cout << endl;
    }
}

void leaveTown() {
    cout << endl;
    int option = 0;
    while (option != 1 && option != 2) {
        cout << "Are you sure you would like to leave " << currentLocation->getLocationName() << "? (1:yes, 2 : no)" << endl;
        cin >> option;
        cout << endl;
    }

    if (option == 1) {
        currentNode = currentNode->getNext();
        if (currentNode != nullptr) {
            currentLocation = currentNode->getData();
            cout << "_______________________________________________________________" << endl;
            cout << "Your quest takes you to " << currentLocation->getLocationName() << endl;
            cout << endl;
            readLongText(currentLocation->getLocationDescription());
            cout << endl;
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
    
    int choice;

    generateItems();
    generateLocations();
    generatePlayer();

    currentNode = locationsList.getHead();
    if (currentNode != nullptr) 
    {
        currentLocation = currentNode->getData();
    }
    else {
        cout << "Error: No locations found." << endl;
        return 1;
    }
    
    firstIntro();


    while (finalLevel == false) {
        getOptions();
        cout << "Pick an option with numbers 1-4." << endl;
        if (!(cin >> choice)) { 
            cout << endl;
            cout << "Why not press a number you fool." << endl;
            cout << endl;
            cin.clear(); // Clear the fail state
            cin.ignore(1000, '\n');
            continue; 
        }
        switch (choice) {
        case 1:
            explore();
            break;
        case 2:
            shop();
            break;
        case 3:
            viewInventory();
            break;
        case 4:
            leaveTown();
            break;
        default:
            cout << endl;
            cout << "Choose a number from the options! Don't wanna get lost doing sidequests!" << endl;
            cout << endl;
            continue;
        }
    }

   
    cout << "start final battle here" << endl;
   

    return 0;
}