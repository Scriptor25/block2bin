#include <b2b/project.hpp>

void b2b::from_json(const nlohmann::json &json, ProjectT &reference)
{
    reference.Targets = json["targets"];
    reference.Monitors = json["monitors"];
    reference.Extensions = json["extensions"];
    reference.Meta = json["meta"];
}

void b2b::from_json(const nlohmann::json &json, TargetPtr &reference)
{
    if (!json["isStage"])
    {
        auto target = std::make_unique<SpriteT>();
        *target = json;
        reference = std::move(target);
    }
    else
    {
        auto target = std::make_unique<StageT>();
        *target = json;
        reference = std::move(target);
    }

    *reference = json;
}

void b2b::from_json(const nlohmann::json &json, TargetT &reference)
{
    reference.Name = json["name"];
    reference.Variables = json["variables"];
    reference.Lists = json["lists"];
    reference.Broadcasts = json["broadcasts"];
    reference.Blocks = json["blocks"];
    reference.Comments = json["comments"];
    reference.CurrentCostume = json["currentCostume"];
    reference.Costumes = json["costumes"];
    reference.Sounds = json["sounds"];
    reference.LayerOrder = json["layerOrder"];
    reference.Volume = json["volume"];
}

void b2b::from_json(const nlohmann::json &json, SpriteT &reference)
{
    reference.Visible = json["visible"];
    reference.X = json["x"];
    reference.Y = json["y"];
    reference.Size = json["size"];
    reference.Direction = json["direction"];
    reference.Draggable = json["draggable"];
    reference.RotationStyle = json["rotationStyle"];
}

void b2b::from_json(const nlohmann::json &json, StageT &reference)
{
    reference.Tempo = json["tempo"];
    reference.VideoState = json["videoState"];
    reference.VideoTransparency = json["videoTransparency"];
    reference.TextToSpeechLanguage = json["textToSpeechLanguage"];
}

void b2b::from_json(const nlohmann::json &json, MonitorT &reference)
{
    reference.Id = json["id"];
    reference.Mode = json["mode"];
    reference.Params = json["params"];
    reference.SpriteName = json["spriteName"];
    reference.Value = json["value"];
    reference.Width = json["width"];
    reference.Height = json["height"];
    reference.X = json["x"];
    reference.Y = json["y"];
    reference.Visible = json["visible"];
    reference.SliderMin = json["sliderMin"];
    reference.SliderMax = json["sliderMax"];
    reference.IsDiscrete = json["isDiscrete"];
}

void b2b::from_json(const nlohmann::json &json, MetaT &reference)
{
    reference.SemVer = json["semver"];
    reference.VM = json["vm"];
    reference.Agent = json["agent"];
}

void b2b::from_json(const nlohmann::json &json, VariableT &reference)
{
    reference.Name = json[0];
    reference.Value = json[1];
    reference.IsCloud = json[2];
}

void b2b::from_json(const nlohmann::json &json, ListT &reference)
{
    reference.Name = json[0];
    reference.Values = json[1];
}

void b2b::from_json(const nlohmann::json &json, OpcodeE &reference)
{
    reference = ToOpcode(json);
}

void b2b::from_json(const nlohmann::json &json, CommentT &reference)
{
    reference.BlockId = json["blockId"];
    reference.X = json["x"];
    reference.Y = json["y"];
    reference.Width = json["width"];
    reference.Height = json["height"];
    reference.Minimized = json["minimized"];
    reference.Text = json["text"];
}

void b2b::from_json(const nlohmann::json &json, AssetPtr &reference)
{
    if (json.contains("rotationCenterX") || json.contains("rotationCenterY"))
    {
        auto asset = std::make_unique<CostumeT>();
        *asset = json;
        reference = std::move(asset);
    }
    else
    {
        auto asset = std::make_unique<SoundT>();
        *asset = json;
        reference = std::move(asset);
    }

    *reference = json;
}

void b2b::from_json(const nlohmann::json &json, AssetT &reference)
{
    reference.AssetId = json["assetId"];
    reference.Name = json["name"];
    reference.MD5Ext = json["md5ext"];
    reference.DataFormat = json["dataFormat"];
}

void b2b::from_json(const nlohmann::json &json, CostumeT &reference)
{
    reference.RotationCenterX = json["rotationCenterX"];
    reference.RotationCenterY = json["rotationCenterY"];
}

void b2b::from_json(const nlohmann::json &json, SoundT &reference)
{
    reference.Rate = json["rate"];
    reference.SampleCount = json["sampleCount"];
}

void b2b::from_json(const nlohmann::json &json, MutationPtr &reference)
{
    if (json.contains("hasnext"))
    {
        auto mutation = std::make_unique<ControlStopT>();
        *mutation = json;
        reference = std::move(mutation);
    }
    else if (json.contains("argumentnames") || json.contains("argumentdefaults"))
    {
        auto mutation = std::make_unique<ProcedurePrototypeT>();
        *mutation = json;
        reference = std::move(mutation);
    }
    else
    {
        auto mutation = std::make_unique<ProcedureCallT>();
        *mutation = json;
        reference = std::move(mutation);
    }

    *reference = json;
}

void b2b::from_json(const nlohmann::json &json, MutationT &reference)
{
    reference.TagName = json["tagName"];
    reference.Children = json["children"];
}

void b2b::from_json(const nlohmann::json &json, ProcedureCallT &reference)
{
    reference.ProcCode = json["proccode"];
    reference.ArgumentIds = nlohmann::json::parse(json["argumentids"].get<std::string>());
    reference.Warp = nlohmann::json::parse(json["warp"].get<std::string>());
}

void b2b::from_json(const nlohmann::json &json, ProcedurePrototypeT &reference)
{
    reference.ProcCode = json["proccode"];
    reference.ArgumentIds = nlohmann::json::parse(json["argumentids"].get<std::string>());
    reference.ArgumentNames = nlohmann::json::parse(json["argumentnames"].get<std::string>());
    reference.ArgumentDefaults = nlohmann::json::parse(json["argumentdefaults"].get<std::string>());
    reference.Warp = nlohmann::json::parse(json["warp"].get<std::string>());
}

void b2b::from_json(const nlohmann::json &json, ControlStopT &reference)
{
    reference.HasNext = json["hasnext"];
}

void b2b::from_json(const nlohmann::json &json, InputPtr &reference)
{
    if (json[0] != 3)
    {
        auto input = std::make_unique<InputT>();
        *input = json;
        reference = std::move(input);
    }
    else
    {
        auto input = std::make_unique<ObscuredInputT>();
        *input = json;
        reference = std::move(input);
    }
}

void b2b::from_json(const nlohmann::json &json, InputT &reference)
{
    reference.IsShadow = json[0] != 2;
    reference.Block = json[1];
}

void b2b::from_json(const nlohmann::json &json, ObscuredInputT &reference)
{
    reference.IsShadow = json[0] != 2;
    reference.Block = json[1];
    reference.Shadow = json[2];
}

void b2b::from_json(const nlohmann::json &json, BlockRefPtr &reference)
{
    if (json.is_string())
    {
        auto ref = std::make_unique<IdRefT>();
        *ref = json;
        reference = std::move(ref);
        return;
    }

    if (json.is_array())
    {
        switch (static_cast<unsigned>(json[0]))
        {
        case 11:
        {
            auto ref = std::make_unique<BroadcastRefT>();
            *ref = json;
            reference = std::move(ref);
            break;
        }
        case 12:
        case 13:
        {
            auto ref = std::make_unique<VariableRefT>();
            *ref = json;
            reference = std::move(ref);
            break;
        }
        default:
        {
            auto ref = std::make_unique<PrimitiveRefT>();
            *ref = json;
            reference = std::move(ref);
            break;
        }
        }
        return;
    }

    auto ref = std::make_unique<BlockT>();
    *ref = json;
    reference = std::move(ref);
}

void b2b::from_json(const nlohmann::json &json, IdRefT &reference)
{
    reference.Id = json;
}

void b2b::from_json(const nlohmann::json &json, PrimitiveRefT &reference)
{
    reference.Type = static_cast<PrimitiveRefE>(static_cast<unsigned>(json[0]));
    reference.Value = json[1];
}

void b2b::from_json(const nlohmann::json &json, BroadcastRefT &reference)
{
    reference.Name = json[1];
    reference.Id = json[2];
}

void b2b::from_json(const nlohmann::json &json, VariableRefT &reference)
{
    reference.IsList = json[0] == 13;
    reference.Name = json[1];
    reference.Id = json[2];
    reference.X = json[3];
    reference.Y = json[4];
}

void b2b::from_json(const nlohmann::json &json, BlockT &reference)
{
    reference.Opcode = json["opcode"];
    reference.Next = json["next"];
    reference.Parent = json["parent"];
    reference.Inputs = json["inputs"];
    reference.Fields = json["fields"];
    reference.Shadow = json["shadow"];
    reference.TopLevel = json["topLevel"];
    reference.X = json["x"];
    reference.Y = json["y"];
    reference.Comment = json["comment"];
    reference.Mutation = json["mutation"];
}

void b2b::from_json(const nlohmann::json &json, FieldT &reference)
{
    reference.Value = json[0];
    reference.Id = json[1];
}

void b2b::from_json(const nlohmann::json &json, ValuePtr &reference)
{
    if (json.is_number())
    {
        auto value = std::make_unique<NumberT>();
        *value = json;
        reference = std::move(value);
    }
    else if (json.is_string())
    {
        auto value = std::make_unique<StringT>();
        *value = json;
        reference = std::move(value);
    }
    else if (json.is_array())
    {
        auto value = std::make_unique<ArrayT>();
        *value = json;
        reference = std::move(value);
    }
}

void b2b::from_json(const nlohmann::json &json, NumberT &reference)
{
    reference.Value = json;
}

void b2b::from_json(const nlohmann::json &json, StringT &reference)
{
    reference.Value = json;
}

void b2b::from_json(const nlohmann::json &json, ArrayT &reference)
{
    reference.Value = json;
}
