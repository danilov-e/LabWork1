/*
 * Egor Danilov
 * st141853@student.spbu.ru
 * My laboratory work 1
 */



#include "BMPHandler.hpp"
#include <fstream>
#include <stdexcept>

#pragma pack(push, 1)
struct BMPFileHeader
{
    uint16_t type;
    uint32_t size;
    uint16_t reserved1 = 0;
    uint16_t reserved2 = 0;
    uint32_t offset;
};

struct BMPInfoHeader
{
    uint32_t size = 40;
    int32_t width;
    int32_t height;
    uint16_t planes = 1;
    uint16_t bpp = 24;
    uint32_t compression = 0;
    uint32_t imgSize = 0;
    int32_t xPPM = 0;
    int32_t yPPM = 0;
    uint32_t colorsUsed = 0;
    uint32_t colorsImportant = 0;
};
#pragma pack(pop)

static int rowPadding(int width)
{
    return (4 - (width * 3) % 4) % 4;
}

RasterImage BMPHandler::load(const std::filesystem::path& path)
{
    std::ifstream f(path, std::ios::binary);
    if (!f) throw std::runtime_error("Cannot open file: " + path.string());

    BMPFileHeader fileHdr;
    BMPInfoHeader infoHdr;
    f.read(reinterpret_cast<char*>(&fileHdr), 14);
    f.read(reinterpret_cast<char*>(&infoHdr), 40);

    if (fileHdr.type != 0x4D42 || infoHdr.bpp != 24 || infoHdr.compression != 0)
        throw std::runtime_error("Unsupported BMP format");

    f.seekg(fileHdr.offset);
    RasterImage img(infoHdr.width, infoHdr.height);
    int pad = rowPadding(infoHdr.width);

    for (int y = 0; y < infoHdr.height; ++y)
    {
        for (int x = 0; x < infoHdr.width; ++x)
        {
            uint8_t b, g, r;
            f.read(reinterpret_cast<char*>(&b), 1);
            f.read(reinterpret_cast<char*>(&g), 1);
            f.read(reinterpret_cast<char*>(&r), 1);
            img.setPixel(x, infoHdr.height - 1 - y, ColorRGB(r, g, b));
        }
        f.ignore(pad);
    }
    return img;
}

void BMPHandler::save(const std::filesystem::path& path, const Image& img)
{
    std::ofstream f(path, std::ios::binary);
    if (!f) throw std::runtime_error("Cannot write to: " + path.string());

    int w = img.width(), h = img.height();
    int pad = rowPadding(w);
    int rowSize = w * 3 + pad;
    int dataSize = rowSize * h;

    BMPFileHeader fileHdr{0x4D42, uint32_t(14 + 40 + dataSize), 0, 0, 54};
    BMPInfoHeader infoHdr{40, w, h};

    f.write(reinterpret_cast<const char*>(&fileHdr), 14);
    f.write(reinterpret_cast<const char*>(&infoHdr), 40);

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            ColorRGB c = img.pixel(x, h - 1 - y);
            f.put(static_cast<char>(c.b));
            f.put(static_cast<char>(c.g));
            f.put(static_cast<char>(c.r));
        }
        for (int i = 0; i < pad; ++i) f.put('\0');
    }
}
