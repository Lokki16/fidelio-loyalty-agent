#include "fidelio/agent/logging/Logger.hpp"

#include <iostream>

namespace fidelio::agent {

void Logger::info(const std::string& message) {
    std::cout << "[info] " << message << '\n';
}

void Logger::warn(const std::string& message) {
    std::cerr << "[warn] " << message << '\n';
}

void Logger::error(const std::string& message) {
    std::cerr << "[error] " << message << '\n';
}

} // namespace fidelio::agent
