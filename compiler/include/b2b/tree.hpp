#pragma once

#include <memory>
#include <string>
#include <vector>

namespace b2b
{
    struct ParameterT
    {
        std::string Name;
        std::string Default;
    };

    struct ParentNodeT
    {
        virtual ~ParentNodeT() = default;
    };

    using ParentNodePtr = std::unique_ptr<ParentNodeT>;

    struct StatementNodeT
    {
        virtual ~StatementNodeT() = default;
    };

    using StatementNodePtr = std::unique_ptr<StatementNodeT>;

    struct ExpressionNodeT
    {
        virtual ~ExpressionNodeT() = default;
    };

    using ExpressionNodePtr = std::unique_ptr<ExpressionNodeT>;

    struct ProcedureNodeT final : ParentNodeT
    {
        std::string Name;
        std::vector<ParameterT> Parameters;
        std::vector<StatementNodePtr> Statements;
    };

    struct ConstructorNodeT final : ParentNodeT
    {
        std::vector<StatementNodePtr> Statements;
    };

    struct ListenerNodeT final : ParentNodeT
    {
        std::string Event;
        std::vector<StatementNodePtr> Statements;
    };
}
