#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>

struct ColorRGB {
    uint8_t r = 0, g = 0, b = 0;
    ColorRGB() = default;
    ColorRGB(uint8_t r_, uint8_t g_, uint8_t b_) : r(r_), g(g_), b(b_) {}
};

class Image {
public:
    virtual ~Image() = default;
    virtual int width() const = 0;
    virtual int height() const = 0;
    virtual ColorRGB pixel(int x, int y) const = 0;
    virtual void setPixel(int x, int y, ColorRGB c) = 0;
};
