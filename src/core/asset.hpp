#pragma once
#include "core/log.hpp"
#include <map>
#include <string>
#include <memory>

namespace sb2d
{
    class asset_base
    {
    protected:
        asset_base() {}
        virtual ~asset_base() {}
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
        asset() {}
        virtual ~asset() {}
        virtual void unload_self() = 0;

    public:
        static std::map<std::string, derived>& get_all()
        {
            return s_loaded_assets;
        }

        static derived* load(const std::string& path)
        {
            auto it = s_loaded_assets.insert({path, derived(get_asset_directory() + path)});
            if (!it.second)
                LOG_WARNING("Asset '", path, "' has already been loaded");

             return &it.first->second;
        }

        static bool unload(const std::string& path)
        {
            auto it = s_loaded_assets.find(path);
            if (it == s_loaded_assets.end())
                return false;

            reinterpret_cast<asset<derived>*>(&it->second)->unload_self();
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
