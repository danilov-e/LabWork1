/*
 * Egor Danilov
 * st141853@student.spbu.ru
 * My laboratory work 1
 */


#ifndef RASTERIMAGE_HPP
#define RASTERIMAGE_HPP

#include "Image.hpp"
#include <vector>

class RasterImage : public Image
{
    int w, h;
    std::vector<ColorRGB> pixels;

public:
    RasterImage(int width, int height)
        : w(width), h(height), pixels(width * height) {}

    int width() const override
    {
        return w;
    }
    int height() const override
    {
        return h;
    }
    ColorRGB pixel(int x, int y) const override
    {
        return pixels[y * w + x];
    }
    void setPixel(int x, int y, ColorRGB c) override
    {
        pixels[y * w + x] = c;
    }
};
#endif
