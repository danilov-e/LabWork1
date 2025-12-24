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
    RasterImage(int width, int height);

    int width() const override;
    int height() const override;
    ColorRGB pixel(int x, int y) const override;
    void setPixel(int x, int y, ColorRGB c) override;
};

#endif
