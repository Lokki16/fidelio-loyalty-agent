#include "fidelio/agent/license/LicenseManager.hpp"

#include <filesystem>

namespace fidelio::agent
{
    LicenseManager::LicenseManager(std::filesystem::path licensePath)
        : licensePath_(std::move(licensePath)) {}

    LicenseStatus LicenseManager::validate() const
    {
        if (!std::filesystem::exists(licensePath_))
        {
            return LicenseStatus{.valid = false, .reason = "license file is missing"};
        }

        if (std::filesystem::file_size(licensePath_) == 0)
        {
            return LicenseStatus{.valid = false, .reason = "license file is empty"};
        }

        return LicenseStatus{.valid = true, .reason = "license file exists"};
    }
}
