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

static const uint16_t bmp_signature = 0x4D42;
static const int file_header_size = 14;
static const int info_header_size = 40;
static const int total_header_size = 54;
static const int bytes_per_pixel = 3;
static const int bits_per_pixel = 24;
static const int row_alignment = 4;

#pragma pack(pop)

static int rowPadding(int width)
{
    return (row_alignment - (width * bytes_per_pixel) % row_alignment) % row_alignment;
}

RasterImage BMPHandler::load(const std::filesystem::path& path)
{
    std::ifstream f(path, std::ios::binary);
    if (!f) throw std::runtime_error("Cannot open file: " + path.string());

    BMPFileHeader fileHdr;
    BMPInfoHeader infoHdr;
    f.read(reinterpret_cast<char*>(&fileHdr), file_header_size);
    f.read(reinterpret_cast<char*>(&infoHdr), info_header_size);

    if (fileHdr.type != bmp_signature || infoHdr.bpp != bits_per_pixel || infoHdr.compression != 0)
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
    int rowSize = w * bytes_per_pixel + pad;
    int dataSize = rowSize * h;

    BMPFileHeader fileHdr{bmp_signature, uint32_t(file_header_size + info_header_size + dataSize), 0, 0, total_header_size};
    BMPInfoHeader infoHdr{info_header_size, w, h};

    f.write(reinterpret_cast<const char*>(&fileHdr), file_header_size);
    f.write(reinterpret_cast<const char*>(&infoHdr), info_header_size);

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
