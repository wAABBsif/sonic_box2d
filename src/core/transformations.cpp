#include "transformations.hpp"
#include "glm/fwd.hpp"

using namespace sb2d;
using namespace glm;

mat3 transformations::translate(mat3 mat, vec2 translation)
{
    mat3 t = mat3(1, 0, 0, 0, 1, 0, translation.x, translation.y, 1);
    return mat * t;
}

mat3 transformations::rotate(mat3 mat, float rotation)
{
    const float s = sinf(rotation);
    const float c = cosf(rotation);

    mat3 t = mat3(c, s, 0, -s, c, 0, 0, 0, 1);
    return mat * t;
}

mat3 transformations::scale(mat3 mat, vec2 scale)
{
    mat3 t = mat3(scale.x, 0, 0, 0, scale.y, 0, 0, 0, 1);
    return mat * t;
}
