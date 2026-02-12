#include "game.hpp"
#include "core/log.hpp"

static void init();
static void update();
static void terminate();
static bool is_running();

void sb2d::game::run()
{
    init();
    LOG_MESSAGE("Game initialized");
    while (is_running())
    {
        update();
    }

    terminate();
    LOG_MESSAGE("Game terminated");
}

static void init()
{

}

static void update()
{

}

static void terminate()
{

}

static bool is_running()
{
    return false;
}
