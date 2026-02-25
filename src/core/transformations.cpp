#include "transformations.hpp"
#include "glm/fwd.hpp"

glm::mat3 sb2d::transformations::translate(glm::mat3 mat, glm::vec2 translation)
{
    glm::mat3 t = glm::mat3(1, 0, 0, 0, 1, 0, translation.x, translation.y, 1);
    return mat * t;
}

glm::mat3 sb2d::transformations::rotate(glm::mat3 mat, float rotation)
{
    const float s = sinf(rotation);
    const float c = cosf(rotation);

    glm::mat3 t = glm::mat3(c, s, 0, -s, c, 0, 0, 0, 1);
    return mat * t;
}

glm::mat3 sb2d::transformations::scale(glm::mat3 mat, glm::vec2 scale)
{
    glm::mat3 t = glm::mat3(scale.x, 0, 0, 0, scale.y, 0, 0, 0, 1);
    return mat * t;
}
