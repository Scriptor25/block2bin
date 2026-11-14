module;

#include <json/json.hxx>

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <vector>

export module b2b.project;

import b2b.opcode;
import b2b.tree;

export namespace b2b
{
    struct ValueT;
    struct NumberT;
    struct StringT;
    struct ArrayT;
    struct MutationT;
    struct ProcedureCallT;
    struct ProcedurePrototypeT;
    struct ControlStopT;
    struct BlockRefT;
    struct IdRefT;
    struct ArrayRefT;
    struct PrimitiveRefT;
    struct BroadcastRefT;
    struct VariableRefT;
    struct InputT;
    struct ObscuredInputT;
    struct FieldT;
    struct BlockT;
    struct CommentT;
    struct AssetT;
    struct CostumeT;
    struct SoundT;
    struct MonitorT;
    struct VariableT;
    struct ListT;
    struct TargetT;
    struct StageT;
    struct SpriteT;
    struct MetaT;
    struct ProjectT;

    using ValuePtr = std::unique_ptr<ValueT>;
    using MutationPtr = std::unique_ptr<MutationT>;
    using BlockRefPtr = std::unique_ptr<BlockRefT>;
    using InputPtr = std::unique_ptr<InputT>;
    using AssetPtr = std::unique_ptr<AssetT>;
    using TargetPtr = std::unique_ptr<TargetT>;

    enum PrimitiveRefE
    {
        Number          = 4,
        PositiveNumber  = 5,
        PositiveInteger = 6,
        Integer         = 7,
        Angle           = 8,
        Color           = 9,
        String          = 10,
    };

    struct ValueT
    {
        ValueT() = default;

        ValueT(const ValueT &) = delete;
        ValueT &operator=(const ValueT &) = delete;

        ValueT(ValueT &&) noexcept = default;
        ValueT &operator=(ValueT &&) noexcept = default;

        virtual ~ValueT() = default;

        [[nodiscard]] virtual ExpressionNodePtr GenerateExpression() const = 0;
    };

    struct NumberT final : ValueT
    {
        [[nodiscard]] ExpressionNodePtr GenerateExpression() const override;

        long double Value;
    };

    struct StringT final : ValueT
    {
        [[nodiscard]] ExpressionNodePtr GenerateExpression() const override;

        std::string Value;
    };

    struct ArrayT final : ValueT
    {
        [[nodiscard]] ExpressionNodePtr GenerateExpression() const override;

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

        [[nodiscard]] virtual ExpressionNodePtr GenerateExpression(
            const ProjectT &project,
            const TargetPtr &target) const = 0;
    };

    struct IdRefT final : BlockRefT
    {
        [[nodiscard]] ExpressionNodePtr GenerateExpression(
            const ProjectT &project,
            const TargetPtr &target) const override;

        std::string Id;
    };

    struct ArrayRefT : BlockRefT
    {
    };

    struct PrimitiveRefT final : ArrayRefT
    {
        [[nodiscard]] ExpressionNodePtr GenerateExpression(
            const ProjectT &project,
            const TargetPtr &target) const override;

        PrimitiveRefE Type;
        std::string Value;
    };

    struct BroadcastRefT final : ArrayRefT
    {
        [[nodiscard]] ExpressionNodePtr GenerateExpression(
            const ProjectT &project,
            const TargetPtr &target) const override;

        std::string Name;
        std::string Id;
    };

    struct VariableRefT final : ArrayRefT
    {
        [[nodiscard]] ExpressionNodePtr GenerateExpression(
            const ProjectT &project,
            const TargetPtr &target) const override;

        bool IsList;
        std::string Name;
        std::string Id;
        std::optional<double> X;
        std::optional<double> Y;
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
        [[nodiscard]] ExpressionNodePtr GenerateExpression(const ProjectT &project, const TargetPtr &target) const;

        ValuePtr Value;
        std::optional<std::string> Id;
    };

    struct BlockT final : BlockRefT
    {
        [[nodiscard]] ExpressionNodePtr GenerateExpression(
            const ProjectT &project,
            const TargetPtr &target) const override;
        [[nodiscard]] StatementNodePtr GenerateStatement(const ProjectT &project, const TargetPtr &target) const;
        [[nodiscard]] ParentNodePtr GenerateParent(const ProjectT &project, const TargetPtr &target) const;

        OpcodeE Opcode;
        std::optional<std::string> Next;
        std::optional<std::string> Parent;
        std::map<std::string, InputPtr> Inputs;
        std::map<std::string, FieldT> Fields;
        bool Shadow;
        bool TopLevel;
        std::optional<double> X;
        std::optional<double> Y;
        std::optional<std::string> Comment;
        std::optional<MutationPtr> Mutation;
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
        std::optional<std::string> SpriteName;
        ValuePtr Value;
        double Width;
        double Height;
        double X;
        double Y;
        bool Visible;
        std::optional<double> SliderMin;
        std::optional<double> SliderMax;
        std::optional<bool> IsDiscrete;
    };

    struct VariableT final
    {
        std::string Name;
        ValuePtr Value;
        std::optional<bool> IsCloud;
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

        unsigned Id = ~0u;
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
        std::optional<double> Tempo;
        std::optional<std::string> VideoState;
        std::optional<double> VideoTransparency;
        std::optional<std::string> TextToSpeechLanguage;
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
}

export namespace data
{
    template<>
    struct serializer<json::node, b2b::ProjectT>
    {
        static bool from_data(const json::node &json, b2b::ProjectT &reference);
    };

    template<>
    struct serializer<json::node, b2b::TargetPtr>
    {
        static bool from_data(const json::node &json, b2b::TargetPtr &reference);
    };

    template<>
    struct serializer<json::node, b2b::TargetT>
    {
        static bool from_data(const json::node &json, b2b::TargetT &reference);
    };

    template<>
    struct serializer<json::node, b2b::SpriteT>
    {
        static bool from_data(const json::node &json, b2b::SpriteT &reference);
    };

    template<>
    struct serializer<json::node, b2b::StageT>
    {
        static bool from_data(const json::node &json, b2b::StageT &reference);
    };

    template<>
    struct serializer<json::node, b2b::MonitorT>
    {
        static bool from_data(const json::node &json, b2b::MonitorT &reference);
    };

    template<>
    struct serializer<json::node, b2b::MetaT>
    {
        static bool from_data(const json::node &json, b2b::MetaT &reference);
    };

    template<>
    struct serializer<json::node, b2b::VariableT>
    {
        static bool from_data(const json::node &json, b2b::VariableT &reference);
    };

    template<>
    struct serializer<json::node, b2b::ListT>
    {
        static bool from_data(const json::node &json, b2b::ListT &reference);
    };

    template<>
    struct serializer<json::node, b2b::CommentT>
    {
        static bool from_data(const json::node &json, b2b::CommentT &reference);
    };

    template<>
    struct serializer<json::node, b2b::AssetPtr>
    {
        static bool from_data(const json::node &json, b2b::AssetPtr &reference);
    };

    template<>
    struct serializer<json::node, b2b::AssetT>
    {
        static bool from_data(const json::node &json, b2b::AssetT &reference);
    };

    template<>
    struct serializer<json::node, b2b::CostumeT>
    {
        static bool from_data(const json::node &json, b2b::CostumeT &reference);
    };

    template<>
    struct serializer<json::node, b2b::SoundT>
    {
        static bool from_data(const json::node &json, b2b::SoundT &reference);
    };

    template<>
    struct serializer<json::node, b2b::MutationPtr>
    {
        static bool from_data(const json::node &json, b2b::MutationPtr &reference);
    };

    template<>
    struct serializer<json::node, b2b::MutationT>
    {
        static bool from_data(const json::node &json, b2b::MutationT &reference);
    };

    template<>
    struct serializer<json::node, b2b::ProcedureCallT>
    {
        static bool from_data(const json::node &json, b2b::ProcedureCallT &reference);
    };

    template<>
    struct serializer<json::node, b2b::ProcedurePrototypeT>
    {
        static bool from_data(const json::node &json, b2b::ProcedurePrototypeT &reference);
    };

    template<>
    struct serializer<json::node, b2b::ControlStopT>
    {
        static bool from_data(const json::node &json, b2b::ControlStopT &reference);
    };

    template<>
    struct serializer<json::node, b2b::InputPtr>
    {
        static bool from_data(const json::node &json, b2b::InputPtr &reference);
    };

    template<>
    struct serializer<json::node, b2b::InputT>
    {
        static bool from_data(const json::node &json, b2b::InputT &reference);
    };

    template<>
    struct serializer<json::node, b2b::ObscuredInputT>
    {
        static bool from_data(const json::node &json, b2b::ObscuredInputT &reference);
    };

    template<>
    struct serializer<json::node, b2b::BlockRefPtr>
    {
        static bool from_data(const json::node &json, b2b::BlockRefPtr &reference);
    };

    template<>
    struct serializer<json::node, b2b::IdRefT>
    {
        static bool from_data(const json::node &json, b2b::IdRefT &reference);
    };

    template<>
    struct serializer<json::node, b2b::PrimitiveRefT>
    {
        static bool from_data(const json::node &json, b2b::PrimitiveRefT &reference);
    };

    template<>
    struct serializer<json::node, b2b::BroadcastRefT>
    {
        static bool from_data(const json::node &json, b2b::BroadcastRefT &reference);
    };

    template<>
    struct serializer<json::node, b2b::VariableRefT>
    {
        static bool from_data(const json::node &json, b2b::VariableRefT &reference);
    };

    template<>
    struct serializer<json::node, b2b::BlockT>
    {
        static bool from_data(const json::node &json, b2b::BlockT &reference);
    };

    template<>
    struct serializer<json::node, b2b::FieldT>
    {
        static bool from_data(const json::node &json, b2b::FieldT &reference);
    };

    template<>
    struct serializer<json::node, b2b::ValuePtr>
    {
        static bool from_data(const json::node &json, b2b::ValuePtr &reference);
    };

    template<>
    struct serializer<json::node, b2b::NumberT>
    {
        static bool from_data(const json::node &json, b2b::NumberT &reference);
    };

    template<>
    struct serializer<json::node, b2b::StringT>
    {
        static bool from_data(const json::node &json, b2b::StringT &reference);
    };

    template<>
    struct serializer<json::node, b2b::ArrayT>
    {
        static bool from_data(const json::node &json, b2b::ArrayT &reference);
    };
}
