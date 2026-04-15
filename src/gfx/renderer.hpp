#pragma once
#include "shader.hpp"
#include <cstddef>
#include <cstdint>
#include <memory>

namespace sb2d::gfx
{
    class renderer_base
    {
        protected:
            renderer_base() = default;
            virtual ~renderer_base() = default;

            enum class field_type : uint8_t
            {
                INT_8,
                UINT_8,
                INT_16,
                UINT_16,
                INT_32,
                UINT_32,
                FLOAT_32,
                FLOAT_64
            };

            static int gl_type_from_field_type(const field_type type);
            static size_t size_from_field_type(const field_type type);

            static void generate_quad_indices(uint16_t* const buffer, const uint16_t quad_count);

            static void create_render_objects(gl_object& vao, gl_object& vbo, gl_object& ibo);
            static void destroy_render_objects(gl_object vao, gl_object vbo, gl_object ibo);
            static void bind_render_objects(gl_object vao, gl_object vbo, gl_object ibo);
            static void unbind_render_objects();

            static void add_vertex_attribute_float(uint32_t index, size_t offset, size_t total_size, field_type type, int count, bool normalized);
            static void add_vertex_attribute_int(uint32_t index, size_t offset, size_t total_size, field_type type, int count);
    
            static void create_vertex_data(size_t size, void* data, bool is_dynamic);
            static void write_vertex_data(size_t offset, size_t size, void* data);

            static void create_index_data(size_t size, void* data, bool is_dynamic);

            static void draw_elements(size_t element_count);
    };

    template <typename derived>
    class renderer : public renderer_base
    {
    private:
        static inline gl_object s_vao;
        static inline gl_object s_vbo;
        static inline gl_object s_ibo;

        static inline uint32_t s_vertex_attrib_count;
        static inline size_t s_vertex_size;

        static inline std::string s_shader;

    protected:
        static void create_render_objects()
        {
            renderer_base::create_render_objects(s_vao, s_vbo, s_ibo);
        }

        static void destroy_render_objects()
        {
            renderer_base::destroy_render_objects(s_vao, s_vbo, s_ibo);
        }

        static void bind_render_objects()
        {
            renderer_base::bind_render_objects(s_vao, s_vbo, s_ibo);
        }

        static void set_vertex_total_size(size_t size)
        {
            s_vertex_size = size;
        }

        static void add_vertex_attribute_float(field_type type, size_t offset, int count, bool normalized)
        {
            renderer_base::add_vertex_attribute_float(s_vertex_attrib_count, offset, s_vertex_size, type, count, normalized);
            s_vertex_attrib_count++;
        }

        static void add_vertex_attribute_int(field_type type, size_t offset, int count)
        {
            renderer_base::add_vertex_attribute_int(s_vertex_attrib_count, offset, s_vertex_size, type, count);
            s_vertex_attrib_count++;
        }

        static void create_vertex_data(size_t count, void* data, bool is_dynamic)
        {
            renderer_base::create_vertex_data(s_vertex_size * count, data, is_dynamic);
            s_vertex_attrib_count = count;
        }

        static void create_index_data(size_t count, void* data, bool is_dynamic)
        {
            renderer_base::create_index_data(count * sizeof(uint16_t), data, is_dynamic);
        }

        static void write_vertex_data(size_t offset_count, size_t count, void* data)
        {
            renderer_base::write_vertex_data(s_vertex_size * offset_count, s_vertex_size * count, data);
        }

        static void set_shader(const std::string& path = "")
        {
            if (shader::get(path))
                shader::unload(path);
            if (path.empty())
                return;
            s_shader = path;
            shader::load(path);
        }

        static shader& get_shader()
        {
            return *shader::get(s_shader);
        }
    };
}
