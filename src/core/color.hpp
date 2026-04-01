#pragma once

namespace sb2d
{
    struct color;

    struct color
    {
        float r;
        float g;
        float b;
        float a;

        constexpr color(float r = 0, float g = 0, float b = 0, float a = 1);
        
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

        static constexpr color red();
        static constexpr color green();
        static constexpr color blue();
        static constexpr color black();
        static constexpr color white();
        static constexpr color clear();
    };
}
