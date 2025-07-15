#pragma once

#include <memory>

namespace b2b
{
    template<typename T>
    class Option
    {
    public:
        Option() = default;

        explicit Option(T &&value)
        {
            m_Value = new T();
            *m_Value = std::move(value);
        }

        Option(const Option &other) = delete;
        Option &operator=(const Option &other) = delete;

        Option(Option &&other) noexcept
        {
            std::swap(m_Value, other.m_Value);
        }

        Option &operator=(Option &&other) noexcept
        {
            std::swap(m_Value, other.m_Value);
            return *this;
        }

        ~Option()
        {
            if (!m_Value)
                return;

            free(m_Value);
        }

        T &operator*() const
        {
            if (m_Value)
                return *m_Value;
            throw std::runtime_error("panic");
        }

        T *operator->() const
        {
            if (m_Value)
                return m_Value;
            throw std::runtime_error("panic");
        }

        explicit operator bool() const
        {
            return m_Value;
        }

    private:
        T *m_Value = nullptr;
    };
}
