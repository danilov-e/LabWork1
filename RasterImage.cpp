#include "RasterImage.hpp"

RasterImage::RasterImage(int width, int height)
    : w(width), h(height), pixels(width * height)
{}

int RasterImage::width() const
{
    return w;
}

int RasterImage::height() const
{
    return h;
}

ColorRGB RasterImage::pixel(int x, int y) const
{
    return pixels[y * w + x];
}

void RasterImage::setPixel(int x, int y, ColorRGB c)
{
    pixels[y * w + x] = c;
}
