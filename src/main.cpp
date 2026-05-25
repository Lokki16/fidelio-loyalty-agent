#include "fidelio/agent/app/AgentApp.hpp"
#include "fidelio/agent/app/AgentConfig.hpp"

#include <string>
#include <vector>

int main(int argc, char **argv)
{
    fidelio::agent::AgentConfigLoader loader;
    fidelio::agent::AgentApp app(loader.loadDefault());

    std::vector<std::string> args;
    args.reserve(static_cast<std::size_t>(argc));
    for (int index = 0; index < argc; ++index)
    {
        args.emplace_back(argv[index]);
    }

    return app.run(args);
}
