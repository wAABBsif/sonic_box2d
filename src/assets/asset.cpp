#include "asset.hpp"
#include <memory>
#include <vector>
#include <map>

using namespace sb2d;

static std::map<std::string, std::weak_ptr<asset_base>> s_loaded_assets;

void asset_base::add_to_map(const std::string &path, std::weak_ptr<asset_base> a)
{
    s_loaded_assets.insert({path, a});
}

std::shared_ptr<asset_base> asset_base::get_if_exists(const std::string &path)
{
    auto it = s_loaded_assets.find(path);
    if (it == s_loaded_assets.end())
        return nullptr;

    if (it->second.expired())
    {
        s_loaded_assets.erase(it);
        return nullptr;
    }

    return it->second.lock();
}
