#include "fidelio/agent/state/StateManager.hpp"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fidelio::agent {

namespace {

std::string nowIsoLike() {
    const auto now = std::chrono::system_clock::now();
    const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    return std::to_string(seconds);
}

} // namespace

StateManager::StateManager(std::filesystem::path statePath)
    : statePath_(std::move(statePath)) {
    state_.components.emplace("backend", ComponentState{.name = "backend"});
    state_.components.emplace("telegram-bot", ComponentState{.name = "telegram-bot"});
    state_.components.emplace("admin-web", ComponentState{.name = "admin-web"});
}

AgentState StateManager::load() {
    if (!std::filesystem::exists(statePath_)) {
        save(state_);
    }

    return state_;
}

void StateManager::save(const AgentState& state) {
    state_ = state;
    std::filesystem::create_directories(statePath_.parent_path());

    std::ofstream output(statePath_, std::ios::trunc);
    output << "{\n";
    output << "  \"installedVersion\": \"" << state_.installedVersion << "\",\n";
    output << "  \"targetVersion\": \"" << state_.targetVersion << "\",\n";
    output << "  \"activeClient\": \"" << state_.activeClient << "\",\n";
    output << "  \"licenseStatus\": \"" << state_.licenseStatus << "\",\n";
    output << "  \"lastIntegrityCheckAt\": \"" << state_.lastIntegrityCheckAt << "\",\n";
    output << "  \"lastUpdateCheckAt\": \"" << state_.lastUpdateCheckAt << "\",\n";
    output << "  \"components\": {\n";

    bool first = true;
    for (const auto& [name, component] : state_.components) {
        if (!first) {
            output << ",\n";
        }
        first = false;
        output << "    \"" << name << "\": {";
        output << "\"version\": \"" << component.version << "\", ";
        output << "\"checksum\": \"" << component.checksum << "\", ";
        output << "\"status\": \"" << toString(component.status) << "\"";
        output << "}";
    }

    output << "\n  }\n";
    output << "}\n";
}

void StateManager::updateComponentStatus(const std::string& name, ComponentRuntimeStatus status) {
    AgentState state = load();
    auto& component = state.components[name];
    component.name = name;
    component.status = status;
    state.lastIntegrityCheckAt = nowIsoLike();
    save(state);
}

void StateManager::updateLicenseStatus(const std::string& status) {
    AgentState state = load();
    state.licenseStatus = status;
    save(state);
}

const std::filesystem::path& StateManager::statePath() const {
    return statePath_;
}

std::string toString(ComponentRuntimeStatus status) {
    switch (status) {
        case ComponentRuntimeStatus::Verified:
            return "verified";
        case ComponentRuntimeStatus::Running:
            return "running";
        case ComponentRuntimeStatus::Stopped:
            return "stopped";
        case ComponentRuntimeStatus::Failed:
            return "failed";
        case ComponentRuntimeStatus::Unknown:
        default:
            return "unknown";
    }
}

} // namespace fidelio::agent
