#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstddef>
#include <string>

class Image {
public:
    virtual ~Image() = default;

    virtual std::size_t getWidth() const = 0;
    virtual std::size_t getHeight() const = 0;

    virtual void rotateCW() = 0;
    virtual void rotateCCW() = 0;
    virtual void applyGaussianFilter() = 0;

    virtual void save(const std::string& filename) const = 0;
};

#endif 
