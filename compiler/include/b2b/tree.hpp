#pragma once

#include <string>
#include <vector>
#include <b2b/tree_fwd.hpp>

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

    struct StatementNodeT
    {
        virtual ~StatementNodeT() = default;
    };

    struct ExpressionNodeT : StatementNodeT
    {
    };

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
        std::vector<ExpressionNodePtr> Inputs;
        std::vector<ExpressionNodePtr> Fields;
        std::vector<StatementNodePtr> Statements;
    };

    struct ForEachStatementNodeT final : StatementNodeT
    {
        ExpressionNodePtr Variable;
        ExpressionNodePtr Times;
        std::vector<StatementNodePtr> Statements;
    };

    struct WhileStatementNodeT final : StatementNodeT
    {
        ExpressionNodePtr Condition;
        std::vector<StatementNodePtr> Statements;
    };

    struct IfElseStatementNodeT final : StatementNodeT
    {
        bool HasElse;
        ExpressionNodePtr Condition;
        std::vector<StatementNodePtr> ThenStatements;
        std::vector<StatementNodePtr> ElseStatements;
    };

    struct InstantStatementNodeT final : StatementNodeT
    {
        std::vector<StatementNodePtr> Statements;
    };

    struct ConstantIntegerNodeT final : ExpressionNodeT
    {
        unsigned long long Value = 0llu;
    };

    struct ConstantFloatingPointNodeT final : ExpressionNodeT
    {
        long double Value = 0.0L;
    };

    struct ConstantStringNodeT final : ExpressionNodeT
    {
        std::string Value;
    };

    struct ConstantArrayNodeT final : ExpressionNodeT
    {
        std::vector<ExpressionNodePtr> Values;
    };

    struct ConstantBroadcastNodeT final : ExpressionNodeT
    {
        // TODO: target
        std::string Id;
    };

    struct ConstantVariableNodeT final : ExpressionNodeT
    {
        // TODO: target
        std::string Id;
    };

    struct ConstantListNodeT final : ExpressionNodeT
    {
        // TODO: target
        std::string Id;
    };

    struct GenericExpressionNodeT final : ExpressionNodeT
    {
        OpcodeE Opcode;
        std::vector<ExpressionNodePtr> Inputs;
        std::vector<ExpressionNodePtr> Fields;
    };

    struct NotExpressionNodeT final : ExpressionNodeT
    {
        ExpressionNodePtr Value;
    };
}
