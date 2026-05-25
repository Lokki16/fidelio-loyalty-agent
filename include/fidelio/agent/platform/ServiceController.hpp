#pragma once

#include <string>

namespace fidelio::agent
{
    class ServiceController
    {
    public:
        bool install(const std::string &serviceName);
        bool uninstall(const std::string &serviceName);
    };
}
