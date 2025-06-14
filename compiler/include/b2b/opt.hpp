#pragma once

#include <memory>

namespace b2b
{
    template<typename T>
    class Opt
    {
    public:
        Opt() = default;

        explicit Opt(T &&value)
        {
            m_Value = new T();
            *m_Value = std::move(value);
        }

        Opt(const Opt &other) = delete;
        Opt &operator=(const Opt &other) = delete;

        Opt(Opt &&other) noexcept
        {
            std::swap(m_Value, other.m_Value);
        }

        Opt &operator=(Opt &&other) noexcept
        {
            std::swap(m_Value, other.m_Value);
            return *this;
        }

        ~Opt()
        {
            if (!m_Value)
                return;

            free(m_Value);
        }

        T &operator*() const
        {
            return *m_Value;
        }

        T *operator->() const
        {
            return m_Value;
        }

        explicit operator bool() const
        {
            return m_Value;
        }

    private:
        T *m_Value = nullptr;
    };
}
