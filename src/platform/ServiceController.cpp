#include "fidelio/agent/platform/ServiceController.hpp"
#include "fidelio/agent/logging/Logger.hpp"

namespace fidelio::agent {

bool ServiceController::install(const std::string& serviceName) {
#ifdef _WIN32
    Logger::info("Windows service install requested: " + serviceName);
    return true;
#elif defined(__linux__)
    Logger::info("Linux service install requested: " + serviceName);
    return true;
#else
    Logger::warn("Service install is not implemented on this platform: " + serviceName);
    return false;
#endif
}

bool ServiceController::uninstall(const std::string& serviceName) {
#ifdef _WIN32
    Logger::info("Windows service uninstall requested: " + serviceName);
    return true;
#elif defined(__linux__)
    Logger::info("Linux service uninstall requested: " + serviceName);
    return true;
#else
    Logger::warn("Service uninstall is not implemented on this platform: " + serviceName);
    return false;
#endif
}

} // namespace fidelio::agent
