#pragma once

#include "fidelio/agent/state/StateManager.hpp"

#include <string>

namespace fidelio::agent {

struct UpdateCheckResult {
    bool ok{false};
    bool updateAvailable{false};
    std::string message;
};

class UpdateManager {
public:
    UpdateManager(std::string manifestUrl, StateManager& stateManager);

    UpdateCheckResult checkForUpdates();

private:
    std::string manifestUrl_;
    StateManager& stateManager_;
};

} // namespace fidelio::agent
