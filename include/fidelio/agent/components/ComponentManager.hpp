#pragma once

#include "fidelio/agent/app/AgentConfig.hpp"
#include "fidelio/agent/integrity/IntegrityChecker.hpp"
#include "fidelio/agent/platform/ProcessSupervisor.hpp"
#include "fidelio/agent/state/StateManager.hpp"

#include <vector>

namespace fidelio::agent {

class ComponentManager {
public:
    ComponentManager(
        std::vector<ComponentConfig> components,
        IntegrityChecker& integrityChecker,
        ProcessSupervisor& processSupervisor,
        StateManager& stateManager);

    bool verifyInstalledComponents();
    void startRuntimeComponents();
    void stopRuntimeComponents();

private:
    std::vector<ComponentConfig> components_;
    IntegrityChecker& integrityChecker_;
    ProcessSupervisor& processSupervisor_;
    StateManager& stateManager_;
};

} // namespace fidelio::agent
