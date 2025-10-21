#include <iostream>
#include <vector>
#include <b2b/common.hpp>
#include <b2b/project.hpp>
#include <b2b/tree.hpp>
#include <b2b/zip.hpp>

static void parse_statement_node(
    std::vector<b2b::StatementNodePtr> &nodes,
    const b2b::TargetPtr &target,
    const b2b::BlockT &block)
{
    std::cerr << "TODO: parse statement node" << std::endl;
}

static void parse_procedure_node(
    std::vector<b2b::ParentNodePtr> &nodes,
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
            parse_statement_node(node->Statements, target, *next);
        }
    }

    nodes.emplace_back(std::move(node));
}

static void parse_constructor_node(
    std::vector<b2b::ParentNodePtr> &nodes,
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
            parse_statement_node(node->Statements, target, *next);
        }
    }

    nodes.emplace_back(std::move(node));
}

static void parse_listener_node(
    std::vector<b2b::ParentNodePtr> &nodes,
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
            parse_statement_node(node->Statements, target, *next);
        }
    }

    nodes.emplace_back(std::move(node));
}

static void parse_parent_node(
    std::vector<b2b::ParentNodePtr> &nodes,
    const b2b::TargetPtr &target,
    const b2b::BlockT &block)
{
    switch (block.Opcode)
    {
    case b2b::event_whenflagclicked:
        return parse_listener_node(nodes, target, block, "event_whenflagclicked");
    case b2b::event_whenkeypressed:
        return parse_listener_node(nodes, target, block, "event_whenkeypressed");
    case b2b::event_whenthisspriteclicked:
        return parse_listener_node(nodes, target, block, "event_whenthisspriteclicked");
    case b2b::event_whenstageclicked:
        return parse_listener_node(nodes, target, block, "event_whenstageclicked");
    case b2b::event_whenbackdropswitchesto:
        return parse_listener_node(nodes, target, block, "event_whenbackdropswitchesto");
    case b2b::event_whengreaterthan:
        return parse_listener_node(nodes, target, block, "event_whengreaterthan");
    case b2b::event_whenbroadcastreceived:
        return parse_listener_node(nodes, target, block, "event_whenbroadcastreceived");
    case b2b::event_whentouchingobject:
        return parse_listener_node(nodes, target, block, "event_whentouchingobject");

    case b2b::control_start_as_clone:
        return parse_constructor_node(nodes, target, block);

    case b2b::procedures_definition:
        return parse_procedure_node(nodes, target, block);

    case b2b::videoSensing_whenMotionGreaterThan:
        return parse_listener_node(nodes, target, block, "videoSensing_whenMotionGreaterThan");

    case b2b::makeymakey_whenMakeyKeyPressed:
        return parse_listener_node(nodes, target, block, "makeymakey_whenMakeyKeyPressed");
    case b2b::makeymakey_whenCodePressed:
        return parse_listener_node(nodes, target, block, "makeymakey_whenCodePressed");

    case b2b::microbit_whenButtonPressed:
        return parse_listener_node(nodes, target, block, "microbit_whenButtonPressed");
    case b2b::microbit_whenGesture:
        return parse_listener_node(nodes, target, block, "microbit_whenGesture");
    case b2b::microbit_whenTilted:
        return parse_listener_node(nodes, target, block, "microbit_whenTilted");
    case b2b::microbit_whenPinConnected:
        return parse_listener_node(nodes, target, block, "microbit_whenPinConnected");

    case b2b::ev3_whenButtonPressed:
        return parse_listener_node(nodes, target, block, "ev3_whenButtonPressed");
    case b2b::ev3_whenDistanceLessThan:
        return parse_listener_node(nodes, target, block, "ev3_whenDistanceLessThan");
    case b2b::ev3_whenBrightnessLessThan:
        return parse_listener_node(nodes, target, block, "ev3_whenBrightnessLessThan");

    case b2b::boost_whenColor:
        return parse_listener_node(nodes, target, block, "boost_whenColor");
    case b2b::boost_whenTilted:
        return parse_listener_node(nodes, target, block, "boost_whenTilted");

    case b2b::wedo2_whenDistance:
        return parse_listener_node(nodes, target, block, "wedo2_whenDistance");
    case b2b::wedo2_whenTilted:
        return parse_listener_node(nodes, target, block, "wedo2_whenTilted");

    case b2b::gdxfor_whenGesture:
        return parse_listener_node(nodes, target, block, "gdxfor_whenGesture");
    case b2b::gdxfor_whenForcePushedOrPulled:
        return parse_listener_node(nodes, target, block, "gdxfor_whenForcePushedOrPulled");
    case b2b::gdxfor_whenTilted:
        return parse_listener_node(nodes, target, block, "gdxfor_whenTilted");

    default:
        std::cerr << "invalid parent node block opcode '" << block.Opcode << "'" << std::endl;
        break;
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
        std::cerr << "in target '" << target->Name << "':" << std::endl;

        std::cerr << " - costumes:" << std::endl;
        for (const auto &costume : target->Costumes)
        {
            const auto &blob = blobs.at(costume->MD5Ext);
            (void) blob;

            std::cerr << "    + '" << costume->Name << "' (" << costume->MD5Ext << ")" << std::endl;
        }

        std::cerr << " - sounds:" << std::endl;
        for (const auto &sound : target->Sounds)
        {
            const auto &blob = blobs.at(sound->MD5Ext);
            (void) blob;

            std::cerr << "    + '" << sound->Name << "' (" << sound->MD5Ext << ")" << std::endl;
        }

        std::map<std::string, b2b::BlockT *> entry_blocks;
        for (const auto &[id, ref] : target->Blocks)
        {
            if (auto block = b2b::cast<b2b::BlockT>(ref); block && b2b::IsEntryPoint(block->Opcode))
            {
                entry_blocks.emplace(id, block);
            }
        }

        std::vector<b2b::ParentNodePtr> entry_nodes;

        std::cerr << " - entry points:" << std::endl;
        for (const auto &[id, block] : entry_blocks)
        {
            std::cerr << "    + " << id << " (" << block->Opcode << ")" << std::endl;

            parse_parent_node(entry_nodes, target, *block);
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
