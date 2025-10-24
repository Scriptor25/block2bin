#include <fstream>
#include <iostream>
#include <vector>
#include <b2b/common.hpp>
#include <b2b/project.hpp>
#include <b2b/tree.hpp>
#include <b2b/zip.hpp>

static void parse_expression_node(
    std::vector<b2b::ExpressionNodePtr> &nodes,
    const b2b::ProjectT &project,
    const b2b::TargetPtr &target,
    const b2b::BlockRefPtr &block)
{
    std::cerr << "TODO: parse expression node " << block << std::endl;
}

static void parse_statement_node(
    std::vector<b2b::StatementNodePtr> &nodes,
    const b2b::ProjectT &project,
    const b2b::TargetPtr &target,
    const b2b::BlockT &block)
{
    // if (!block.Inputs.empty())
    // {
    //     std::cerr << block.Opcode << ".inputs:" << std::endl;
    //     for (auto &[key, value] : block.Inputs)
    //     {
    //         std::cerr << " " << key << " -> " << value << std::endl;
    //     }
    // }
    // if (!block.Fields.empty())
    // {
    //     std::cerr << block.Opcode << ".fields:" << std::endl;
    //     for (auto &[key, value] : block.Fields)
    //     {
    //         std::cerr << " " << key << " -> " << value.Id << "," << value.Value << std::endl;
    //     }
    // }

    std::vector<b2b::ExpressionNodePtr> inputs;
    std::vector<b2b::ExpressionNodePtr> fields;

    const auto opcode = block.Opcode;

    const auto input_count = b2b::GetInputCount(opcode);
    for (unsigned i = 0; i < input_count; ++i)
    {
        const auto input_name = b2b::GetInputName(opcode, i);
        auto &input = block.Inputs.at(input_name);
        parse_expression_node(inputs, project, target, input->Block);
    }

    const auto field_count = b2b::GetFieldCount(opcode);
    for (unsigned i = 0; i < field_count; ++i)
    {
        const auto field_name = b2b::GetFieldName(opcode, i);
        auto &field = block.Fields.at(field_name);
        // id -> pointer to block, list, variable, etc.
        // value -> raw value, only if no id
        std::cerr << "field " << field_name << ": id=\"" << field.Id << "\" value=" << field.Value << std::endl;
    }
}

static void parse_procedure_node(
    std::vector<b2b::ParentNodePtr> &nodes,
    const b2b::ProjectT &project,
    const b2b::TargetPtr &target,
    const b2b::BlockT &block)
{
    const auto &id_ref = *b2b::cast<b2b::IdRefT>(block.Inputs.at("custom_block")->Block);
    const auto &proc_block = b2b::cast<b2b::BlockT>(target->Blocks.at(id_ref.Id));
    const auto &prototype = *b2b::cast<b2b::ProcedurePrototypeT>(*proc_block->Mutation);

    auto node = std::make_unique<b2b::ProcedureNodeT>();
    node->Name = prototype.ProcCode;

    for (unsigned i = 0; i < prototype.ArgumentIds.size(); ++i)
    {
        node->Parameters.emplace_back(
            prototype.ArgumentNames.at(i),
            prototype.ArgumentDefaults.at(i));
    }

    for (auto next = &block; next && next->Next;)
    {
        auto &ref = target->Blocks.at(*next->Next);
        next = b2b::cast<b2b::BlockT>(ref);

        if (next)
        {
            parse_statement_node(node->Statements, project, target, *next);
        }
    }

    nodes.emplace_back(std::move(node));
}

static void parse_constructor_node(
    std::vector<b2b::ParentNodePtr> &nodes,
    const b2b::ProjectT &project,
    const b2b::TargetPtr &target,
    const b2b::BlockT &block)
{
    auto node = std::make_unique<b2b::ConstructorNodeT>();

    for (auto next = &block; next && next->Next;)
    {
        auto &ref = target->Blocks.at(*next->Next);
        next = b2b::cast<b2b::BlockT>(ref);

        if (next)
        {
            parse_statement_node(node->Statements, project, target, *next);
        }
    }

    nodes.emplace_back(std::move(node));
}

static void parse_listener_node(
    std::vector<b2b::ParentNodePtr> &nodes,
    const b2b::ProjectT &project,
    const b2b::TargetPtr &target,
    const b2b::BlockT &block,
    const std::string_view &event)
{
    auto node = std::make_unique<b2b::ListenerNodeT>();
    node->Event = event;

    for (auto next = &block; next && next->Next;)
    {
        auto &ref = target->Blocks.at(*next->Next);
        next = b2b::cast<b2b::BlockT>(ref);

        if (next)
        {
            parse_statement_node(node->Statements, project, target, *next);
        }
    }

    nodes.emplace_back(std::move(node));
}

static void parse_parent_node(
    std::vector<b2b::ParentNodePtr> &nodes,
    const b2b::ProjectT &project,
    const b2b::TargetPtr &target,
    const b2b::BlockT &block)
{
    const auto opcode = block.Opcode;
    if (!b2b::IsEntry(opcode))
    {
        std::cerr << "invalid parent node block opcode '" << opcode << "'" << std::endl;
        return;
    }

    switch (opcode)
    {
    case b2b::control_start_as_clone:
        return parse_constructor_node(nodes, project, target, block);
    case b2b::procedures_definition:
        return parse_procedure_node(nodes, project, target, block);
    default:
        return parse_listener_node(nodes, project, target, block, b2b::GetName(opcode));
    }
}

int main()
{
    // 1. extract source files and assets from project file
    // 2. build ast from source json structure
    // 3. compile assets to data blobs
    // 4. compile ast to ir, use assets as global constants
    // 5. write ir to file, or compile ir to object file, or run the ir using a jit runtime
    // --> single file executable with all code and assets combined

    // - how to display the game? --> maybe linked library with opengl and glfw
    // --> scratch runtime library!!!
    // --> whole scratch engine

    const b2b::Zip zip("example.sb3");
    if (!zip)
    {
        return 1;
    }

    std::ifstream blocks("blocks.json");
    if (!blocks)
    {
        return 1;
    }

    b2b::ReadDictionary(blocks);

    b2b::ProjectT project;
    std::map<std::string, std::vector<char>> blobs;

    for (const auto entry : zip)
    {
        const auto stat = entry.Stat();
        const auto file = entry.Open();

        std::vector<char> blob(stat.size + 1);
        file.Read(blob.data(), blob.size());

        std::cerr << stat.name << " (" << stat.size << " B)" << std::endl;

        if (std::string_view(stat.name).ends_with(".json"))
        {
            project = nlohmann::json::parse(blob);
            continue;
        }

        blobs.emplace(stat.name, std::move(blob));
    }

    for (const auto &target : project.Targets)
    {
        for (const auto &costume : target->Costumes)
        {
            const auto &blob = blobs.at(costume->MD5Ext);
            (void) blob;
        }

        for (const auto &sound : target->Sounds)
        {
            const auto &blob = blobs.at(sound->MD5Ext);
            (void) blob;
        }

        std::vector<b2b::ParentNodePtr> entry_nodes;
        for (const auto &ref : target->Blocks | std::views::values)
        {
            if (const auto block = b2b::cast<b2b::BlockT>(ref); block && b2b::IsEntry(block->Opcode))
            {
                parse_parent_node(entry_nodes, project, target, *block);
            }
        }
    }

    for (const auto &monitor : project.Monitors)
    {
        (void) monitor;
    }

    for (const auto &extension : project.Extensions)
    {
        (void) extension;
    }

    return 0;
}
