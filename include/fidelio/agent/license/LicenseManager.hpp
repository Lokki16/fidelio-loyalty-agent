#pragma once

#include <filesystem>
#include <string>

namespace fidelio::agent
{
    struct LicenseStatus
    {
        bool valid{false};
        std::string reason{"not checked"};
    };

    class LicenseManager
    {
    public:
        explicit LicenseManager(std::filesystem::path licensePath);

        LicenseStatus validate() const;

    private:
        std::filesystem::path licensePath_;
    };
}
