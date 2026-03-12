#pragma once
#include <cstdint>
#include <string>
#include <map>

namespace sb2d::game
{
    class entity
    {
    public:
        using entity_id = size_t;
        using tag_mask = uint32_t;

        enum tag : uint8_t
        {
            TAG_DELETION,
            TAG_COUNT
        };

    private:
        static inline std::map<entity_id, entity> s_entities;
        static inline entity_id s_next_id;

        entity(const std::string& name);
        static entity_id get_unique_id();

    public:
        static void init();
        static void terminate();
        static void update();
        
        static entity_id create(const std::string& name = "");

        static std::map<entity_id, entity>& get_all();

    public:
        std::string name;

        tag_mask tags;

    public:
        void set_tag(tag t, bool value);
        bool get_tag(tag t);
        tag_mask get_tag_mask();
    };
}
