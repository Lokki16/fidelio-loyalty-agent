#pragma once

#include <filesystem>
#include <string>

namespace fidelio::agent
{
    enum class ProcessStatus
    {
        NotStarted,
        Running,
        Stopped,
        Failed
    };

    struct ProcessStartResult
    {
        bool ok{false};
        ProcessStatus status{ProcessStatus::NotStarted};
        std::string message;
    };

    class ProcessSupervisor
    {
    public:
        ProcessStartResult startProcess(const std::string &name, const std::filesystem::path &executable);
        bool stopProcess(const std::string &name);
    };
}
