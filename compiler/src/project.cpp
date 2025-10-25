#include <b2b/common.hpp>
#include <b2b/project.hpp>
#include <b2b/tree.hpp>

b2b::ExpressionNodePtr b2b::NumberT::GenerateExpression() const
{
    auto node = std::make_unique<ConstantFloatingPointNodeT>();
    node->Value = Value;
    return std::move(node);
}

b2b::ExpressionNodePtr b2b::StringT::GenerateExpression() const
{
    auto node = std::make_unique<ConstantStringNodeT>();
    node->Value = Value;
    return std::move(node);
}

b2b::ExpressionNodePtr b2b::ArrayT::GenerateExpression() const
{
    auto node = std::make_unique<ConstantArrayNodeT>();
    for (auto &value : Values)
    {
        node->Values.emplace_back(value->GenerateExpression());
    }
    return std::move(node);
}

b2b::ExpressionNodePtr b2b::IdRefT::GenerateExpression(const ProjectT &project, const TargetPtr &target) const
{
    return target->Blocks.at(Id)->GenerateExpression(project, target);
}

b2b::ExpressionNodePtr b2b::PrimitiveRefT::GenerateExpression(const ProjectT &project, const TargetPtr &target) const
{
    switch (Type)
    {
    case Number:
    {
        auto node = std::make_unique<ConstantFloatingPointNodeT>();
        node->Value = std::stold(Value);
        return std::move(node);
    }
    case PositiveNumber:
    {
        auto node = std::make_unique<ConstantFloatingPointNodeT>();
        node->Value = std::stold(Value);
        return std::move(node);
    }
    case PositiveInteger:
    {
        auto node = std::make_unique<ConstantIntegerNodeT>();
        node->Value = std::stoull(Value);
        return std::move(node);
    }
    case Integer:
    {
        auto node = std::make_unique<ConstantIntegerNodeT>();
        node->Value = std::stoll(Value);
        return std::move(node);
    }
    case Angle:
    {
        auto node = std::make_unique<ConstantFloatingPointNodeT>();
        node->Value = std::stold(Value);
        return std::move(node);
    }
    case Color:
    {
        throw std::runtime_error("TODO");
    }
    case String:
    {
        auto node = std::make_unique<ConstantStringNodeT>();
        node->Value = Value;
        return std::move(node);
    }
    }

    throw std::runtime_error("undefined primitive type");
}

b2b::ExpressionNodePtr b2b::BroadcastRefT::GenerateExpression(const ProjectT &project, const TargetPtr &target) const
{
    if (target->Broadcasts.contains(Id))
    {
        auto broadcast = std::make_unique<ConstantBroadcastNodeT>();
        broadcast->Id = Id;
        return std::move(broadcast);
    }

    for (auto &foreign : project.Targets)
    {
        if (foreign->Broadcasts.contains(Id))
        {
            auto broadcast = std::make_unique<ConstantBroadcastNodeT>();
            broadcast->Id = Id;
            return std::move(broadcast);
        }
    }

    throw std::runtime_error("undefined broadcast");
}

b2b::ExpressionNodePtr b2b::VariableRefT::GenerateExpression(const ProjectT &project, const TargetPtr &target) const
{
    if (IsList)
    {
        if (target->Lists.contains(Id))
        {
            auto list = std::make_unique<ConstantListNodeT>();
            list->Id = Id;
            return std::move(list);
        }

        for (auto &foreign : project.Targets)
        {
            if (foreign->Lists.contains(Id))
            {
                auto list = std::make_unique<ConstantListNodeT>();
                list->Id = Id;
                return std::move(list);
            }
        }

        throw std::runtime_error("undefined list");
    }

    if (target->Variables.contains(Id))
    {
        auto variable = std::make_unique<ConstantVariableNodeT>();
        variable->Id = Id;
        return std::move(variable);
    }

    for (auto &foreign : project.Targets)
    {
        if (foreign->Variables.contains(Id))
        {
            auto variable = std::make_unique<ConstantVariableNodeT>();
            variable->Id = Id;
            return std::move(variable);
        }
    }

    throw std::runtime_error("undefined variable");
}

b2b::ExpressionNodePtr b2b::FieldT::GenerateExpression(const ProjectT &project, const TargetPtr &target) const
{
    if (Id)
    {
        for (auto &t : project.Targets)
        {
            if (t->Variables.contains(*Id))
            {
                auto variable = std::make_unique<ConstantVariableNodeT>();
                variable->Id = *Id;
                return std::move(variable);
            }
            if (t->Lists.contains(*Id))
            {
                auto list = std::make_unique<ConstantListNodeT>();
                list->Id = *Id;
                return std::move(list);
            }
            if (t->Broadcasts.contains(*Id))
            {
                auto broadcast = std::make_unique<ConstantBroadcastNodeT>();
                broadcast->Id = *Id;
                return std::move(broadcast);
            }
        }
        throw std::runtime_error("undefined entity");
    }

    return Value->GenerateExpression();
}

b2b::ExpressionNodePtr b2b::BlockT::GenerateExpression(const ProjectT &project, const TargetPtr &target) const
{
    auto node = std::make_unique<GenericExpressionNodeT>();
    node->Opcode = Opcode;

    const auto input_count = GetInputCount(node->Opcode);
    for (unsigned i = 0; i < input_count; ++i)
    {
        const auto input_name = GetInputName(node->Opcode, i);
        const auto &input = Inputs.at(input_name);
        node->Inputs.emplace_back(input->Block->GenerateExpression(project, target));
    }

    const auto field_count = GetFieldCount(node->Opcode);
    for (unsigned i = 0; i < field_count; ++i)
    {
        const auto field_name = GetFieldName(node->Opcode, i);
        const auto &field = Fields.at(field_name);
        node->Fields.emplace_back(field.GenerateExpression(project, target));
    }

    return std::move(node);
}

b2b::StatementNodePtr b2b::BlockT::GenerateStatement(const ProjectT &project, const TargetPtr &target) const
{
    switch (Opcode)
    {
    case control_repeat:
    {
        auto node = std::make_unique<ForEachStatementNodeT>();

        auto &input_times = Inputs.at("TIMES");
        auto &input_substack = Inputs.at("SUBSTACK");

        node->Times = input_times->Block->GenerateExpression(project, target);

        const auto &block_id = *b2b::cast<IdRefT>(input_substack->Block);
        const auto &block = *b2b::cast<BlockT>(target->Blocks.at(block_id.Id));
        GenerateStatements(node->Statements, project, target, block);

        return std::move(node);
    }
    case control_forever:
    {
        auto node = std::make_unique<WhileStatementNodeT>();

        auto &input_substack = Inputs.at("SUBSTACK");

        const auto &block_id = *b2b::cast<IdRefT>(input_substack->Block);
        const auto &block = *b2b::cast<BlockT>(target->Blocks.at(block_id.Id));
        GenerateStatements(node->Statements, project, target, block);

        return std::move(node);
    }
    case control_if:
    {
        auto node = std::make_unique<IfElseStatementNodeT>();
        node->HasElse = false;

        auto &input_condition = Inputs.at("CONDITION");
        auto &input_substack = Inputs.at("SUBSTACK");

        node->Condition = input_condition->Block->GenerateExpression(project, target);

        const auto &block_id = *b2b::cast<IdRefT>(input_substack->Block);
        const auto &block = *b2b::cast<BlockT>(target->Blocks.at(block_id.Id));
        GenerateStatements(node->ThenStatements, project, target, block);

        return std::move(node);
    }
    case control_if_else:
    {
        auto node = std::make_unique<IfElseStatementNodeT>();
        node->HasElse = true;

        auto &input_condition = Inputs.at("CONDITION");
        auto &input_substack = Inputs.at("SUBSTACK");
        auto &input_substack2 = Inputs.at("SUBSTACK2");

        node->Condition = input_condition->Block->GenerateExpression(project, target);

        const auto &block_id = *b2b::cast<IdRefT>(input_substack->Block);
        const auto &block = *b2b::cast<BlockT>(target->Blocks.at(block_id.Id));
        GenerateStatements(node->ThenStatements, project, target, block);

        const auto &block2_id = *b2b::cast<IdRefT>(input_substack2->Block);
        const auto &block2 = *b2b::cast<BlockT>(target->Blocks.at(block_id.Id));
        GenerateStatements(node->ElseStatements, project, target, block2);

        return std::move(node);
    }
    case control_repeat_until:
    {
        auto node = std::make_unique<WhileStatementNodeT>();

        auto &input_condition = Inputs.at("CONDITION");
        auto &input_substack = Inputs.at("SUBSTACK");

        auto condition = std::make_unique<NotExpressionNodeT>();
        condition->Value = input_condition->Block->GenerateExpression(project, target);
        node->Condition = std::move(condition);

        const auto &block_id = *b2b::cast<IdRefT>(input_substack->Block);
        const auto &block = *b2b::cast<BlockT>(target->Blocks.at(block_id.Id));
        GenerateStatements(node->Statements, project, target, block);

        return std::move(node);
    }
    case control_for_each:
    {
        // for ([variable] = 1; [variable] <= <value>; [variable]++) {
        //   (substack)
        // }

        auto node = std::make_unique<ForEachStatementNodeT>();

        auto &input_value = Inputs.at("VALUE");
        auto &input_substack = Inputs.at("SUBSTACK");

        auto &field_variable = Fields.at("VARIABLE");

        node->Variable = field_variable.GenerateExpression(project, target);

        node->Times = input_value->Block->GenerateExpression(project, target);

        const auto &block_id = *b2b::cast<IdRefT>(input_substack->Block);
        const auto &block = *b2b::cast<BlockT>(target->Blocks.at(block_id.Id));
        GenerateStatements(node->Statements, project, target, block);

        return std::move(node);
    }
    case control_while:
    {
        auto node = std::make_unique<WhileStatementNodeT>();

        auto &input_condition = Inputs.at("CONDITION");
        auto &input_substack = Inputs.at("SUBSTACK");

        node->Condition = input_condition->Block->GenerateExpression(project, target);

        const auto &block_id = *b2b::cast<IdRefT>(input_substack->Block);
        const auto &block = *b2b::cast<BlockT>(target->Blocks.at(block_id.Id));
        GenerateStatements(node->Statements, project, target, block);

        return std::move(node);
    }
    case control_all_at_once:
    {
        auto node = std::make_unique<InstantStatementNodeT>();

        auto &input_substack = Inputs.at("SUBSTACK");

        const auto &block_id = *b2b::cast<IdRefT>(input_substack->Block);
        const auto &block = *b2b::cast<BlockT>(target->Blocks.at(block_id.Id));
        GenerateStatements(node->Statements, project, target, block);

        return std::move(node);
    }

    default:
        break;
    }

    return GenerateExpression(project, target);
}

b2b::ParentNodePtr b2b::BlockT::GenerateParent(const ProjectT &project, const TargetPtr &target) const
{
    if (!IsEntry(Opcode))
    {
        throw std::runtime_error("invalid parent node block opcode");
    }

    switch (Opcode)
    {
    case control_start_as_clone:
    {
        auto node = std::make_unique<ConstructorNodeT>();

        if (Next)
        {
            const auto &next = *cast<BlockT>(target->Blocks.at(*Next));
            GenerateStatements(node->Statements, project, target, next);
        }

        return std::move(node);
    }
    case procedures_definition:
    {
        const auto id_ref = b2b::cast<IdRefT>(Inputs.at("custom_block")->Block);
        const auto proc_block = b2b::cast<BlockT>(target->Blocks.at(id_ref->Id));
        const auto prototype = b2b::cast<ProcedurePrototypeT>(*proc_block->Mutation);

        auto node = std::make_unique<ProcedureNodeT>();
        node->Name = prototype->ProcCode;

        for (unsigned i = 0; i < prototype->ArgumentIds.size(); ++i)
        {
            node->Parameters.emplace_back(
                prototype->ArgumentNames.at(i),
                prototype->ArgumentDefaults.at(i));
        }

        if (Next)
        {
            const auto &next = *cast<BlockT>(target->Blocks.at(*Next));
            GenerateStatements(node->Statements, project, target, next);
        }

        return std::move(node);
    }
    default:
    {
        auto node = std::make_unique<ListenerNodeT>();
        node->Event = GetName(Opcode);

        const auto input_count = GetInputCount(Opcode);
        for (unsigned i = 0; i < input_count; ++i)
        {
            const auto input_name = GetInputName(Opcode, i);
            const auto &input = Inputs.at(input_name);
            node->Inputs.emplace_back(input->Block->GenerateExpression(project, target));
        }

        const auto field_count = GetFieldCount(Opcode);
        for (unsigned i = 0; i < field_count; ++i)
        {
            const auto field_name = GetFieldName(Opcode, i);
            const auto &field = Fields.at(field_name);
            node->Fields.emplace_back(field.GenerateExpression(project, target));
        }

        if (Next)
        {
            const auto &next = *cast<BlockT>(target->Blocks.at(*Next));
            GenerateStatements(node->Statements, project, target, next);
        }

        return std::move(node);
    }
    }
}

void b2b::GenerateStatements(
    std::vector<StatementNodePtr> &nodes,
    const ProjectT &project,
    const TargetPtr &target,
    const BlockT &block)
{
    for (auto next = &block; next;)
    {
        nodes.emplace_back(next->GenerateStatement(project, target));

        if (!next->Next)
        {
            break;
        }

        auto &ref = target->Blocks.at(*next->Next);
        next = b2b::cast<BlockT>(ref);
    }
}

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
    reference.Tempo = option_from<double>(json, "tempo");
    reference.VideoState = option_from<std::string>(json, "videoState");
    reference.VideoTransparency = option_from<double>(json, "videoTransparency");
    reference.TextToSpeechLanguage = option_from<std::string>(json, "textToSpeechLanguage");
}

void b2b::from_json(const nlohmann::json &json, MonitorT &reference)
{
    reference.Id = json["id"];
    reference.Mode = json["mode"];
    reference.Params = json["params"];
    reference.SpriteName = option_from<std::string>(json, "spriteName");
    reference.Value = json["value"];
    reference.Width = json["width"];
    reference.Height = json["height"];
    reference.X = json["x"];
    reference.Y = json["y"];
    reference.Visible = json["visible"];
    reference.SliderMin = option_from<double>(json, "sliderMin");
    reference.SliderMax = option_from<double>(json, "sliderMax");
    reference.IsDiscrete = option_from<bool>(json, "isDiscrete");
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
    reference.IsCloud = option_from<bool>(json, 2);
}

void b2b::from_json(const nlohmann::json &json, ListT &reference)
{
    reference.Name = json[0];
    reference.Values = json[1];
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
    if (auto node = json["hasnext"]; node.is_string())
    {
        reference.HasNext = node.get<std::string>() == "true";
    }
    else
    {
        reference.HasNext = node.get<bool>();
    }
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
    reference.X = option_from<double>(json, 3);
    reference.Y = option_from<double>(json, 4);
}

void b2b::from_json(const nlohmann::json &json, BlockT &reference)
{
    reference.Opcode = json["opcode"];
    reference.Next = option_from<std::string>(json, "next");
    reference.Parent = option_from<std::string>(json, "parent");
    reference.Inputs = json["inputs"];
    reference.Fields = json["fields"];
    reference.Shadow = json["shadow"];
    reference.TopLevel = json["topLevel"];
    reference.X = option_from<double>(json, "x");
    reference.Y = option_from<double>(json, "y");
    reference.Comment = option_from<std::string>(json, "comment");
    reference.Mutation = option_from<MutationPtr>(json, "mutation");
}

void b2b::from_json(const nlohmann::json &json, FieldT &reference)
{
    reference.Value = json[0];
    reference.Id = option_from<std::string>(json, 1);
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
    reference.Values = json;
}
