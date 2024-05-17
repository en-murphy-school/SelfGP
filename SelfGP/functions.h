#ifndef DELAYEDOSTREAM_H
#define DELAYEDOSTREAM_H

#include <iostream>
#include <string>

void delayedPrint(std::ostream& os, const std::string& text);

class DelayedOstream {
public:
    // Constructor taking an ostream reference
    DelayedOstream(std::ostream& stream);

    // Overload the << operator for strings
    DelayedOstream& operator<<(const std::string& text);

    // Overload the << operator for other types
    template<typename T>
    DelayedOstream& operator<<(const T& data) {
        stream << data;
        return *this;
    }

private:
    std::ostream& stream;
};

#endif // DELAYEDOSTREAM_H