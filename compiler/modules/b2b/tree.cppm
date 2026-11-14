module;

#include <memory>
#include <string>
#include <vector>

export module b2b.tree;

import b2b.opcode;

export namespace b2b
{
    struct ParameterT;

    struct TargetTypeFieldT;
    struct TargetTypeT;

    struct ParentNodeT;
    struct StatementNodeT;
    struct ExpressionNodeT;

    using ParentNodePtr = std::unique_ptr<ParentNodeT>;
    using StatementNodePtr = std::unique_ptr<StatementNodeT>;
    using ExpressionNodePtr = std::unique_ptr<ExpressionNodeT>;

    struct TargetTypeFieldT final
    {
        std::string Id;
        std::string Name;
        ExpressionNodePtr InitialValue;
    };

    struct TargetTypeT final
    {
        std::string Name;
        std::vector<TargetTypeFieldT> Fields;
    };

    struct ParameterT final
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
        unsigned TargetId;
        std::string Id;
    };

    struct ConstantVariableNodeT final : ExpressionNodeT
    {
        unsigned TargetId;
        std::string Id;
    };

    struct ConstantListNodeT final : ExpressionNodeT
    {
        unsigned TargetId;
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
