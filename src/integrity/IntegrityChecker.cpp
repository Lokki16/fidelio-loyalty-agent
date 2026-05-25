#include "fidelio/agent/integrity/IntegrityChecker.hpp"

#include <fstream>
#include <iomanip>
#include <sstream>

namespace fidelio::agent
{
    IntegrityResult IntegrityChecker::verifyFile(
        const std::filesystem::path &path,
        const std::optional<std::string> &expectedChecksum) const
    {
        if (!std::filesystem::exists(path))
        {
            return IntegrityResult{.ok = false, .checksum = "", .reason = "file is missing: " + path.string()};
        }

        const std::string checksum = calculateChecksum(path);
        if (checksum.empty())
        {
            return IntegrityResult{.ok = false, .checksum = "", .reason = "checksum calculation failed"};
        }

        if (expectedChecksum.has_value() && checksum != expectedChecksum.value())
        {
            return IntegrityResult{.ok = false, .checksum = checksum, .reason = "checksum mismatch"};
        }

        return IntegrityResult{.ok = true, .checksum = checksum, .reason = "ok"};
    }

    std::string IntegrityChecker::calculateChecksum(const std::filesystem::path &path) const
    {
        std::ifstream input(path, std::ios::binary);
        if (!input)
        {
            return {};
        }

        std::uint64_t hash = 14695981039346656037ull;
        char buffer[4096]{};

        while (input.read(buffer, sizeof(buffer)) || input.gcount() > 0)
        {
            const std::streamsize count = input.gcount();
            for (std::streamsize index = 0; index < count; ++index)
            {
                hash ^= static_cast<unsigned char>(buffer[index]);
                hash *= 1099511628211ull;
            }
        }

        std::ostringstream output;
        output << std::hex << std::setw(16) << std::setfill('0') << hash;
        return output.str();
    }
}
