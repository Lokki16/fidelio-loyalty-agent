#include "fidelio/agent/platform/WindowsService.hpp"
#include "fidelio/agent/logging/Logger.hpp"

namespace fidelio::agent {

bool WindowsService::install(const std::string& serviceName) {
#ifdef _WIN32
    Logger::info("Windows service install requested: " + serviceName);
    return true;
#else
    Logger::warn("Windows service install is only available on Windows: " + serviceName);
    return false;
#endif
}

bool WindowsService::uninstall(const std::string& serviceName) {
#ifdef _WIN32
    Logger::info("Windows service uninstall requested: " + serviceName);
    return true;
#else
    Logger::warn("Windows service uninstall is only available on Windows: " + serviceName);
    return false;
#endif
}

} // namespace fidelio::agent
