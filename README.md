# Fidelio Loyalty Agent

Native runtime agent for Fidelio Loyalty deployments.

The agent is the local parent process for the installed product. It does not contain business logic from the API, Telegram bot, or admin web UI. Its job is to install, verify, start, stop, update, and recover the local runtime components.

## Responsibilities

- license validation before runtime startup;
- runtime state persistence;
- component integrity checks;
- backend and Telegram bot process supervision;
- update manifest checks;
- staged download/update flow;
- rollback boundary for failed updates;
- autostart/service integration on supported host platforms.

## Workspace Role

Fidelio Loyalty is split into independent projects:

- `fidelio-loyalty-backend` - C# API and admin static host;
- `fidelio-loyalty-admin-web` - React/Redux admin UI;
- `fidelio-loyalty-telegram-bot` - Python Telegram worker;
- `fidelio-loyalty-agent` - native runtime manager.

Shared product documentation should stay outside these repositories, either in a separate `fidelio-loyalty-docs` repository or in a workspace-level `docs/` folder while developing locally.

## Architecture

```text
include/fidelio/agent/
  app/             Application lifecycle and config
  components/      Backend, bot, and web component model
  integrity/       File checksum verification
  license/         License loading and validation boundary
  logging/         Small logging facade
  platform/        Process and service integration
  state/           Runtime state manager
  update/          Update manifest and update orchestration

src/
  app/
  components/
  integrity/
  license/
  logging/
  platform/
  state/
  update/
```

## State Manager

`StateManager` owns local runtime state:

- installed version;
- target version;
- active client profile;
- license status;
- component status;
- last integrity check;
- last update check.

The state file is intentionally local runtime data and must not be committed.

## Build

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
ctest --test-dir build --output-on-failure
```

Linux shell:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Preset-based flow for IDEs and CI:

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

## Basic Commands

```powershell
.\build\fidelio-loyalty-agent.exe status
.\build\fidelio-loyalty-agent.exe verify
.\build\fidelio-loyalty-agent.exe check-updates
.\build\fidelio-loyalty-agent.exe run
```

Service commands are intentionally stubbed until the installer policy is finalized:

```powershell
.\build\fidelio-loyalty-agent.exe install-service
.\build\fidelio-loyalty-agent.exe uninstall-service
```

## Runtime Layout

Target installed layout:

```text
C:\Program Files\Fidelio Loyalty\
  agent\
  backend\
  telegram-bot\
  data\
  logs\
  updates\
```

The backend should serve the built admin web. The Telegram bot should talk to the backend through API calls. The agent supervises both runtime processes.

## Cross-Platform Development

The agent must build and debug on Windows and Linux. OS-specific service
registration belongs behind `ServiceController`; the app layer should remain
platform-neutral.

VS Code task and launch files are committed under `.vscode/` and contain no
machine-specific paths.
