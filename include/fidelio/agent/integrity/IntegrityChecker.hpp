#pragma once

#include <filesystem>
#include <optional>
#include <string>

namespace fidelio::agent {

struct IntegrityResult {
    bool ok{false};
    std::string checksum;
    std::string reason;
};

class IntegrityChecker {
public:
    IntegrityResult verifyFile(const std::filesystem::path& path, const std::optional<std::string>& expectedChecksum) const;
    std::string calculateChecksum(const std::filesystem::path& path) const;
};

} // namespace fidelio::agent
