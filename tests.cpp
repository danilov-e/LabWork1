/*
 * Egor Danilov
 * st141853@student.spbu.ru
 * My laboratory work 1
 */


#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

#include "RasterImage.hpp"
#include "ImageOps.hpp"
#include "BMPHandler.hpp"

RasterImage makeImage(int w, int h, uint8_t r, uint8_t g, uint8_t b)
{
    RasterImage img(w, h);
    ColorRGB c(r, g, b);
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
            img.setPixel(x, y, c);
    return img;
}


TEST(RasterImageSimpleTest, SizeIsCorrect)
{
    RasterImage img(5, 3);
    EXPECT_EQ(img.width(), 5);
    EXPECT_EQ(img.height(), 3);
}

TEST(RasterImageSimpleTest, PixelIsBlackByDefault)
{
    RasterImage img(1, 1);
    ColorRGB p = img.pixel(0, 0);
    EXPECT_EQ(p.r, 0);
    EXPECT_EQ(p.g, 0);
    EXPECT_EQ(p.b, 0);
}

TEST(RasterImageSimpleTest, CanSetAndReadPixel)
{
    RasterImage img(2, 2);
    img.setPixel(1, 0, ColorRGB(10, 20, 30));
    ColorRGB p = img.pixel(1, 0);
    EXPECT_EQ(p.r, 10);
    EXPECT_EQ(p.g, 20);
    EXPECT_EQ(p.b, 30);
}

TEST(RasterImageSimpleTest, DifferentPixelsAreIndependent)
{
    RasterImage img(2, 1);
    img.setPixel(0, 0, ColorRGB(255, 0, 0));
    img.setPixel(1, 0, ColorRGB(0, 255, 0));
    EXPECT_EQ(img.pixel(0, 0).r, 255);
    EXPECT_EQ(img.pixel(1, 0).g, 255);
    EXPECT_EQ(img.pixel(0, 0).g, 0);
    EXPECT_EQ(img.pixel(1, 0).r, 0);
}

TEST(RotateCWSimpleTest, SizeSwaps)
{
    RasterImage img(4, 2);
    auto out = ImageOps::rotateCW(img);
    EXPECT_EQ(out.width(), 2);
    EXPECT_EQ(out.height(), 4);
}

TEST(RotateCWSimpleTest, SinglePixelStaysSameColor)
{
    RasterImage img(1, 1);
    img.setPixel(0, 0, ColorRGB(50, 60, 70));
    auto out = ImageOps::rotateCW(img);
    EXPECT_EQ(out.pixel(0, 0).r, 50);
    EXPECT_EQ(out.pixel(0, 0).g, 60);
    EXPECT_EQ(out.pixel(0, 0).b, 70);
}

TEST(RotateCWSimpleTest, TopLeftGoesToTopRightAfterCW)
{
    RasterImage img(2, 2);
    img.setPixel(0, 0, ColorRGB(255, 0, 0));
    auto out = ImageOps::rotateCW(img);
    EXPECT_EQ(out.pixel(1, 0).r, 255);
    EXPECT_EQ(out.pixel(1, 0).g, 0);
    EXPECT_EQ(out.pixel(1, 0).b, 0);
}

TEST(RotateCWSimpleTest, BottomLeftGoesToTopLeftAfterCW)
{
    RasterImage img(2, 2);
    img.setPixel(0, 1, ColorRGB(0, 0, 255));
    auto out = ImageOps::rotateCW(img);
    EXPECT_EQ(out.pixel(0, 0).b, 255);
    EXPECT_EQ(out.pixel(0, 0).r, 0);
    EXPECT_EQ(out.pixel(0, 0).g, 0);
}

TEST(RotateCCWSimpleTest, SizeSwaps)
{
    RasterImage img(3, 5);
    auto out = ImageOps::rotateCCW(img);
    EXPECT_EQ(out.width(), 5);
    EXPECT_EQ(out.height(), 3);
}

TEST(RotateCCWSimpleTest, SinglePixelStaysSameColor)
{
    RasterImage img(1, 1);
    img.setPixel(0, 0, ColorRGB(80, 90, 100));
    auto out = ImageOps::rotateCCW(img);
    EXPECT_EQ(out.pixel(0, 0).r, 80);
    EXPECT_EQ(out.pixel(0, 0).g, 90);
    EXPECT_EQ(out.pixel(0, 0).b, 100);
}

TEST(RotateCCWSimpleTest, TopLeftGoesToBottomLeftAfterCCW)
{
    RasterImage img(2, 2);
    img.setPixel(0, 0, ColorRGB(255, 0, 0));
    auto out = ImageOps::rotateCCW(img);
    EXPECT_EQ(out.pixel(0, 1).r, 255);
    EXPECT_EQ(out.pixel(0, 1).g, 0);
    EXPECT_EQ(out.pixel(0, 1).b, 0);
}

TEST(RotateCCWSimpleTest, TopRightGoesToTopLeftAfterCCW)
{
    RasterImage img(2, 2);
    img.setPixel(1, 0, ColorRGB(0, 255, 0));
    auto out = ImageOps::rotateCCW(img);

    EXPECT_EQ(out.pixel(0, 0).g, 255);
    EXPECT_EQ(out.pixel(0, 0).r, 0);
    EXPECT_EQ(out.pixel(0, 0).b, 0);
}


TEST(GaussianSimpleTest, SolidRedImageStaysRed)
{
    auto img = makeImage(3, 3, 200, 0, 0);
    auto out = ImageOps::gaussian(img);
    for (int y = 0; y < 3; ++y)
        for (int x = 0; x < 3; ++x)
            EXPECT_EQ(out.pixel(x, y).r, 200);
}

TEST(GaussianSimpleTest, SolidGreenImageStaysGreen)
{
    auto img = makeImage(4, 4, 0, 180, 0);
    auto out = ImageOps::gaussian(img);
    for (int y = 0; y < 4; ++y)
        for (int x = 0; x < 4; ++x)
            EXPECT_EQ(out.pixel(x, y).g, 180);
}

TEST(GaussianSimpleTest, SolidBlueImageStaysBlue)
{
    auto img = makeImage(2, 5, 0, 0, 220);
    auto out = ImageOps::gaussian(img);
    for (int y = 0; y < 5; ++y)
        for (int x = 0; x < 2; ++x)
            EXPECT_EQ(out.pixel(x, y).b, 220);
}

TEST(GaussianSimpleTest, WhiteImageStaysWhite)
{
    auto img = makeImage(3, 3, 255, 255, 255);
    auto out = ImageOps::gaussian(img);
    for (int y = 0; y < 3; ++y)
        for (int x = 0; x < 3; ++x)
        {
            EXPECT_EQ(out.pixel(x, y).r, 255);
            EXPECT_EQ(out.pixel(x, y).g, 255);
            EXPECT_EQ(out.pixel(x, y).b, 255);
        }
}

TEST(BMPHandlerSimpleTest, SaveAndLoadPreservesSolidColor)
{
    namespace fs = std::filesystem;
    fs::path path = "temp_solid_test.bmp";
    auto original = makeImage(2, 2, 100, 150, 200);
    BMPHandler::save(path, original);

    auto loaded = BMPHandler::load(path);

    EXPECT_EQ(loaded.width(), 2);
    EXPECT_EQ(loaded.height(), 2);
    for (int y = 0; y < 2; ++y)
        for (int x = 0; x < 2; ++x)
        {
            ColorRGB p = loaded.pixel(x, y);
            EXPECT_EQ(p.r, 100);
            EXPECT_EQ(p.g, 150);
            EXPECT_EQ(p.b, 200);
        }

    fs::remove(path);
}

TEST(BMPHandlerSimpleTest, SaveAndLoadPreservesSinglePixel)
{
    namespace fs = std::filesystem;
    fs::path path = "temp_pixel_test.bmp";

    RasterImage img(1, 1);
    img.setPixel(0, 0, ColorRGB(30, 40, 50));
    BMPHandler::save(path, img);

    auto loaded = BMPHandler::load(path);
    EXPECT_EQ(loaded.width(), 1);
    EXPECT_EQ(loaded.height(), 1);
    EXPECT_EQ(loaded.pixel(0, 0).r, 30);
    EXPECT_EQ(loaded.pixel(0, 0).g, 40);
    EXPECT_EQ(loaded.pixel(0, 0).b, 50);

    fs::remove(path);
}
