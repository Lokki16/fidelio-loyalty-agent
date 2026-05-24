#pragma once

#include "fidelio/agent/app/AgentConfig.hpp"
#include "fidelio/agent/components/ComponentManager.hpp"
#include "fidelio/agent/integrity/IntegrityChecker.hpp"
#include "fidelio/agent/license/LicenseManager.hpp"
#include "fidelio/agent/platform/ProcessSupervisor.hpp"
#include "fidelio/agent/platform/ServiceController.hpp"
#include "fidelio/agent/state/StateManager.hpp"
#include "fidelio/agent/update/UpdateManager.hpp"

#include <string>
#include <vector>

namespace fidelio::agent {

class AgentApp {
public:
    explicit AgentApp(AgentConfig config);

    int run(const std::vector<std::string>& args);

private:
    int showStatus();
    int verify();
    int checkUpdates();
    int runForeground();
    int installService();
    int uninstallService();
    int printHelp();

    AgentConfig config_;
    StateManager stateManager_;
    IntegrityChecker integrityChecker_;
    LicenseManager licenseManager_;
    ProcessSupervisor processSupervisor_;
    ComponentManager componentManager_;
    UpdateManager updateManager_;
    ServiceController serviceController_;
};

} // namespace fidelio::agent
