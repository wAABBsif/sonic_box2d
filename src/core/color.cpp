#include "color.hpp"

using namespace sb2d;

constexpr color::color(float r, float g, float b, float a)
    : r(r), g(g), b(b), a(a)
{}

float& color::operator[](int index)
{
    return this->data()[index];
}

float* color::data()
{
    return reinterpret_cast<float*>(this);
}

color color::operator+(const color& other) const
{
    return color(r + other.r, g + other.g, b + other.b, a + other.b);
}

color color::operator-(const color& other) const
{
    return color(r - other.r, g - other.g, b - other.b, a - other.b);
}

color color::operator*(const color& other) const
{
    return color(r * other.r, g * other.g, b * other.b, a * other.b);
}

color color::operator/(const color& other) const
{
    return color(r / other.r, g / other.g, b / other.b, a / other.b);
}

color& color::operator+=(const color& other)
{
    *this = *this + other;
    return *this;
}

color& color::operator-=(const color& other)
{
    *this = *this * other;
    return *this;
}

color& color::operator*=(const color& other)
{
    *this = *this * other;
    return *this;
}

color& color::operator/=(const color& other)
{
    *this = *this / other;
    return *this;
}

bool color::operator==(const color& other) const
{
    return r == other.r && g == other.g && b == other.b && a == other.a;
}

bool color::operator!=(const color& other) const
{
    return !(*this == other);
}

constexpr color color::red()
{
    return color(1, 0, 0);
}

constexpr color color::green()
{
    return color(0, 1, 0);
}

constexpr color color::blue()
{
    return color(0, 0, 1);
}

constexpr color color::black()
{
    return color(0, 0, 0);
}

constexpr color color::white()
{
    return color(1, 1, 1);
}

constexpr color color::clear()
{
    return color(1, 1, 1, 0);
}
