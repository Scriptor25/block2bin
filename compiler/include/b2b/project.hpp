#pragma once

// #define JSON_ASSERT(x)

#include <map>
#include <string>
#include <vector>
#include <b2b/opcode.hpp>
#include <b2b/option.hpp>
#include <b2b/project_fwd.hpp>
#include <b2b/tree_fwd.hpp>
#include <nlohmann/json.hpp>

namespace b2b
{
    struct ValueT
    {
        ValueT() = default;

        ValueT(const ValueT &) = delete;
        ValueT &operator=(const ValueT &) = delete;

        ValueT(ValueT &&) noexcept = default;
        ValueT &operator=(ValueT &&) noexcept = default;

        virtual ~ValueT() = default;

        virtual ExpressionNodePtr GenerateExpression() const = 0;
    };

    struct NumberT final : ValueT
    {
        ExpressionNodePtr GenerateExpression() const override;

        long double Value;
    };

    struct StringT final : ValueT
    {
        ExpressionNodePtr GenerateExpression() const override;

        std::string Value;
    };

    struct ArrayT final : ValueT
    {
        ExpressionNodePtr GenerateExpression() const override;

        std::vector<ValuePtr> Values;
    };

    struct MutationT
    {
        MutationT() = default;

        MutationT(const MutationT &) = delete;
        MutationT &operator=(const MutationT &) = delete;

        MutationT(MutationT &&) noexcept = default;
        MutationT &operator=(MutationT &&) noexcept = default;

        virtual ~MutationT() = default;

        std::string TagName;
        std::vector<ValuePtr> Children;
    };

    struct ProcedureCallT final : MutationT
    {
        std::string ProcCode;
        std::vector<std::string> ArgumentIds;
        bool Warp;
    };

    struct ProcedurePrototypeT final : MutationT
    {
        std::string ProcCode;
        std::vector<std::string> ArgumentIds;
        std::vector<std::string> ArgumentNames;
        std::vector<std::string> ArgumentDefaults;
        bool Warp;
    };

    struct ControlStopT final : MutationT
    {
        bool HasNext;
    };

    struct BlockRefT
    {
        BlockRefT() = default;

        BlockRefT(const BlockRefT &) = delete;
        BlockRefT &operator=(const BlockRefT &) = delete;

        BlockRefT(BlockRefT &&) noexcept = default;
        BlockRefT &operator=(BlockRefT &&) noexcept = default;

        virtual ~BlockRefT() = default;

        virtual ExpressionNodePtr GenerateExpression(const ProjectT &project, const TargetPtr &target) const = 0;
    };

    struct IdRefT final : BlockRefT
    {
        ExpressionNodePtr GenerateExpression(const ProjectT &project, const TargetPtr &target) const override;

        std::string Id;
    };

    struct ArrayRefT : BlockRefT
    {
    };

    struct PrimitiveRefT final : ArrayRefT
    {
        ExpressionNodePtr GenerateExpression(const ProjectT &project, const TargetPtr &target) const override;

        PrimitiveRefE Type;
        std::string Value;
    };

    struct BroadcastRefT final : ArrayRefT
    {
        ExpressionNodePtr GenerateExpression(const ProjectT &project, const TargetPtr &target) const override;

        std::string Name;
        std::string Id;
    };

    struct VariableRefT final : ArrayRefT
    {
        ExpressionNodePtr GenerateExpression(const ProjectT &project, const TargetPtr &target) const override;

        bool IsList;
        std::string Name;
        std::string Id;
        Option<double> X;
        Option<double> Y;
    };

    struct InputT
    {
        InputT() = default;

        InputT(const InputT &) = delete;
        InputT &operator=(const InputT &) = delete;

        InputT(InputT &&) noexcept = default;
        InputT &operator=(InputT &&) noexcept = default;

        virtual ~InputT() = default;

        bool IsShadow{};
        BlockRefPtr Block;
    };

    struct ObscuredInputT final : InputT
    {
        BlockRefPtr Shadow;
    };

    struct FieldT final
    {
        ExpressionNodePtr GenerateExpression(const ProjectT &project, const TargetPtr &target) const;

        ValuePtr Value;
        Option<std::string> Id;
    };

    struct BlockT final : BlockRefT
    {
        ExpressionNodePtr GenerateExpression(const ProjectT &project, const TargetPtr &target) const override;
        StatementNodePtr GenerateStatement(const ProjectT &project, const TargetPtr &target) const;
        ParentNodePtr GenerateParent(const ProjectT &project, const TargetPtr &target) const;

        OpcodeE Opcode;
        Option<std::string> Next;
        Option<std::string> Parent;
        std::map<std::string, InputPtr> Inputs;
        std::map<std::string, FieldT> Fields;
        bool Shadow;
        bool TopLevel;
        Option<double> X;
        Option<double> Y;
        Option<std::string> Comment;
        Option<MutationPtr> Mutation;
    };

    struct CommentT final
    {
        std::string BlockId;
        double X;
        double Y;
        double Width;
        double Height;
        bool Minimized;
        std::string Text;
    };

    struct AssetT
    {
        AssetT() = default;

        AssetT(const AssetT &) = delete;
        AssetT &operator=(const AssetT &) = delete;

        AssetT(AssetT &&) noexcept = default;
        AssetT &operator=(AssetT &&) noexcept = default;

        virtual ~AssetT() = default;

        std::string AssetId;
        std::string Name;
        std::string MD5Ext;
        std::string DataFormat;
    };

    struct CostumeT final : AssetT
    {
        double RotationCenterX{};
        double RotationCenterY{};
    };

    struct SoundT final : AssetT
    {
        unsigned Rate{};
        unsigned SampleCount{};
    };

    struct MonitorT final
    {
        std::string Id;
        std::string Mode;
        std::map<std::string, std::string> Params;
        Option<std::string> SpriteName;
        ValuePtr Value;
        double Width;
        double Height;
        double X;
        double Y;
        bool Visible;
        Option<double> SliderMin;
        Option<double> SliderMax;
        Option<bool> IsDiscrete;
    };

    struct VariableT final
    {
        std::string Name;
        ValuePtr Value;
        Option<bool> IsCloud;
    };

    struct ListT final
    {
        std::string Name;
        std::vector<ValuePtr> Values;
    };

    struct TargetT
    {
        TargetT() = default;

        TargetT(const TargetT &) = delete;
        TargetT &operator=(const TargetT &) = delete;

        TargetT(TargetT &&) noexcept = default;
        TargetT &operator=(TargetT &&) noexcept = default;

        virtual ~TargetT() = default;

        std::string Name;
        std::map<std::string, VariableT> Variables;
        std::map<std::string, ListT> Lists;
        std::map<std::string, std::string> Broadcasts;
        std::map<std::string, BlockRefPtr> Blocks;
        std::map<std::string, CommentT> Comments;
        unsigned CurrentCostume{};
        std::vector<AssetPtr> Costumes;
        std::vector<AssetPtr> Sounds;
        unsigned LayerOrder{};
        double Volume{};
    };

    struct StageT final : TargetT
    {
        Option<double> Tempo;
        Option<std::string> VideoState;
        Option<double> VideoTransparency;
        Option<std::string> TextToSpeechLanguage;
    };

    struct SpriteT final : TargetT
    {
        bool Visible;
        double X;
        double Y;
        double Size;
        double Direction;
        bool Draggable;
        std::string RotationStyle;
    };

    struct MetaT final
    {
        std::string SemVer;
        std::string VM;
        std::string Agent;
    };

    struct ProjectT final
    {
        std::vector<TargetPtr> Targets;
        std::vector<MonitorT> Monitors;
        std::vector<std::string> Extensions;
        MetaT Meta;
    };

    void GenerateStatements(
        std::vector<StatementNodePtr> &nodes,
        const ProjectT &project,
        const TargetPtr &target,
        const BlockT &block);

    template<typename T>
    void from_json(const nlohmann::json &json, Option<T> &reference)
    {
        if (json.is_null() || json.is_binary() || json.is_discarded())
        {
            reference = Option<T>();
            return;
        }

        reference = Option<T>(json.get<T>());
    }

    void from_json(const nlohmann::json &json, ProjectT &reference);

    void from_json(const nlohmann::json &json, TargetPtr &reference);
    void from_json(const nlohmann::json &json, TargetT &reference);
    void from_json(const nlohmann::json &json, SpriteT &reference);
    void from_json(const nlohmann::json &json, StageT &reference);

    void from_json(const nlohmann::json &json, MonitorT &reference);

    void from_json(const nlohmann::json &json, MetaT &reference);

    void from_json(const nlohmann::json &json, VariableT &reference);

    void from_json(const nlohmann::json &json, ListT &reference);

    void from_json(const nlohmann::json &json, CommentT &reference);

    void from_json(const nlohmann::json &json, AssetPtr &reference);
    void from_json(const nlohmann::json &json, AssetT &reference);
    void from_json(const nlohmann::json &json, CostumeT &reference);
    void from_json(const nlohmann::json &json, SoundT &reference);

    void from_json(const nlohmann::json &json, MutationPtr &reference);
    void from_json(const nlohmann::json &json, MutationT &reference);
    void from_json(const nlohmann::json &json, ProcedureCallT &reference);
    void from_json(const nlohmann::json &json, ProcedurePrototypeT &reference);
    void from_json(const nlohmann::json &json, ControlStopT &reference);

    void from_json(const nlohmann::json &json, InputPtr &reference);
    void from_json(const nlohmann::json &json, InputT &reference);
    void from_json(const nlohmann::json &json, ObscuredInputT &reference);

    void from_json(const nlohmann::json &json, BlockRefPtr &reference);
    void from_json(const nlohmann::json &json, IdRefT &reference);
    void from_json(const nlohmann::json &json, PrimitiveRefT &reference);
    void from_json(const nlohmann::json &json, BroadcastRefT &reference);
    void from_json(const nlohmann::json &json, VariableRefT &reference);
    void from_json(const nlohmann::json &json, BlockT &reference);

    void from_json(const nlohmann::json &json, FieldT &reference);

    void from_json(const nlohmann::json &json, ValuePtr &reference);
    void from_json(const nlohmann::json &json, NumberT &reference);
    void from_json(const nlohmann::json &json, StringT &reference);
    void from_json(const nlohmann::json &json, ArrayT &reference);
}
