#include "fidelio/agent/platform/ProcessSupervisor.hpp"
#include "fidelio/agent/logging/Logger.hpp"

#include <filesystem>

namespace fidelio::agent {

ProcessStartResult ProcessSupervisor::startProcess(const std::string& name, const std::filesystem::path& executable) {
    if (!std::filesystem::exists(executable)) {
        return ProcessStartResult{
            .ok = false,
            .status = ProcessStatus::Failed,
            .message = "executable is missing: " + executable.string(),
        };
    }

    Logger::info("Process start requested for " + name + ": " + executable.string());
    return ProcessStartResult{
        .ok = true,
        .status = ProcessStatus::Running,
        .message = "start requested",
    };
}

bool ProcessSupervisor::stopProcess(const std::string& name) {
    Logger::info("Process stop requested for " + name);
    return true;
}

} // namespace fidelio::agent
