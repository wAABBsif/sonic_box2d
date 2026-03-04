#pragma once
#include "assets/shader.hpp"
#include <cstddef>
#include <cstdint>

namespace sb2d::gfx
{
    class renderer_base
    {
        protected:
            renderer_base() {}
            virtual ~renderer_base() {}

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

            static void create_render_objects(uint32_t& vao, uint32_t& vbo, uint32_t& ibo);
            static void destroy_render_objects(uint32_t vao, uint32_t vbo, uint32_t ibo);
            static void bind_render_objects(uint32_t vao, uint32_t vbo, uint32_t ibo);
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
        static uint32_t s_vao;
        static uint32_t s_vbo;
        static uint32_t s_ibo;

        static uint32_t s_vertex_attrib_count;
        static size_t s_vertex_size;
        static size_t s_vertex_count;

    protected:
        static std::shared_ptr<assets::shader> s_shader;

        void create_render_objects()
        {
            create_render_objects(s_vao, s_vbo, s_ibo);
        }

        void destroy_render_objects()
        {
            destroy_render_objects(s_vao, s_vbo, s_ibo);
        }

        void bind_render_objects()
        {
            bind_render_objects(s_vao, s_vbo, s_ibo);
        }

        void set_vertex_total_size(size_t size)
        {
            s_vertex_size = size;
        }

        void add_vertex_attribute_float(field_type type, size_t offset, int count, bool normalized)
        {
            add_vertex_attribute_float(s_vertex_attrib_count, offset, s_vertex_size, type, count, normalized);
            s_vertex_attrib_count++;
        }

        void add_vertex_attribute_int(field_type type, size_t offset, int count)
        {
            add_vertex_attribute_int(s_vertex_attrib_count, offset, s_vertex_size, type, count);
            s_vertex_attrib_count++;
        }

        void create_vertex_data(size_t count, void* data, bool is_dynamic)
        {
            create_vertex_data(s_vertex_size * count, data, is_dynamic);
            s_vertex_attrib_count = count;
        }

        void write_vertex_data(size_t offset_count, size_t count, void* data)
        {
            write_vertex_data(s_vertex_size * offset_count, s_vertex_size * count, data);
        }

        void draw_elements()
        {
            draw_elements(s_vertex_count * 6);
        }
    };
}
