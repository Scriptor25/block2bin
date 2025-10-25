#include <fstream>
#include <iostream>
#include <vector>
#include <b2b/common.hpp>
#include <b2b/project.hpp>
#include <b2b/tree.hpp>
#include <b2b/zip.hpp>

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

    const b2b::Zip zip("example2.sb3");
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
                entry_nodes.emplace_back(block->GenerateParent(project, target));
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
