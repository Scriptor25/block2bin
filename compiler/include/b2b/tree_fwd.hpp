#pragma once

#include <memory>

namespace b2b
{
    struct ParameterT;
    struct ParentNodeT;
    struct StatementNodeT;
    struct ExpressionNodeT;

    using ParentNodePtr = std::unique_ptr<ParentNodeT>;
    using StatementNodePtr = std::unique_ptr<StatementNodeT>;
    using ExpressionNodePtr = std::unique_ptr<ExpressionNodeT>;
}
