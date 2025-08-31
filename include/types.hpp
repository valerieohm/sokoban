#ifndef TYPES_H_9b47c15f853c5a1d
#define TYPES_H_9b47c15f853c5a1d
#include <stdint.h>
#include <string>

namespace Type {
using Flag = unsigned char;
const Flag Empty = 0x00;
const Flag Floor = 0x01;
const Flag Wall = 0x02;
const Flag Start = 0x04;
const Flag Goal = 0x08;
const Flag At = 0x10;
const Flag Box = 0x20;

inline const char toChar(const Flag &f) {
    if (f == Empty)
        return ' ';
    if (f & Wall)
        return 'X';
    if ((f & Box) && (f & Goal))
        return '*'; // Box on goal
    if ((f & At) && (f & Goal))
        return '+'; // Player on goal
    if (f & Box)
        return 'O';
    if (f & At)
        return '@';
    if (f & Start)
        return 's';
    if (f & Goal)
        return 'g';
    if (f & Floor)
        return '.';
    return '?';
}

inline std::string toString(const Flag &f) {
    std::string s("");
    if (f & Floor)
        s += "F";
    else
        s += "-";
    if (f & Wall)
        s += "W";
    else
        s += "-";
    if (f & Start)
        s += "S";
    else
        s += "-";
    if (f & Goal)
        s += "G";
    else
        s += "-";
    if (f & At)
        s += "@";
    else
        s += "-";
    if (f & Box)
        s += "O";
    else
        s += "-";
    return s;
}

} // namespace Type
#endif