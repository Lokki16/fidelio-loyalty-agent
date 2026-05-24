cmake_minimum_required(VERSION 3.24)

project(FidelioLoyaltyAgent
    VERSION 0.1.0
    DESCRIPTION "Fidelio Loyalty runtime agent"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(FIDELIO_AGENT_BUILD_TESTS "Build Fidelio Loyalty Agent tests" ON)

add_library(fidelio_agent_core
    src/app/AgentApp.cpp
    src/app/AgentConfig.cpp
    src/components/ComponentManager.cpp
    src/integrity/IntegrityChecker.cpp
    src/license/LicenseManager.cpp
    src/logging/Logger.cpp
    src/platform/ProcessSupervisor.cpp
    src/platform/WindowsService.cpp
    src/state/StateManager.cpp
    src/update/UpdateManager.cpp
)

target_include_directories(fidelio_agent_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

if (WIN32)
    target_compile_definitions(fidelio_agent_core PUBLIC NOMINMAX WIN32_LEAN_AND_MEAN)
endif()

add_executable(fidelio-loyalty-agent
    src/main.cpp
)

target_link_libraries(fidelio-loyalty-agent PRIVATE fidelio_agent_core)

include(CTest)
if (FIDELIO_AGENT_BUILD_TESTS AND BUILD_TESTING)
    add_executable(fidelio-agent-state-smoke-test
        tests/state_manager_smoke.cpp
    )
    target_link_libraries(fidelio-agent-state-smoke-test PRIVATE fidelio_agent_core)
    add_test(NAME fidelio-agent-state-smoke-test COMMAND fidelio-agent-state-smoke-test)
endif()
