#include "assets/asset.hpp"
#include "game/game.hpp"

int main(int argc, char *argv[])
{
    if (argc > 1)
        sb2d::asset_base::set_asset_directory(argv[1]);
    else
        sb2d::asset_base::set_asset_directory("res");

    sb2d::game::run();
}
