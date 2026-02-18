#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace sb2d::game
{
    class game_object
    {
    public:
        enum obj_tag : uint8_t
        {
            NONE = 0,
            QUEUE_DELETION = 1 << 0
        };

        static void init();
        static void terminate();
        static void update();

        game_object(std::string name = "", obj_tag tags = NONE);
        static game_object& create(std::string name = "", obj_tag tags = NONE);
        static std::vector<std::unique_ptr<game_object>>& get();
         
    public:
        std::string name;
    private:
        obj_tag tags;
        
    public:
        void set_tag(obj_tag t, bool value);
        bool get_tag(obj_tag t);

        void queue_deletion();
    };
}
