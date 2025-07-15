#pragma once

#include <string>
#include <vector>

namespace b2b
{
    struct ParameterT
    {
        std::string Name;
        bool IsBoolean;
    };

    struct FunctionNodeT
    {
        std::string Name;
        std::vector<ParameterT> Parameters;
    };
}
