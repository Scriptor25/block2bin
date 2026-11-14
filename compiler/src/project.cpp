module;

#include <json/json.hxx>

#include <memory>

module b2b.project;

import b2b.common;

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

b2b::ExpressionNodePtr b2b::IdRefT::GenerateExpression(
    const ProjectT &project,
    const TargetPtr &target) const
{
    return target->Blocks.at(Id)->GenerateExpression(project, target);
}

b2b::ExpressionNodePtr b2b::PrimitiveRefT::GenerateExpression(
    const ProjectT &project,
    const TargetPtr &target) const
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

b2b::ExpressionNodePtr b2b::BroadcastRefT::GenerateExpression(
    const ProjectT &project,
    const TargetPtr &target) const
{
    for (auto &t : project.Targets)
    {
        if (t->Broadcasts.contains(Id))
        {
            auto broadcast = std::make_unique<ConstantBroadcastNodeT>();
            broadcast->TargetId = t->Id;
            broadcast->Id = Id;
            return std::move(broadcast);
        }
    }

    throw std::runtime_error("undefined broadcast");
}

b2b::ExpressionNodePtr b2b::VariableRefT::GenerateExpression(
    const ProjectT &project,
    const TargetPtr &target) const
{
    if (IsList)
    {
        for (auto &t : project.Targets)
        {
            if (t->Lists.contains(Id))
            {
                auto list = std::make_unique<ConstantListNodeT>();
                list->TargetId = t->Id;
                list->Id = Id;
                return std::move(list);
            }
        }

        throw std::runtime_error("undefined list");
    }

    for (auto &t : project.Targets)
    {
        if (t->Variables.contains(Id))
        {
            auto variable = std::make_unique<ConstantVariableNodeT>();
            variable->TargetId = t->Id;
            variable->Id = Id;
            return std::move(variable);
        }
    }

    throw std::runtime_error("undefined variable");
}

b2b::ExpressionNodePtr b2b::FieldT::GenerateExpression(
    const ProjectT &project,
    const TargetPtr &target) const
{
    if (Id)
    {
        for (auto &t : project.Targets)
        {
            if (t->Variables.contains(*Id))
            {
                auto variable = std::make_unique<ConstantVariableNodeT>();
                variable->TargetId = t->Id;
                variable->Id = *Id;
                return std::move(variable);
            }
            if (t->Lists.contains(*Id))
            {
                auto list = std::make_unique<ConstantListNodeT>();
                list->TargetId = t->Id;
                list->Id = *Id;
                return std::move(list);
            }
            if (t->Broadcasts.contains(*Id))
            {
                auto broadcast = std::make_unique<ConstantBroadcastNodeT>();
                broadcast->TargetId = t->Id;
                broadcast->Id = *Id;
                return std::move(broadcast);
            }
        }
        throw std::runtime_error("undefined entity");
    }

    return Value->GenerateExpression();
}

b2b::ExpressionNodePtr b2b::BlockT::GenerateExpression(
    const ProjectT &project,
    const TargetPtr &target) const
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

bool data::serializer<json::node, b2b::ProjectT>::from_data(
    const json::node &node,
    b2b::ProjectT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["targets"] >> value.Targets;
    ok &= node["monitors"] >> value.Monitors;
    ok &= node["extensions"] >> value.Extensions;
    ok &= node["meta"] >> value.Meta;

    return ok;
}

bool data::serializer<json::node, b2b::TargetPtr>::from_data(
    const json::node &node,
    b2b::TargetPtr &value)
{
    if (!node.is<json::object>())
        return false;

    bool is_stage;
    if (!(node["isStage"] >> is_stage))
        return false;

    bool ok = true;

    if (!is_stage)
    {
        auto target = std::make_unique<b2b::SpriteT>();
        ok &= node >> *target;
        value = std::move(target);
    }
    else
    {
        auto target = std::make_unique<b2b::StageT>();
        ok &= node >> *target;
        value = std::move(target);
    }

    ok &= node >> *value;

    return ok;
}

bool data::serializer<json::node, b2b::TargetT>::from_data(
    const json::node &node,
    b2b::TargetT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["name"] >> value.Name;
    ok &= node["variables"] >> value.Variables;
    ok &= node["lists"] >> value.Lists;
    ok &= node["broadcasts"] >> value.Broadcasts;
    ok &= node["blocks"] >> value.Blocks;
    ok &= node["comments"] >> value.Comments;
    ok &= node["currentCostume"] >> value.CurrentCostume;
    ok &= node["costumes"] >> value.Costumes;
    ok &= node["sounds"] >> value.Sounds;
    ok &= node["layerOrder"] >> value.LayerOrder;
    ok &= node["volume"] >> value.Volume;

    return ok;
}

bool data::serializer<json::node, b2b::SpriteT>::from_data(
    const json::node &node,
    b2b::SpriteT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["visible"] >> value.Visible;
    ok &= node["x"] >> value.X;
    ok &= node["y"] >> value.Y;
    ok &= node["size"] >> value.Size;
    ok &= node["direction"] >> value.Direction;
    ok &= node["draggable"] >> value.Draggable;
    ok &= node["rotationStyle"] >> value.RotationStyle;

    return ok;
}

bool data::serializer<json::node, b2b::StageT>::from_data(
    const json::node &node,
    b2b::StageT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["tempo"] >> value.Tempo;
    ok &= node["videoState"] >> value.VideoState;
    ok &= node["videoTransparency"] >> value.VideoTransparency;
    ok &= node["textToSpeechLanguage"] >> value.TextToSpeechLanguage;

    return ok;
}

bool data::serializer<json::node, b2b::MonitorT>::from_data(
    const json::node &node,
    b2b::MonitorT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["id"] >> value.Id;
    ok &= node["mode"] >> value.Mode;
    ok &= node["params"] >> value.Params;
    ok &= node["spriteName"] >> value.SpriteName;
    ok &= node["value"] >> value.Value;
    ok &= node["width"] >> value.Width;
    ok &= node["height"] >> value.Height;
    ok &= node["x"] >> value.X;
    ok &= node["y"] >> value.Y;
    ok &= node["visible"] >> value.Visible;
    ok &= node["sliderMin"] >> value.SliderMin;
    ok &= node["sliderMax"] >> value.SliderMax;
    ok &= node["isDiscrete"] >> value.IsDiscrete;

    return ok;
}

bool data::serializer<json::node, b2b::MetaT>::from_data(
    const json::node &node,
    b2b::MetaT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["semver"] >> value.SemVer;
    ok &= node["vm"] >> value.VM;
    ok &= node["agent"] >> value.Agent;

    return ok;
}

bool data::serializer<json::node, b2b::VariableT>::from_data(
    const json::node &node,
    b2b::VariableT &value)
{
    if (!node.is<json::array>())
        return false;

    bool ok = true;

    ok &= node[0] >> value.Name;
    ok &= node[1] >> value.Value;
    ok &= node[2] >> value.IsCloud;

    return ok;
}

bool data::serializer<json::node, b2b::ListT>::from_data(
    const json::node &node,
    b2b::ListT &value)
{
    if (!node.is<json::array>())
        return false;

    bool ok = true;

    ok &= node[0] >> value.Name;
    ok &= node[1] >> value.Values;

    return ok;
}

bool data::serializer<json::node, b2b::CommentT>::from_data(
    const json::node &node,
    b2b::CommentT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["blockId"] >> value.BlockId;
    ok &= node["x"] >> value.X;
    ok &= node["y"] >> value.Y;
    ok &= node["width"] >> value.Width;
    ok &= node["height"] >> value.Height;
    ok &= node["minimized"] >> value.Minimized;
    ok &= node["text"] >> value.Text;

    return ok;
}

bool data::serializer<json::node, b2b::AssetPtr>::from_data(
    const json::node &node,
    b2b::AssetPtr &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    if (node["rotationCenterX"] || node["rotationCenterY"])
    {
        auto asset = std::make_unique<b2b::CostumeT>();
        ok &= node >> *asset;
        value = std::move(asset);
    }
    else
    {
        auto asset = std::make_unique<b2b::SoundT>();
        ok &= node >> *asset;
        value = std::move(asset);
    }

    ok &= node >> *value;

    return ok;
}

bool data::serializer<json::node, b2b::AssetT>::from_data(
    const json::node &node,
    b2b::AssetT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["assetId"] >> value.AssetId;
    ok &= node["name"] >> value.Name;
    ok &= node["md5ext"] >> value.MD5Ext;
    ok &= node["dataFormat"] >> value.DataFormat;

    return ok;
}

bool data::serializer<json::node, b2b::CostumeT>::from_data(
    const json::node &node,
    b2b::CostumeT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["rotationCenterX"] >> value.RotationCenterX;
    ok &= node["rotationCenterY"] >> value.RotationCenterY;

    return ok;
}

bool data::serializer<json::node, b2b::SoundT>::from_data(
    const json::node &node,
    b2b::SoundT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["rate"] >> value.Rate;
    ok &= node["sampleCount"] >> value.SampleCount;

    return ok;
}

bool data::serializer<json::node, b2b::MutationPtr>::from_data(
    const json::node &node,
    b2b::MutationPtr &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    if (node["hasnext"])
    {
        auto mutation = std::make_unique<b2b::ControlStopT>();
        ok &= node >> *mutation;
        value = std::move(mutation);
    }
    else if (node["argumentnames"] || node["argumentdefaults"])
    {
        auto mutation = std::make_unique<b2b::ProcedurePrototypeT>();
        ok &= node >> *mutation;
        value = std::move(mutation);
    }
    else
    {
        auto mutation = std::make_unique<b2b::ProcedureCallT>();
        ok &= node >> *mutation;
        value = std::move(mutation);
    }

    ok &= node >> *value;

    return ok;
}

bool data::serializer<json::node, b2b::MutationT>::from_data(
    const json::node &node,
    b2b::MutationT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["tagName"] >> value.TagName;
    ok &= node["children"] >> value.Children;

    return ok;
}

bool data::serializer<json::node, b2b::ProcedureCallT>::from_data(
    const json::node &node,
    b2b::ProcedureCallT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["proccode"] >> value.ProcCode;
    // TODO: ok &= json::parse(json["argumentids"].get<std::string>()) >> reference.ArgumentIds;
    // TODO: ok &= json::parse(json["warp"].get<std::string>()) >> reference.Warp;

    return ok;
}

bool data::serializer<json::node, b2b::ProcedurePrototypeT>::from_data(
    const json::node &node,
    b2b::ProcedurePrototypeT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["proccode"] >> value.ProcCode;
    // TODO: ok &= json::parse(json["argumentids"].get<std::string>()) >> reference.ArgumentIds;
    // TODO: ok &= json::parse(json["argumentnames"].get<std::string>()) >> reference.ArgumentNames;
    // TODO: ok &= json::parse(json["argumentdefaults"].get<std::string>()) >> reference.ArgumentDefaults;
    // TODO: ok &= json::parse(json["warp"].get<std::string>()) >> reference.Warp;

    return ok;
}

bool data::serializer<json::node, b2b::ControlStopT>::from_data(
    const json::node &node,
    b2b::ControlStopT &value)
{
    if (!node.is<json::object>())
        return false;

    auto &hasnext_node = node["hasnext"];

    if (std::string str; hasnext_node >> str)
    {
        value.HasNext = str == "true";
        return true;
    }

    return hasnext_node >> value.HasNext;
}

bool data::serializer<json::node, b2b::InputPtr>::from_data(
    const json::node &node,
    b2b::InputPtr &value)
{
    if (!node.is<json::array>())
        return false;

    if (unsigned type; node[0] >> type)
    {
        if (type != 3)
        {
            auto input = std::make_unique<b2b::InputT>();
            const auto ok = node >> *input;
            value = std::move(input);
            return ok;
        }

        auto input = std::make_unique<b2b::ObscuredInputT>();
        const auto ok = node >> *input;
        value = std::move(input);
        return ok;
    }

    return false;
}

bool data::serializer<json::node, b2b::InputT>::from_data(
    const json::node &node,
    b2b::InputT &value)
{
    if (!node.is<json::array>())
        return false;

    if (unsigned type; node[0] >> type)
        value.IsShadow = type != 2;
    else
        return false;

    return node[1] >> value.Block;
}

bool data::serializer<json::node, b2b::ObscuredInputT>::from_data(
    const json::node &node,
    b2b::ObscuredInputT &value)
{
    if (!node.is<json::array>())
        return false;

    if (unsigned type; node[0] >> type)
        value.IsShadow = type != 2;
    else
        return false;

    bool ok = true;

    ok &= node[1] >> value.Block;
    ok &= node[2] >> value.Shadow;

    return ok;
}

bool data::serializer<json::node, b2b::BlockRefPtr>::from_data(
    const json::node &node,
    b2b::BlockRefPtr &value)
{
    if (node.is<json::string>())
    {
        auto ref = std::make_unique<b2b::IdRefT>();
        const auto ok = node >> *ref;
        value = std::move(ref);
        return ok;
    }

    if (node.is<json::array>())
    {
        unsigned type;
        if (!(node[0] >> type))
            return false;

        switch (type)
        {
            case 11:
            {
                auto ref = std::make_unique<b2b::BroadcastRefT>();
                const auto ok = node >> *ref;
                value = std::move(ref);
                return ok;
            }
            case 12:
            case 13:
            {
                auto ref = std::make_unique<b2b::VariableRefT>();
                const auto ok = node >> *ref;
                value = std::move(ref);
                return ok;
            }
            default:
            {
                auto ref = std::make_unique<b2b::PrimitiveRefT>();
                const auto ok = node >> *ref;
                value = std::move(ref);
                return ok;
            }
        }
    }

    auto ref = std::make_unique<b2b::BlockT>();
    const auto ok = node >> *ref;
    value = std::move(ref);
    return ok;
}

bool data::serializer<json::node, b2b::IdRefT>::from_data(
    const json::node &node,
    b2b::IdRefT &value)
{
    return node >> value.Id;
}

bool data::serializer<json::node, b2b::PrimitiveRefT>::from_data(
    const json::node &node,
    b2b::PrimitiveRefT &value)
{
    if (!node.is<json::array>())
        return false;

    if (unsigned type; node[0] >> type)
        value.Type = static_cast<b2b::PrimitiveRefE>(type);
    else
        return false;

    return node[1] >> value.Value;
}

bool data::serializer<json::node, b2b::BroadcastRefT>::from_data(
    const json::node &node,
    b2b::BroadcastRefT &value)
{
    if (!node.is<json::array>())
        return false;

    bool ok = true;

    ok &= node[1] >> value.Name;
    ok &= node[2] >> value.Id;

    return ok;
}

bool data::serializer<json::node, b2b::VariableRefT>::from_data(
    const json::node &node,
    b2b::VariableRefT &value)
{
    if (!node.is<json::array>())
        return false;

    if (unsigned type; node[0] >> type)
        value.IsList = type == 13;
    else
        return false;

    bool ok = true;

    ok &= node[1] >> value.Name;
    ok &= node[2] >> value.Id;
    ok &= node[3] >> value.X;
    ok &= node[4] >> value.Y;

    return ok;
}

bool data::serializer<json::node, b2b::BlockT>::from_data(
    const json::node &node,
    b2b::BlockT &value)
{
    if (!node.is<json::object>())
        return false;

    bool ok = true;

    ok &= node["opcode"] >> value.Opcode;
    ok &= node["next"] >> value.Next;
    ok &= node["parent"] >> value.Parent;
    ok &= node["inputs"] >> value.Inputs;
    ok &= node["fields"] >> value.Fields;
    ok &= node["shadow"] >> value.Shadow;
    ok &= node["topLevel"] >> value.TopLevel;
    ok &= node["x"] >> value.X;
    ok &= node["y"] >> value.Y;
    ok &= node["comment"] >> value.Comment;
    ok &= node["mutation"] >> value.Mutation;

    return ok;
}

bool data::serializer<json::node, b2b::FieldT>::from_data(
    const json::node &node,
    b2b::FieldT &value)
{
    if (!node.is<json::array>())
        return false;

    bool ok = true;

    ok &= node[0] >> value.Value;
    ok &= node[1] >> value.Id;

    return ok;
}

bool data::serializer<json::node, b2b::ValuePtr>::from_data(
    const json::node &node,
    b2b::ValuePtr &value)
{
    if (node.is<json::integer>() || node.is<json::floating_point>())
    {
        auto val = std::make_unique<b2b::NumberT>();
        const auto ok = node >> *val;
        value = std::move(val);
        return ok;
    }

    if (node.is<json::string>())
    {
        auto val = std::make_unique<b2b::StringT>();
        const auto ok = node >> *val;
        value = std::move(val);
        return ok;
    }

    if (node.is<json::array>())
    {
        auto val = std::make_unique<b2b::ArrayT>();
        const auto ok = node >> *val;
        value = std::move(val);
        return ok;
    }

    return false;
}

bool data::serializer<json::node, b2b::NumberT>::from_data(
    const json::node &node,
    b2b::NumberT &value)
{
    return node >> value.Value;
}

bool data::serializer<json::node, b2b::StringT>::from_data(
    const json::node &node,
    b2b::StringT &value)
{
    return node >> value.Value;
}

bool data::serializer<json::node, b2b::ArrayT>::from_data(
    const json::node &node,
    b2b::ArrayT &value)
{
    return node >> value.Values;
}
