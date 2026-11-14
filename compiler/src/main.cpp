#include <json/json.hxx>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <fstream>
#include <iostream>
#include <map>
#include <ranges>
#include <sstream>
#include <vector>

import b2b.zip;
import b2b.opcode;
import b2b.project;
import b2b.ir.builder;
import b2b.tree;
import b2b.common;

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
        return 1;

    std::ifstream blocks("blocks.json");
    if (!blocks)
        return 1;

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
            std::istringstream stream(std::string(blob.begin(), blob.end()));

            json::node project_node;
            stream >> project_node;

            if (!(project_node >> project))
                throw std::runtime_error("TODO");

            continue;
        }

        blobs.emplace(stat.name, std::move(blob));
    }

    llvm::LLVMContext llvm_context;
    llvm::Module llvm_module("game", llvm_context);

    b2b::ir::Builder builder(llvm_context, llvm_module);

    for (const auto &target : project.Targets)
    {
        b2b::TargetTypeT target_type;

        for (auto &[id, variable] : target->Variables)
        {
            auto initial_value = variable.Value->GenerateExpression();

            target_type.Fields.emplace_back(id, variable.Name, std::move(initial_value));
        }

        for (auto &[id, list] : target->Lists)
        {
            auto initial_value = std::make_unique<b2b::ConstantArrayNodeT>();
            for (auto &value : list.Values)
            {
                initial_value->Values.emplace_back(value->GenerateExpression());
            }

            target_type.Fields.emplace_back(id, list.Name, std::move(initial_value));
        }

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

        for (const auto &ref : target->Blocks | std::views::values)
        {
            if (const auto block = b2b::cast<b2b::BlockT>(ref); block && b2b::IsEntry(block->Opcode))
            {
                auto node = block->GenerateParent(project, target);
                (void) node;
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

    llvm_module.print(llvm::outs(), nullptr);

    return 0;
}
