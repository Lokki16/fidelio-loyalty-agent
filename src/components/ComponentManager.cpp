#include "fidelio/agent/components/ComponentManager.hpp"
#include "fidelio/agent/logging/Logger.hpp"

#include <filesystem>

namespace fidelio::agent
{
    ComponentManager::ComponentManager(
        std::vector<ComponentConfig> components,
        IntegrityChecker &integrityChecker,
        ProcessSupervisor &processSupervisor,
        StateManager &stateManager)
        : components_(std::move(components)),
          integrityChecker_(integrityChecker),
          processSupervisor_(processSupervisor),
          stateManager_(stateManager) {}

    bool ComponentManager::verifyInstalledComponents()
    {
        bool ok = true;

        for (const ComponentConfig &component : components_)
        {
            if (component.executable.empty())
            {
                stateManager_.updateComponentStatus(component.name, ComponentRuntimeStatus::Verified);
                continue;
            }

            const IntegrityResult result = integrityChecker_.verifyFile(component.executable, std::nullopt);
            if (!result.ok)
            {
                ok = false;
                Logger::warn(component.name + " verification failed: " + result.reason);
                stateManager_.updateComponentStatus(component.name, ComponentRuntimeStatus::Failed);
                continue;
            }

            stateManager_.updateComponentStatus(component.name, ComponentRuntimeStatus::Verified);
        }

        return ok;
    }

    void ComponentManager::startRuntimeComponents()
    {
        for (const ComponentConfig &component : components_)
        {
            if (component.executable.empty())
            {
                continue;
            }

            const ProcessStartResult result = processSupervisor_.startProcess(component.name, component.executable);
            stateManager_.updateComponentStatus(
                component.name,
                result.ok ? ComponentRuntimeStatus::Running : ComponentRuntimeStatus::Failed);
        }
    }

    void ComponentManager::stopRuntimeComponents()
    {
        for (const ComponentConfig &component : components_)
        {
            if (processSupervisor_.stopProcess(component.name))
            {
                stateManager_.updateComponentStatus(component.name, ComponentRuntimeStatus::Stopped);
            }
        }
    }
}
