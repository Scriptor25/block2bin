#pragma once

#include <memory>
#include <nlohmann/json.hpp>

namespace b2b
{
    template<typename T>
    class Option
    {
    public:
        Option() = default;

        explicit Option(T &&value)
        {
            m_P = static_cast<T *>(malloc(sizeof(T)));
            new(m_P) T(std::move(value));
        }

        Option(const Option &other)
        {
            m_P = static_cast<T *>(malloc(sizeof(T)));
            new(m_P) T(*other.m_P);
        }

        Option &operator=(const Option &other)
        {
            if (this != &other)
            {
                if (m_P && other.m_P)
                {
                    *m_P = *other.m_P;
                }
                else if (m_P)
                {
                    free(m_P);
                    m_P = nullptr;
                }
                else
                {
                    m_P = static_cast<T *>(malloc(sizeof(T)));
                    new(m_P) T(*other.m_P);
                }
            }
            return *this;
        }

        Option(Option &&other) noexcept
        {
            std::swap(m_P, other.m_P);
        }

        Option &operator=(Option &&other) noexcept
        {
            std::swap(m_P, other.m_P);
            return *this;
        }

        ~Option()
        {
            if (!m_P)
            {
                return;
            }

            free(m_P);
            m_P = nullptr;
        }

        T &operator*() const
        {
            if (m_P)
            {
                return *m_P;
            }
            throw std::runtime_error("panic");
        }

        T *operator->() const
        {
            if (m_P)
            {
                return m_P;
            }
            throw std::runtime_error("panic");
        }

        explicit operator bool() const
        {
            return m_P != nullptr;
        }

    private:
        T *m_P = nullptr;
    };

    template<typename T>
    Option<T> option_from(const nlohmann::json &json, const std::string_view &key)
    {
        if (json.contains(key))
        {
            return json[key];
        }
        return {};
    }

    template<typename T>
    Option<T> option_from(const nlohmann::json &json, const unsigned index)
    {
        if (index < json.size())
        {
            return json[index];
        }
        return {};
    }
}
