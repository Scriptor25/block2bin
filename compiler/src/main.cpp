#include <iostream>
#include <vector>
#include <b2b/zip.hpp>
#include <nlohmann/json.hpp>

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


    for (const b2b::Zip zip("example.sb3"); const auto entry : zip)
    {
        auto stat = entry.Stat();

        std::cout << stat.name << " (" << stat.size << " B)" << std::endl;

        if (std::string_view(stat.name).ends_with(".json"))
        {
            auto file = entry.Open();

            std::vector<char> buffer(stat.size + 1);
            file.Read(buffer.data(), buffer.size());

            auto json = nlohmann::json::parse(buffer);

            std::cout << std::setw(4) << json << std::endl;
        }
    }

    return 0;
}
