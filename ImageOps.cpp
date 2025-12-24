/*
 * Egor Danilov
 * st141853@student.spbu.ru
 * My laboratory work 1
 */


#include "ImageOps.hpp"
#include <algorithm>
#include <cmath>

static ColorRGB safePixel(const Image& img, int x, int y)
{
    x = std::clamp(x, 0, img.width() - 1);
    y = std::clamp(y, 0, img.height() - 1);
    return img.pixel(x, y);
}

RasterImage ImageOps::rotateCW(const Image& img)
{
    int w = img.width(), h = img.height();
    RasterImage out(h, w);
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            out.setPixel(h - 1 - y, x, img.pixel(x, y));
    return out;
}

RasterImage ImageOps::rotateCCW(const Image& img)
{
    int w = img.width(), h = img.height();
    RasterImage out(h, w);
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            out.setPixel(y, w - 1 - x, img.pixel(x, y));
    return out;
}

RasterImage ImageOps::gaussian(const Image& img)
{
    const float K[3][3] =
    {
        {1.f/16, 2.f/16, 1.f/16},
        {2.f/16, 4.f/16, 2.f/16},
        {1.f/16, 2.f/16, 1.f/16}
    };
    int w = img.width(), h = img.height();
    RasterImage out(w, h);
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            float R = 0, G = 0, B = 0;
            for (int dy = -1; dy <= 1; ++dy)
                for (int dx = -1; dx <= 1; ++dx)
                {
                    ColorRGB p = safePixel(img, x + dx, y + dy);
                    float w = K[dy + 1][dx + 1];
                    R += p.r * w;
                    G += p.g * w;
                    B += p.b * w;
                }
            auto clamp = [](float v)
            {
                return static_cast<uint8_t>(std::clamp(int(v + 0.5f), 0, 255));
            };
            out.setPixel(x, y, ColorRGB(clamp(R), clamp(G), clamp(B)));
        }
    }
    return out;
}
