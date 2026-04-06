#include "color.hpp"

using namespace sb2d;

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
