#include "bmp_reader.hpp"
#include <fstream>
#include <stdexcept>
#include <cstdint>

std::size_t calculateSize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    uint16_t fileType;
    file.read(reinterpret_cast<char*>(&fileType), 2);

    if (fileType != 0x4D42) {
        throw std::runtime_error("Not a BMP file");
    }

    file.seekg(18);

    int32_t width, height;

    file.read(reinterpret_cast<char*>(&width), 4);
    file.read(reinterpret_cast<char*>(&height), 4);

    std::size_t rowSize = (static_cast<std::size_t>(width) * 3 + 3) / 4 * 4;
    std::size_t pixelDataSize = rowSize * static_cast<std::size_t>(height);

    return pixelDataSize;
}
