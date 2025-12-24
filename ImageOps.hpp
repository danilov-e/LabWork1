/*
 * Egor Danilov
 * st141853@student.spbu.ru
 * My laboratory work 1
 */


#ifndef IMAGEOPS_HPP
#define IMAGEOPS_HPP

#include "RasterImage.hpp"

class ImageOps
{
public:
    static RasterImage rotateCW(const Image& img);
    static RasterImage rotateCCW(const Image& img);
    static RasterImage gaussian(const Image& img);
};

#endif
