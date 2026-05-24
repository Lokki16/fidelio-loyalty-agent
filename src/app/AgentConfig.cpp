#include "fidelio/agent/app/AgentConfig.hpp"

namespace fidelio::agent {

AgentConfig AgentConfigLoader::loadDefault() const {
    AgentConfig config;
    config.updateManifestUrl = "https://example.com/fidelio-loyalty/manifest.json";
    config.components = {
        ComponentConfig{
            .name = "backend",
            .executable = "backend/Fidelio.Loyalty.Backend.exe",
            .healthUrl = "http://127.0.0.1:8000/health",
        },
        ComponentConfig{
            .name = "telegram-bot",
            .executable = "telegram-bot/Fidelio.Loyalty.TelegramBot.exe",
            .healthUrl = "",
        },
        ComponentConfig{
            .name = "admin-web",
            .executable = "",
            .healthUrl = "http://127.0.0.1:8000/",
        },
    };
    return config;
}

} // namespace fidelio::agent
