#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace fidelio::agent
{
    struct ComponentConfig
    {
        std::string name;
        std::filesystem::path executable;
        std::string healthUrl;
    };

    struct AgentConfig
    {
        std::string productName{"Fidelio Loyalty"};
        std::string activeClient{"fidelio"};
        std::filesystem::path statePath{"data/agent-state.json"};
        std::filesystem::path licensePath{"license.json"};
        std::string updateManifestUrl;
        std::vector<ComponentConfig> components;
    };

    class AgentConfigLoader
    {
    public:
        AgentConfig loadDefault() const;
    };
}
