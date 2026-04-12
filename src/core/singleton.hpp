#pragma once

namespace sb2d
{
    template <typename derived>
    class singleton
    {
    protected:
        inline static derived* instance = nullptr;

        singleton() = default;
        ~singleton() = default;

    public:
        singleton(const singleton&) = delete;
        singleton& operator=(const singleton&) = delete;

        static derived& get()
        {
            if (instance == nullptr)
                instance = new derived();

            return *instance;
        }
    
        static void destroy()
        {
            delete instance;
            instance = nullptr;
        }
    };
}
