#ifndef BOARD_H_9b47c15f853c5a1d
#define BOARD_H_9b47c15f853c5a1d
#include "types.hpp"
#include <cstddef>
#include <fstream>
#include <string>
#include <vector>

using namespace Type;

class Board {
public:
    static Board &instance();
    void resize(size_t x, size_t y);         // Accepts (width, height)
    std::vector<Flag> &operator[](size_t i); // Access by row index
    const std::vector<Flag> &operator[](size_t i) const; // Access by row index
    size_t width() const;  // Returns number of columns
    size_t height() const; // Returns number of rows
    bool saveToFile(const std::string &filename) const;
    bool loadFromFile(const std::string &filename);
    void print() const;

private:
    Board();
    std::vector<std::vector<Flag>> data_;
};

#endif
