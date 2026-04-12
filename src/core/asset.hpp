#pragma once
#include "core/log.hpp"
#include <map>
#include <string>

namespace sb2d
{
    class asset_base
    {
        asset_base(asset_base& a) = delete;
    protected:
        asset_base() = default;
        virtual ~asset_base() = default;
    public:
        static void set_asset_directory(const std::string& path);
        static const std::string& get_asset_directory();
    };

    template <typename derived>
    class asset : public asset_base
    {
    private:
        static inline std::map<std::string, derived> s_loaded_assets;
    protected:
        asset() = default;
        virtual ~asset() = default;

    public:
        static std::map<std::string, derived>& get_all()
        {
            return s_loaded_assets;
        }

        static derived* load(const std::string& path)
        {
            auto it = s_loaded_assets.emplace(path, get_asset_directory() + path);
            if (!it.second)
                LOG_WARNING("Asset '", path, "' has already been loaded");

             return &it.first->second;
        }

        static bool unload(const std::string& path)
        {
            auto it = s_loaded_assets.find(path);
            if (it == s_loaded_assets.end())
                return false;

            s_loaded_assets.erase(it);
            return true;
        }

        static derived* get(const std::string& path)
        {
            auto it = s_loaded_assets.find(path);
            if (it == s_loaded_assets.end())
                return nullptr;

            return &it->second;
        }
    };
}
