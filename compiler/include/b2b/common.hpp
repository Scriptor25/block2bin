#pragma once

#include <memory>

namespace b2b
{
    template<typename D, typename S>
    D *cast(const std::unique_ptr<S> &ptr)
    {
        return dynamic_cast<D *>(ptr.get());
    }

    template<typename D, typename S>
    std::unique_ptr<D> cast(std::unique_ptr<S> &&ptr)
    {
        auto s = ptr.release();
        if (auto d = dynamic_cast<D *>(s))
        {
            return std::unique_ptr<D *>(d);
        }
        delete s;
        return std::unique_ptr<D>();
    }
}
