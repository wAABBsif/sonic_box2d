#pragma once

namespace sb2d
{
    struct color
    {
        float r;
        float g;
        float b;
        float a;

        constexpr color(float r = 0, float g = 0, float b = 0, float a = 1)
            : r(r), g(g), b(b), a(a)
        {}
        
        float& operator[](int index);
        float* data();

        color operator+(const color& other) const;
        color operator-(const color& other) const;
        color operator*(const color& other) const;
        color operator/(const color& other) const;

        color& operator+=(const color& other);
        color& operator-=(const color& other);
        color& operator*=(const color& other);
        color& operator/=(const color& other);

        bool operator==(const color& other) const;
        bool operator!=(const color& other) const;

        static constexpr color black() { return color(0, 0, 0); }
        static constexpr color white() { return color(1, 1, 1); }
        static constexpr color clear() { return color(1, 1, 1, 0); }
        static constexpr color red() { return color(1, 0, 0); }
        static constexpr color green() { return color(0, 1, 0); }
        static constexpr color blue() { return color(0, 0, 1); }
    };
}
