#pragma once
#include "component.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace sb2d::game
{
    class entity
    {
    public:
        enum tag : uint8_t
        {
            NONE = 0,
            QUEUE_DELETION = 1 << 0
        };

        static void init();
        static void terminate();
        static void update();

        entity(std::string name = "", tag tags = NONE);
        static std::weak_ptr<entity> create(std::string name = "", tag tags = NONE);

        static size_t get_count();
        static std::vector<std::shared_ptr<entity>>& get_all();
         
    public:
        std::string name;
    private:
        tag tags;
        
    public:
        std::vector<std::shared_ptr<component>> components;

        void set_tag(tag t, bool value);
        bool get_tag(tag t);

        void queue_deletion();
    };
}
