#pragma once
#include <string>
#include <memory>

namespace sb2d
{
    class asset_base
    {
    protected:
        asset_base() {}
        virtual ~asset_base() {}
        static void add_to_map(const std::string &path, std::weak_ptr<asset_base> a);
        static std::shared_ptr<asset_base> get_if_exists(const std::string &path);
    };

    template <typename derived>
    class asset : public asset_base
    {
    protected:
        asset() {}
        virtual ~asset() {}
    public:
        static std::shared_ptr<derived> get(const std::string &path)
        {
            std::shared_ptr<derived> result = std::dynamic_pointer_cast<derived>(asset_base::get_if_exists(path));
            if (result)
                return result;
            result = std::make_shared<derived>(path);
            add_to_map(path, std::static_pointer_cast<asset_base>(result));
            return result;
        }
    };
}
