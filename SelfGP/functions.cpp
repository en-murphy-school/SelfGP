#include "functions.h"
#include <windows.h> // For Sleep function

using namespace std;

// Function definition
void delayedPrint(ostream& os, const string& text) {
    for (int i = 0; i < text.length(); i++) {
        cout << text[i];
        Sleep(20);
    }
}

// Constructor definition
DelayedOstream::DelayedOstream(ostream& stream) : stream(stream) {}

// Overload the << operator for strings
DelayedOstream& DelayedOstream::operator<<(const string& text) {
    delayedPrint(stream, text);
    return *this;
}