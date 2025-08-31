#include "board.hpp"
#include <fstream>
#include <iostream>
#include <string>

using namespace Type;

Board &Board::instance() {
    static Board inst;
    return inst;
}

Board::Board() = default;

void Board::resize(size_t x, size_t y) {
    data_.assign(y, std::vector<Flag>(x, Empty));
}

std::vector<Flag> &Board::operator[](size_t i) { return data_[i]; }

const std::vector<Flag> &Board::operator[](size_t i) const { return data_[i]; }

size_t Board::width() const { return data_.empty() ? 0 : data_[0].size(); }

size_t Board::height() const { return data_.size(); }

bool Board::saveToFile(const std::string &filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs)
        return false;
    uint32_t w = static_cast<uint32_t>(width());
    uint32_t h = static_cast<uint32_t>(height());
    ofs.write(reinterpret_cast<const char *>(&w), sizeof(w));
    ofs.write(reinterpret_cast<const char *>(&h), sizeof(h));
    for (size_t j = 0; j < h; ++j) {
        for (size_t i = 0; i < w; ++i) {
            uint32_t val = static_cast<uint32_t>(data_[j][i]);
            ofs.write(reinterpret_cast<const char *>(&val), sizeof(val));
        }
    }
    return ofs.good();
}

bool Board::loadFromFile(const std::string &filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs)
        return false;
    uint32_t w = 0, h = 0;
    ifs.read(reinterpret_cast<char *>(&w), sizeof(w));
    ifs.read(reinterpret_cast<char *>(&h), sizeof(h));
    if (!ifs)
        return false;
    resize(w, h);
    for (size_t j = 0; j < h; ++j) {
        for (size_t i = 0; i < w; ++i) {
            uint32_t val = 0;
            ifs.read(reinterpret_cast<char *>(&val), sizeof(val));
            data_[j][i] = static_cast<Flag>(val);
        }
    }
    return ifs.good();
}

#include <iostream>

void Board::print() const {
    for (size_t j = 0; j < height(); ++j) {
        for (size_t i = 0; i < width(); ++i) {
            std::cout << Type::toChar(data_[j][i]);
        }
        std::cout << std::endl;
    }
}