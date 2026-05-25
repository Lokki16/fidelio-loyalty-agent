#include "fidelio/agent/app/AgentApp.hpp"
#include "fidelio/agent/logging/Logger.hpp"

#include <iostream>

namespace fidelio::agent {

AgentApp::AgentApp(AgentConfig config)
    : config_(std::move(config)),
      stateManager_(config_.statePath),
      licenseManager_(config_.licensePath),
      componentManager_(config_.components, integrityChecker_, processSupervisor_, stateManager_),
      updateManager_(config_.updateManifestUrl, stateManager_) {}

int AgentApp::run(const std::vector<std::string>& args) {
    const std::string command = args.size() > 1 ? args[1] : "help";

    if (command == "status") {
        return showStatus();
    }
    if (command == "verify") {
        return verify();
    }
    if (command == "check-updates") {
        return checkUpdates();
    }
    if (command == "run") {
        return runForeground();
    }
    if (command == "install-service") {
        return installService();
    }
    if (command == "uninstall-service") {
        return uninstallService();
    }

    return printHelp();
}

int AgentApp::showStatus() {
    const AgentState state = stateManager_.load();
    std::cout << config_.productName << '\n';
    std::cout << "Version: " << state.installedVersion << '\n';
    std::cout << "Client: " << state.activeClient << '\n';
    std::cout << "License: " << state.licenseStatus << '\n';
    std::cout << "State: " << stateManager_.statePath().string() << '\n';

    for (const auto& [name, component] : state.components) {
        std::cout << "- " << name << ": " << toString(component.status) << '\n';
    }

    return 0;
}

int AgentApp::verify() {
    const LicenseStatus license = licenseManager_.validate();
    stateManager_.updateLicenseStatus(license.valid ? "valid" : "invalid: " + license.reason);

    const bool componentsOk = componentManager_.verifyInstalledComponents();
    if (!license.valid) {
        Logger::warn("License check did not pass: " + license.reason);
    }

    return license.valid && componentsOk ? 0 : 2;
}

int AgentApp::checkUpdates() {
    const UpdateCheckResult result = updateManager_.checkForUpdates();
    if (!result.ok) {
        Logger::warn(result.message);
        return 2;
    }

    Logger::info(result.message);
    return result.updateAvailable ? 10 : 0;
}

int AgentApp::runForeground() {
    const int verifyCode = verify();
    if (verifyCode != 0) {
        Logger::warn("Runtime startup blocked by verification result");
        return verifyCode;
    }

    componentManager_.startRuntimeComponents();
    Logger::info("Runtime components start requested");
    return 0;
}

int AgentApp::installService() {
    return serviceController_.install("FidelioLoyaltyAgent") ? 0 : 2;
}

int AgentApp::uninstallService() {
    return serviceController_.uninstall("FidelioLoyaltyAgent") ? 0 : 2;
}

int AgentApp::printHelp() {
    std::cout << "Fidelio Loyalty Agent\n\n";
    std::cout << "Commands:\n";
    std::cout << "  status            Show local runtime state\n";
    std::cout << "  verify            Validate license and component files\n";
    std::cout << "  check-updates     Check configured update manifest\n";
    std::cout << "  run               Verify and start runtime components\n";
    std::cout << "  install-service   Register local service\n";
    std::cout << "  uninstall-service Remove local service\n";
    return 0;
}

} // namespace fidelio::agent
