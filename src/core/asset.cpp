#include "asset.hpp"
#include <memory>
#include <vector>
#include <map>

using namespace sb2d;

static std::string s_asset_directory;

void asset_base::set_asset_directory(const std::string &path)
{
    s_asset_directory = path + '/';
}

const std::string& asset_base::get_asset_directory()
{
    return s_asset_directory;
}
