#include "format.hpp"
#include <cstdlib>

using namespace sb2d::audio;

format::~format()
{
    delete buffer;
}

bool format::isValid()
{
    return buffer != nullptr;
}
