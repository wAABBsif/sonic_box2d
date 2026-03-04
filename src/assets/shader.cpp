#include "shader.hpp"
#include <GLES2/gl2.h>
#include "core/log.hpp"
#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>

using namespace sb2d::assets;

struct shader_program_source
{
    std::string vert;
    std::string frag;
};

static shader_program_source s_parse_shader(const std::string &path)
{
    std::ifstream file_stream = std::ifstream(path);
    std::string line;
    std::stringstream vert_stream;
    std::stringstream frag_stream;
    std::stringstream *current_stream;

    while (std::getline(file_stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vert") != std::string::npos)
                current_stream = &vert_stream;
            else if (line.find("frag") != std::string::npos)
                current_stream = &frag_stream;
    
            continue;
        }

        *current_stream << line << '\n';
    }

    return shader_program_source(vert_stream.str(), frag_stream.str());
}

static uint32_t s_compile_shader(const char *source, const uint32_t type)
{
    const uint32_t id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    int32_t result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        int len;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

        char *message = (char *)malloc(len);
        glGetShaderInfoLog(id, len, &len, message);
        message[len - 1] = 0;
        LOG_WARNING("Shader error: ", message);

        glDeleteShader(id);
        return -1;
    }

    return id;
}

shader::shader(const std::string &path)
{
    this->program_id = 0;

    shader_program_source source = s_parse_shader(path);
    if (source.vert.empty() || source.frag.empty())
    {
        LOG_WARNING("Shader file '", path, "' could not be loaded");
        return;
    }

    uint32_t vert = s_compile_shader(source.vert.c_str(), GL_VERTEX_SHADER);
    uint32_t frag = s_compile_shader(source.frag.c_str(), GL_FRAGMENT_SHADER);

    if (vert == -1)
    {
        LOG_WARNING("Vertex shader '", path, "' failed to compile");
        return;
    }

    if (frag == -1)
    {
        LOG_WARNING("Fragment shader '", path, "' failed to compile");
        return;
    }

    this->program_id = glCreateProgram();
    glAttachShader(this->program_id, vert);
    glAttachShader(this->program_id, frag);
    glLinkProgram(this->program_id);
    glValidateProgram(this->program_id);

    glDeleteShader(vert);
    glDeleteShader(frag);

    LOG_MESSAGE("Shader '", path, "' loaded");
}

shader::~shader()
{
    glDeleteProgram(this->program_id);
}

void shader::set_current(const shader& s)
{
    glUseProgram(s.program_id);
}
