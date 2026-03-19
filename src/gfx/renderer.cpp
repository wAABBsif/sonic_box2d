#include "renderer.hpp"
#include "glad/glad.h"
#include <cstdint>

using namespace sb2d::gfx;

int renderer_base::gl_type_from_field_type(const field_type type)
{
    switch (type)
    {
        case field_type::INT_8:
            return GL_BYTE;
        case field_type::UINT_8:
            return GL_UNSIGNED_BYTE;
        case field_type::INT_16:
            return GL_SHORT;
        case field_type::UINT_16:
            return GL_UNSIGNED_SHORT;
        case field_type::INT_32:
            return GL_INT;
        case field_type::UINT_32:
            return GL_UNSIGNED_INT;
        case field_type::FLOAT_32:
            return GL_FLOAT;
        case field_type::FLOAT_64:
            return GL_DOUBLE;
    }

    return 0;
}

size_t renderer_base::size_from_field_type(const field_type type)
{
    switch (type)
    {
        case field_type::INT_8:
        case field_type::UINT_8:
            return 1;
        case field_type::INT_16:
        case field_type::UINT_16:
            return 2;
        case field_type::INT_32:
        case field_type::UINT_32:
        case field_type::FLOAT_32:
            return 4;
        case field_type::FLOAT_64:
            return 8;
    }

    return 0;
}

void renderer_base::generate_quad_indices(uint16_t* const buffer, const uint16_t quad_count)
{
    for (int i = 0; i < 6 * quad_count; i++)
    {
        const int index = i % 6;
        const int quad = i / 6;
        buffer[i] = (uint16_t[]){0, 1, 2, 2, 3, 0}[index] + 4 * quad;
    }
}

void renderer_base::create_render_objects(uint32_t& vao, uint32_t& vbo, uint32_t& ibo)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
}

void renderer_base::destroy_render_objects(uint32_t vao, uint32_t vbo, uint32_t ibo)
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}

void renderer_base::bind_render_objects(uint32_t vao, uint32_t vbo, uint32_t ibo)
{
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void renderer_base::unbind_render_objects()
{
    glBindVertexArray(0);
}

void renderer_base::add_vertex_attribute_float(uint32_t index, size_t offset, size_t total_size, field_type type, int count, bool normalized)
{
    glVertexAttribPointer(index, count, gl_type_from_field_type(type), normalized, total_size, (void*)offset);
    glEnableVertexAttribArray(index);
}

void renderer_base::add_vertex_attribute_int(uint32_t index, size_t offset, size_t total_size, field_type type, int count)
{
    glVertexAttribIPointer(index, count, gl_type_from_field_type(type), total_size, (void*)offset);
    glEnableVertexAttribArray(index);
}

void renderer_base::create_vertex_data(size_t size, void* data, bool is_dynamic)
{
    glBufferData(GL_ARRAY_BUFFER, size, data, is_dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void renderer_base::write_vertex_data(size_t offset, size_t size, void* data)
{
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void renderer_base::create_index_data(size_t size, void* data, bool is_dynamic)
{
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, is_dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

void renderer_base::draw_elements(size_t element_count)
{
    glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_SHORT, 0);
}
