#include "fidelio/agent/update/UpdateManager.hpp"

#include <utility>

namespace fidelio::agent {

UpdateManager::UpdateManager(std::string manifestUrl, StateManager& stateManager)
    : manifestUrl_(std::move(manifestUrl)),
      stateManager_(stateManager) {}

UpdateCheckResult UpdateManager::checkForUpdates() {
    AgentState state = stateManager_.load();
    state.lastUpdateCheckAt = "requested";
    stateManager_.save(state);

    if (manifestUrl_.empty()) {
        return UpdateCheckResult{
            .ok = false,
            .updateAvailable = false,
            .message = "update manifest url is not configured",
        };
    }

    return UpdateCheckResult{
        .ok = true,
        .updateAvailable = false,
        .message = "update manifest configured: " + manifestUrl_,
    };
}

} // namespace fidelio::agent
