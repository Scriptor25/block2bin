#pragma once

#include <memory>
#include <vector>

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

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const std::vector<T> &reference)
    {
        os << '[';
        for (unsigned i = 0; i < reference.size(); ++i)
        {
            if (i)
                os << ", ";
            os << reference.at(i);
        }
        return os << ']';
    }
}
