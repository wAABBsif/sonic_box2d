#pragma once
#include "glm/glm.hpp"

namespace sb2d::transformations
{
    glm::mat3 translate(glm::mat3 mat, glm::vec2 translation);
    glm::mat3 rotate(glm::mat3 mat, float rotation);
    glm::mat3 scale(glm::mat3 mat, glm::vec2 scale);
}
