#pragma once
#include <memory>

namespace b2b
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
}
