#pragma once

#include <map>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace b2b
{
    struct MutationT
    {
        /**
         * Always equal to "mutation".
         */
        std::string TagName;

        /**
         * Seems to always be an empty array.
         */
        std::vector<nlohmann::json> Children;
    };

    struct ProceduresCallT : MutationT
    {
        std::string ProcCode;
        std::vector<std::string> ArgumentIds;
        bool Warp;
    };

    struct ProceduresPrototypeT : ProceduresCallT
    {
        std::vector<std::string> ArgumentNames;
    };

    struct ControlStopT : MutationT
    {
        bool HasNext;
    };

    /**
     * Fields are text boxes, drop-down menus, etc. These are used directly in blocks where there is an input
     * into which one cannot drop a reporter. However, more often than not, one should be able to do this;
     * in this case no field exists directly in the block, but an input does, and that input may have a shadow
     * block in it. A shadow block is a reporter in an input for which one can enter or pick a value, and which
     * cannot be dragged around but can be replaced by a normal reporter. Scratch internally considers these to
     * be blocks, although they are not usually thought of as such. (These notions come from Blockly, which
     * Scratch Blocks is based on.)
     */
    struct BlockT
    {
        /**
         * A string naming the block. A list of block opcodes can be found here.
         */
        std::string Opcode;

        /**
         * The ID of the following block or null.
         */
        std::optional<std::string> Next;

        /**
         * If the block is a stack block and is preceded, this is the ID of the preceding block. If the
         * block is the first stack block in a C mouth, this is the ID of the C block. If the block is
         * an input to another block, this is the ID of that other block. Otherwise, it is null.
         */
        std::optional<std::string> Parent;

        /**
         * An object associating names with arrays representing inputs into which other blocks may be dropped,
         * including C mouths. The first element of each array is 1 if the input is a shadow, 2 if there is no
         * shadow, and 3 if there is a shadow, but it is obscured by the input. The second is either the ID of
         * the input or an array representing it as described in the table below. If there is an obscured shadow,
         * the third element is its ID or an array representing it.
         */
        std::map<std::string, nlohmann::json> Inputs;

        /**
         * An object associating names with arrays representing fields. The first element of each array is the
         * field's value. For certain fields, such as variable and broadcast dropdown menus, there is also a
         * second element, which is the ID of the field's value.
         */
        std::map<std::string, nlohmann::json> Fields;

        /**
         * True if this is a shadow block and false otherwise.
         */
        bool Shadow;

        /**
         * False if the block has a parent and true otherwise.
         */
        bool TopLevel;

        std::optional<double> X;
        std::optional<double> Y;
        std::optional<std::string> Comment;
        std::optional<MutationT> Mutation;
    };

    struct CommentT
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
        std::string AssetId;
        std::string Name;
        std::string MD5Ext;
        std::string DataFormat;
    };

    struct CostumeT : AssetT
    {
        double RotationCenterX;
        double RotationCenterY;
    };

    struct SoundT : AssetT
    {
        unsigned Rate;
        unsigned SampleCount;
    };

    struct MonitorT
    {
        std::string Id;
        std::string Mode;
        std::map<std::string, std::string> Params;
        std::string SpriteName;
        std::string Value;
        double Width;
        double Height;
        double X;
        double Y;
        bool Visible;
        double SliderMin;
        double SliderMax;
        bool IsDiscrete;
    };

    struct VariableT
    {
        std::string Name;
        std::string Value;
        bool IsCloud;
    };

    struct ListT
    {
        std::string Name;
        std::vector<std::string> Values;
    };

    struct TargetT
    {
        bool IsStage;
        std::string Name;
        std::map<std::string, VariableT> Variables;
        std::map<std::string, ListT> Lists;
        std::map<std::string, std::string> Broadcasts;
        std::map<std::string, BlockT> Blocks;
        std::map<std::string, CommentT> Comments;
        unsigned CurrentCostume;
        std::vector<CostumeT> Costumes;
        std::vector<SoundT> Sounds;
        unsigned LayerOrder;
        double Volume;
    };

    struct StageT : TargetT
    {
        double Tempo;
        std::string VideoState;
        double VideoTransparency;
        std::string TextToSpeechLanguage;
    };

    struct SpriteT : TargetT
    {
        bool Visible;
        double X;
        double Y;
        double Size;
        double Direction;
        bool Draggable;
        std::string RotationStyle;
    };

    struct ExtensionT
    {
    };

    struct MetaT
    {
        std::string SemVer;
        std::string VM;
        std::string Agent;
    };

    struct ProjectT
    {
        std::vector<TargetT> Targets;
        std::vector<MonitorT> Monitors;
        std::vector<ExtensionT> Extensions;
        MetaT Meta;
    };
}
