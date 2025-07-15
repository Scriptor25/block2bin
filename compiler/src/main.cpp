#include <iostream>
#include <vector>
#include <b2b/project.hpp>
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

    b2b::ProjectT project;
    std::map<std::string, std::vector<char>> blobs;

    for (const b2b::Zip zip("example.sb3"); const auto entry : zip)
    {
        const auto stat = entry.Stat();
        const auto file = entry.Open();

        std::vector<char> blob(stat.size + 1);
        file.Read(blob.data(), blob.size());

        std::cout << stat.name << " (" << stat.size << " B)" << std::endl;

        if (std::string_view(stat.name).ends_with(".json"))
        {
            project = nlohmann::json::parse(blob);
            continue;
        }

        blobs.emplace(stat.name, std::move(blob));
    }

    (void) project;
    (void) blobs;

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

        std::map<std::string, b2b::BlockT *> entry_points;
        for (const auto &[id, ref] : target->Blocks)
            if (auto block = dynamic_cast<b2b::BlockT *>(ref.get()); block && b2b::IsEntryPoint(block->Opcode))
                entry_points.emplace(id, block);

        for (auto [id, block] : entry_points)
            std::cout << id << " (" << block->Opcode << ")" << std::endl;
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
