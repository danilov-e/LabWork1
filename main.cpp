/*
 * Egor Danilov
 * st141853@student.spbu.ru
 * My laboratory work 1
 */


#include "BMPHandler.hpp"
#include "ImageOps.hpp"
#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter path fo a file: ";
    std::string inputPath;
    std::getline(std::cin, inputPath);

    auto img = BMPHandler::load(inputPath);
    auto cw = ImageOps::rotateCW(img);
    auto ccw = ImageOps::rotateCCW(img);
    auto blurred = ImageOps::gaussian(cw);

    BMPHandler::save("rotated_cw.bmp", cw);
    BMPHandler::save("rotated_ccw.bmp", ccw);
    BMPHandler::save("blurred.bmp", blurred);

    std::cout << "  rotated_cw.bmp\n"
              << "  rotated_ccw.bmp\n"
              << "  blurred.bmp\n";


    return 0;
}
