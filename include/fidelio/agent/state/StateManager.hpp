#pragma once

#include <filesystem>
#include <map>
#include <string>

namespace fidelio::agent {

enum class ComponentRuntimeStatus {
    Unknown,
    Verified,
    Running,
    Stopped,
    Failed
};

struct ComponentState {
    std::string name;
    std::string version{"0.0.0"};
    std::string checksum;
    ComponentRuntimeStatus status{ComponentRuntimeStatus::Unknown};
};

struct AgentState {
    std::string installedVersion{"0.1.0"};
    std::string targetVersion;
    std::string activeClient{"fidelio"};
    std::string licenseStatus{"unknown"};
    std::string lastIntegrityCheckAt;
    std::string lastUpdateCheckAt;
    std::map<std::string, ComponentState> components;
};

class StateManager {
public:
    explicit StateManager(std::filesystem::path statePath);

    AgentState load();
    void save(const AgentState& state);
    void updateComponentStatus(const std::string& name, ComponentRuntimeStatus status);
    void updateLicenseStatus(const std::string& status);
    const std::filesystem::path& statePath() const;

private:
    std::filesystem::path statePath_;
    AgentState state_;
};

std::string toString(ComponentRuntimeStatus status);

} // namespace fidelio::agent
