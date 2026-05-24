#include "fidelio/agent/state/StateManager.hpp"

#include <filesystem>
#include <iostream>

int main() {
    const auto statePath = std::filesystem::temp_directory_path() / "fidelio-agent-state-smoke.json";
    std::filesystem::remove(statePath);

    fidelio::agent::StateManager manager(statePath);
    manager.updateComponentStatus("backend", fidelio::agent::ComponentRuntimeStatus::Verified);
    const fidelio::agent::AgentState state = manager.load();

    const auto found = state.components.find("backend");
    if (found == state.components.end()) {
        std::cerr << "backend component missing\n";
        return 1;
    }

    if (found->second.status != fidelio::agent::ComponentRuntimeStatus::Verified) {
        std::cerr << "backend component status was not persisted in memory\n";
        return 1;
    }

    if (!std::filesystem::exists(statePath)) {
        std::cerr << "state file was not created\n";
        return 1;
    }

    std::filesystem::remove(statePath);
    return 0;
}
