#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <thread>

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
void printStats(int attack, int magic, int defense, int evasion);
void stealthBattle(int attack, int magic, int defense, int evasion);
void attackBattle(int attack, int magic, int defense, int evasion);
void printWin();
void printLoss();

class SlowStream {
public:
    SlowStream(int delay_ms) : delay_(delay_ms) {}

    // Overload the << operator for SlowStream
    SlowStream& operator<<(const string& text) {
        for (char c : text) {
            cout << c << flush;  // Print each character to cout
            this_thread::sleep_for(chrono::milliseconds(delay_));
        }
        return *this;
    }

private:
    int delay_;
};

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
            //cout << "Weapon Made" << endl;
            items[itemCount] = newWeapon;
            itemCount++;
        } else if (type == "ARMOR") {
            name = formatName(name);
            description = formatDescription(description);
            Armor* newArmor = new Armor(name, description, cost, tf, value1, value2);
            //cout << "Armor Made" << endl;
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
        //cout << "Location Made" << endl;
    }
}

void generatePlayer() {
    SlowStream sout(20);
    string name;
    int difficulty;
    int money;
    sout << "_______________________________________________________________________________";
    cout << endl;
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
    sout << "_______________________________________________________________________________";
    cout << endl;
    cout << endl;
    sout << "Welcome dear Traveler to our humble kingdom of Cline. A kingdom reaching as far \nas the eye can see. A kingdom which has a wide variety of scenery and towns.";
    cout << endl;
    cout << endl;
    sout << "Ah, who am I kidding. I know you aren't into any of that. Only looking for rough \nand tough adventure. I get it, I used to feel the same when I was young. \n\nNow tell me, what is your name?";
    cout << endl;
    
    cin >> name;
    user.SetName(name);
    cout << endl;
    sout << "Alright " + user.GetName() + " the 'Eventual' great. Let me get you situated for your journey.";
    cout << endl;
    cout << endl;
    while (true)
    {
        sout << "Which of the bounties would you like to try and take on?";
        cout << endl;
        sout << "Easy(1), Medium(2), Hard(3)";
        cout << endl;
        sout << "Enter your Choice: ";
        cout << endl;
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
    SlowStream sout(20);
    cout << endl;
    sout << user.GetName() + "...     Are you sure you're ready to take this quest? It looks like a tough one.";
    cout << endl;
    cout << endl;
    sout << "Either way, if it's adventure you want, you are sure to get it.";
    cout << endl;
    sout << "Here, take some gold. Im sure it will help you during your travels.";
    cout << endl;
    cout << endl;
    sout << "*** You gained " + to_string(user.GetMoney()) + " gold.";
    cout << endl;
    cout << "" << endl;
    cout << "" << endl;
    sout << "Your adventure begins in " + currentLocation->getLocationName();
    cout << endl;
    cout << currentLocation->getLocationDescription() << endl;
    cout << "" << endl;
}

void getOptions() {
    SlowStream sout(20);
    cout << "**************************************" << endl;
    sout << "What would you like to do?";
    cout << endl;
    sout << "1. Explore " + currentLocation->getLocationName() + ".";
    cout << endl;
    sout << "2. Enter " + currentLocation->getLocationName() + "'s shop.";
    cout << endl;
    sout << "3. View your Inventory.";
    cout << endl;
    sout << "4. Leave " + currentLocation->getLocationName() + ".";
    cout << endl;
    cout << "**************************************" << endl;
    cout << endl;
}

void explore() {
    SlowStream sout(20);
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
                sout << "*** You obtained: " + item->getItemName();
                cout << endl;
                cout << endl;
                item->setAvailability(false);
            }
            else {
                cout << endl;
                sout << "You've already gathered all you can.";
                cout << endl;
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
                sout << "*** You obtained: " + item->getItemName();
                cout << endl;
                cout << endl;
                item->setAvailability(false);
            }
            else {
                cout << endl;
                sout << "You've already gathered all you can.";
                cout << endl;
                cout << endl;
            }
        }
    }
}

void shop() {
    SlowStream sout(20);
    vector<Item*> stock = currentLocation->getStoreItems();
    int counter = 1;
    int choice;

    cout << endl;
    sout << "Welcome to " + currentLocation->getLocationName() + "'s shop.";
    cout << endl;
    while (true) {
        cout << "---------------------------------------------------------------" << endl;

        for (Item* item : stock) {
            sout << to_string(counter) + ". " + item->getItemName() + ": " + item->getItemDescription();
            cout << endl;
            sout << "Cost: " + to_string(item->getItemCost()) + " gold.";
            cout << endl;
            cout << "---------------------------------------------------------------" << endl;
            counter++;
        }
        cout << endl;
        sout << "Select the number that corresponds to the item you would like to buy. Or, press '0' to leave.";
        cout << endl;
        if (!(cin >> choice)) {
            cout << endl;
            cout << "Letters are not numbers." << endl;
            cout << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        if (choice == 0) {
            cout << endl;
            sout << "You left the shop.";
            cout << endl;
            cout << endl;
            break;
        }
        if (choice >= 1 && choice <= stock.size()) {
            if (user.GetMoney() < stock[choice - 1]->getItemCost()) {
                cout << endl;
                sout << "You don't have enough money for that!";
                cout << endl;
                cout << endl;
                break;
            }
            addItem(stock[choice-1]);
            user.SetMoney(user.GetMoney() - stock[choice - 1]->getItemCost());
            cout << endl;
            sout << "*** You bought: " + stock[choice - 1]->getItemName() + ". ";
            cout << endl;
            cout << endl;
            sout << "Thank you for shopping! Come back soon!";
            cout << endl;
            cout << endl;
            break;
        }
        else {
            cout << "Please choose from the selectable options" << endl;
            counter = 1;
        }
    }

}

void viewInventory() {
    SlowStream sout(20);
    cout << endl;
    vector<Item*> inventory = user.GetItems();

    cout << endl;
    cout << "_______________________________________________________________" << endl;
    sout << "You have " + to_string(user.GetMoney()) + " gold.";
    cout << endl;
    cout << endl;

    if (inventory.empty()) {
        sout << "Your inventory is empty... Womp Womp";
        cout << endl;
        cout << endl;
    }
    else {
        sout << "Inventory: ";
        cout << endl;
        cout << "---------------------------------------------------------------" << endl;
        for (Item* item : inventory) {
            sout << "Name: " + item->getItemName() + ".";
            cout << endl;
            sout << "Description: " + item->getItemDescription();
            cout << endl;
            cout << endl;
            cout << "---------------------------------------------------------------" << endl;
        }
        cout << endl;
    }
}

void leaveTown() {
    SlowStream sout(20);
    cout << endl;
    int option = 0;
    while (option != 1 && option != 2) {
        sout << "Are you sure you would like to leave " + currentLocation->getLocationName() + "? (1:yes, 2 : no)";
        cout << endl;
        cin >> option;
        cout << endl;
    }

    if (option == 1) {
        currentNode = currentNode->getNext();
        if (currentNode != nullptr) {
            currentLocation = currentNode->getData();
            cout << "______________________________________________________________" << endl;
            cout << endl;
            sout << "Your quest takes you to " + currentLocation->getLocationName();
            cout << endl;
            cout << endl;
            readLongText(currentLocation->getLocationDescription());
            cout << endl;
        }
        else {
            //************************************************************************* Create final level from here
            cout << "_______________________________________________________________" << endl;
            cout << "You have left the last town, and move to the Beast's den." << endl;
            finalLevel = true;
        }
    }
    else {
        cout << "No current location set." << endl;
    }
}


int get12Choice() {
    int choice;
    while (true)
    {
        cout << endl;
        cout << "Enter the number for the option you want" << endl;
        if (!(cin >> choice)) {
            cout << endl;
            cout << "Letters are not choices, you should know this by now." << endl;
            cout << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout << endl;
        if (choice == 1 || choice == 2) {
            break;
        }
        else {
            cout << "Please choose from the selectable options" << endl;
        }
    }

    return choice;
}
int getRand() {
    int randomNumber = rand() % 20 + 1;
    return randomNumber;
}

void finalBattle() {
    SlowStream sout(20);
    int attack=0;
    int magic=0;
    int defense=0;
    int evasion=0;
    int choice1;

    vector<Item*> inventory = user.GetItems();
    for (Item* item : inventory) {
        Weapon* weapon = dynamic_cast<Weapon*>(item);
        if (weapon != nullptr) {
            attack += weapon->getAttack();
            magic += weapon->getMagic();
        }
        else {
            Armor* armor = dynamic_cast<Armor*>(item);
            defense += armor->getDefense();
            evasion += armor->getEvasion();
        }
    }

    attack /= locationsList.Size();
    magic /= locationsList.Size();
    defense /= locationsList.Size();
    evasion /= locationsList.Size();

    cout << endl;
    sout << "As you take one final look at your gear, you think to yourself: ";
    cout << endl;
    printStats(attack, magic, defense, evasion);

    cout << endl;
    sout << "You see your foe before you, the stature matching the picture on the bounty.";
    cout << endl;
    sout << "From the look of things, it seems you have 2 options.";
    cout << endl;
    sout << "1. Go with a more stealthy approach               2. Go with a guaranteed hit attack";
    cout << endl;

    choice1 = get12Choice();

    if (choice1 == 1) {
        stealthBattle(attack,magic,defense,evasion);
    }
    else {
        attackBattle(attack, magic, defense, evasion);
    }
}

void printStats(int attack, int magic, int defense, int evasion) {
    SlowStream sout(20);
    int stats[] = { attack, magic, defense, evasion};
    string words[] = { "Attack", "Magic", "Defense", "Evasion" };

    for (int i = 0; i < 4; i++) {
        sout << "I feel like my " + words[i] + " is ";
        if (stats[i]<8) {
            cout << "Bad." << endl;
        }
        else if (stats[i]<12) {
            cout << "Alright" << endl;
        }
        else if (stats[i]<20) {
            cout << "Pretty Amazing" << endl;
        }
        else {
            cout << "Perfect." << endl;
        }
    }
}

void stealthBattle(int attack, int magic, int defense, int evasion) {
    SlowStream sout(20);
    int choice;
    int choice2;
    cout << endl;
    sout << "You approach the sleeping beast cautiously, trying not to make a sound.";
    cout << endl;
    sout << ".   .   .";
    cout << endl;

    if (evasion > 20) {
        sout << "You manage to sneak up to the beast's weakest point, giving him a quick and precise end.";
        cout << endl;
        printWin();
        return;
    }
    else {
        sout << "Your footsteps accidentally disturb the beast's slumber, and it wakes up.";
        cout << endl;
        if (getRand() + defense < 20) {
            sout << "The beast notices you and launches an unreactable attack.";
            cout << endl;
            printLoss();
            return;
        }
    }
    sout << "With the beast now awake, it fixes its gaze upon you.";
    cout << endl << endl;
    sout << "WHO DARES INTRUDE UPON MY DOMAIN? I, THE MIGHTY PYUTORR WILL NEVER FALL TO SUCH AN ATTEMPT";
    cout << endl;
    cout << endl;
    sout << "The beast prepares to cast a spell at you rapidly. Quick! What would you like to do?";
    cout << endl;
    sout << "1. Try to dodge               2. Try to counter with magic";
    cout << endl << endl;
    choice = get12Choice();

    if (choice == 1) {
        if (getRand() + evasion < 22) {
            sout << "Your attempt to dodge is unsuccessful.";
            cout << endl;
            printLoss();
            return;
        }
        sout << "You manage to avoid Pyutorr's attack.";
        cout << endl;
    }
    else {
        if (getRand() + magic < 18) {
            sout << "Your magic is not strong enough to counter the beast's spell.";
            cout << endl;
            printLoss();
            return;
        }
        sout << "Your magic overpowers the beast's spell, dispelling it.";
        cout << endl;
    }
    cout << endl;
    sout << "After that last attack, Pyutorr is REALLY angry. He starts to charge up a stronger blast. you decide you NEED to finish him off before this attack comes out.";
    cout << endl;
    sout << "1. Try to finish him with an attack               2. Try to finish him with magic";
    cout << endl;
    choice2 = get12Choice();
    if (choice2 == 1) {
        if (getRand() + attack > 20) {
            sout << "Just in the nick of time, your weapon strikes into Pyutorr, making his attack impode on himself!";
            cout << endl;
            printWin();
            return;
        }
        else {
            sout << "Your attack seems to just barely not stop him. And as Pyutorr fires his blast, your life flashes before your eyes.";
            cout << endl;
            printLoss();
            return;
        }
    }
    else {
        if (getRand() + magic > 18) {
            sout << "Just in the nick of time, your spell causes the blast Pyutorr was forming to combust.";
            cout << endl;
            printWin();
            return;
        }
        else {
            sout << "Your spell seems to just not do enough to the blast Pyutor was forming.";
            cout << endl;
            printLoss();
            return;
        }
    }
}

void attackBattle(int attack, int magic, int defense, int evasion) {
    SlowStream sout(20);
    int choice;
    int choice2;
    cout << endl;
    sout << "You charge at the beast, weapon in hand, and ";
    cout << endl;
    sout << ".   .   .";
    cout << endl;
    if (attack > 20) {
        sout << "IT HITS. Catching the beast off gaurd, you kill him instantly.";
        cout << endl;
        printWin();
        return;
    }
    else if(getRand() + attack>15){
        sout << "Your attack hits, however, the beast is still alive and now, wakes up angerly. ";
        cout << endl;
    }
    else {
        sout << "Your attack bounces right off the beast. He is now woken with the threat of danger.";
        cout << endl;
        if (getRand() + defense < 20) {
            sout << "He instantly slams you with its giant tail, knocking you unconcious. ";
            cout << endl;
            printLoss();
            return;
        }
    }
    sout << "With the beast now awake, he speaks to you.";
    cout << endl;
    sout << "HOW DARE YOU TRY AND SLAIN ME, FOR I, THE GREAT PYUTORR WAS ENJOYING A NICE REST.";
    cout << endl;
    cout << endl;
    sout << "Pyutorr then sends fire in your direction immediately, giving you no time to prepare. What would you like to do?";
    cout << endl;
    sout << "1. Try to dodge               2. Try to tank it";
    cout << endl;
    choice = get12Choice();

    if (choice == 1) {
        if (getRand() + evasion < 22) {
            sout << "You were unable to dodge Pyutorr's flames.";
            cout << endl;
            printLoss();
            return;
        }
        sout << "You barely manage to dodge Pyutorr's attack.";
        cout << endl;
    }
    else {
        if (getRand() + defense < 22) {
            sout << "You were unable to withstand the hit. ";
            cout << endl;
            printLoss();
            return;
        }
        sout << "You barely seem to be holding on after that last attack, but alive nonetheless.";
        cout << endl;
    }

    cout << endl;
    sout << "After that last attack, Pyutorr is REALLY angry. He starts to charge up a stronger blast. you decide you NEED to finish him off before this attack comes out.";
    cout << endl;
    sout << "1. Try to finish him with an attack               2. Try to finish him with magic";
    cout << endl;
    choice2 = get12Choice();

    if (choice2 == 1) {
        if (getRand() + attack > 20) {
            sout << "Just in the nick of time, your weapon strikes into Pyutorr, making his attack impode on himself!";
            cout << endl;
            printWin();
            return;
        }
        else {
            sout << "Your attack seems to just barely not stop him. And as Pyutorr fires his blast, your life flashes before your eyes.";
            cout << endl;
            printLoss();
            return;
        }
    }
    else {
        if (getRand() + magic > 18) {
            sout << "Just in the nick of time, your spell causes the blast Pyutorr was forming to combust.";
            cout << endl;
            printWin();
            return;
        }
        else {
            sout << "Your spell seems to just not do enough to the blast Pyutor was forming.";
            cout << endl;
            printLoss();
            return;
        }
    }
}

void printWin() {
    SlowStream sout(20);
    sout << "____________________________________________________";
    cout << endl;
    cout << endl;
    cout << "\\ \\   / /          \\ \\        / (_)     | |" << endl;
    cout << " \\ \\_/ /__  _   _   \\ \\  /\\  / / _ _ __ | |" << endl;
    cout << "  \\   / _ \\| | | |   \\ \\/  \\/ / | | '_ \\| |" << endl;
    cout << "   | | (_) | |_| |    \\  /\\  /  | | | | |_|" << endl;
    cout << "   |_|\\___/ \\__,_|     \\/  \\/   |_|_| |_|(_)" << endl;
    sout << "____________________________________________________";
    cout << endl;
    cout << endl << endl;
    sout << "You have slain the beast, Pyutorr. His mountains of riches put the bounty reward to shame.";
    cout << endl;
    sout << "You now have all you need to live a life of pure luxury, in any kingdom that you please.";
    cout << endl;
}

void printLoss() {
    SlowStream sout(20);
    sout << "____________________________________________________";
    cout << endl;
    cout << endl;
    cout << "  _____                         ____                 " << endl;
    cout << " / ____|                       / __ \\                " << endl;
    cout << "| |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ " << endl;
    cout << "| | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|" << endl;
    cout << "| |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   " << endl;
    cout << " \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   " << endl;
    cout << "                                                    " << endl;
    cout << "                                                    " << endl;
    sout << "____________________________________________________";
    cout << endl;
}


int main() {
    SlowStream sout(20);
    
    srand(time(nullptr));
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
        sout << "Pick an option with numbers 1-4.";
        cout << endl;
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

    cout << endl;
    sout << "You have finally reached the end of your quest. Hopefully all the items you have collected will help in this battle";
    
    cout << endl;

    finalBattle();
    
    cout << " _______ _                 _                           __             _____  _             _             _ " << endl;
    cout << " |__   __| |               | |                         / _|           |  __ \\| |           (_)           | |" << endl;
    cout << "    | |  | |__   __ _ _ __ | | __  _   _  ___  _   _  | |_ ___  _ __  | |__) | | __ _ _   _ _ _ __   __ _| |" << endl;
    cout << "    | |  | '_ \\ / _` | '_ \\| |/ / | | | |/ _ \\| | | | |  _/ _ \\| '__| |  ___/| |/ _` | | | | | '_ \\ / _` | |" << endl;
    cout << "    | |  | | | | (_| | | | |   <  | |_| | (_) | |_| | | || (_) | |    | |    | | (_| | |_| | | | | | (_| |_|" << endl;
    cout << "    |_|  |_| |_|\\__,_|_| |_|_|\\_\\  \\__, |\\___/ \\__,_| |_| \\___/|_|    |_|    |_|\\__,_|\\__, |_|_| |_|\\__, (_) " << endl;
    cout << "                                    __/ |                                              __/ |         __/ |  " << endl;
    cout << "                                   |___/                                              |___/         |___/   " << endl;

    return 0;
}