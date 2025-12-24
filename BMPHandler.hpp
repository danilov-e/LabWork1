/*
 * Egor Danilov
 * st141853@student.spbu.ru
 * My laboratory work 1
 */


#ifndef BMPHANDLER_HPP
#define BMPHANDLER_HPP

#include "RasterImage.hpp"
#include <string>
#include <filesystem>

class BMPHandler
{
public:
    static RasterImage load(const std::filesystem::path& path);
    static void save(const std::filesystem::path& path, const Image& img);
};

#endif
