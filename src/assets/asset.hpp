#pragma once
#include <string>
#include <memory>

namespace sb2d
{
    class asset_base
    {
        asset_base() = delete;
    protected:
        static void add_to_map(const std::string &path, std::weak_ptr<asset_base> a);
        static std::shared_ptr<asset_base> get_if_exists(const std::string &path);
    };

    template <typename derived>
    class asset : asset_base
    {
        asset() = delete;
    protected:
        asset(const std::string &path) = 0;
    public:
        static std::shared_ptr<asset<derived>> get(const std::string &path)
        {
            std::shared_ptr<asset<derived>> result = asset_base::get_if_exists(path);
            if (result)
                return result;
            result = std::make_shared<asset<derived>>(path);
            add_to_map(path, result);
            return result;
        }
    };
}
