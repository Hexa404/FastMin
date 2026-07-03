# Developer Setup Guide

## 1. Purpose
The purpose of this guide is to provide a clear, step‑by‑step onboarding process so that a new developer can set up a complete FastMin development environment from scratch with minimal friction.

> **Why it exists:** Reduces the time and effort required for a newcomer to become productive.
> **Who benefits:** New contributors, interns, and anyone unfamiliar with the project’s toolchain.

## 2. Target Audience
- New developers joining the FastMin project.
- Experienced contributors who need a refresher on the current setup.
- Hobbyists and students exploring the platform.

> **Why it exists:** Defines the intended readers to tailor the level of detail.
> **Who benefits:** All readers, ensuring the guide matches their experience.

## 3. Relationship with Core Documents
- **CONSTITUTION.md** – Reinforces the principles of open collaboration, living documentation, and architecture‑first development.
- **WORKFLOW.md** – Shows how the setup feeds into the overall engineering workflow (e.g., after environment setup you can start the feature branch flow).
- **CONTRIBUTING.md** – Complements contribution instructions by ensuring the environment is ready before following contribution steps.

> **Why it exists:** Provides context and avoids duplication.
> **Who benefits:** Readers can navigate to the relevant deeper documentation as needed.

## 4. Supported Platforms
- **Ubuntu** – Primary supported platform; all instructions are written for Ubuntu LTS.
- **Other operating systems** – Community‑supported; users may adapt the steps for macOS, Windows (WSL), or other Linux distros.

> **Why it exists:** Sets expectations and clarifies where the guide is authoritative.
> **Who benefits:** Users know which platform will work out‑of‑the‑box.

## 5. Repository Overview
```
FastMin/
├─ docs/          # Documentation (this guide, architecture, etc.)
├─ firmware/      # Embedded source code, PlatformIO project
├─ hardware/      # Hardware schematics, BOMs
├─ assets/        # Images, diagrams, UI assets
├─ scripts/       # Helper scripts for build, flashing, CI
└─ experiments/   # Prototype and experimental code
```

> **Why it exists:** Gives a mental map of where code and resources reside.
> **Who benefits:** New developers can locate files quickly.

## 6. Repository Bootstrap
1. **Clone the repository** – `git clone https://github.com/yourorg/FastMin.git`
2. **Enter the project root** – `cd FastMin`
3. **Run the setup script** (future) – this will install required tools and configure the environment.
4. **Open the VS Code workspace** – `code .`
5. **Verify the build** – run the PlatformIO build task.

> **Why it exists:** Provides a concrete onboarding sequence.
> **Who benefits:** Anyone performing the initial setup.

## 7. Development Tools
**Required**
- Git – source control.
- PlatformIO – build system for ESP32 firmware.
- VS Code – recommended IDE.

**Recommended**
- `tree` – visualise directory structures.
- `ripgrep` – fast code searching.
- `clang-format` – enforce coding style.

**Optional**
- `clang-tidy` – static analysis.
- Docker – containerised builds and CI.

> **Why it exists:** Specifies tools needed and nice‑to‑have utilities.
> **Who benefits:** Developers can set up the exact toolchain.

## 8. VS Code Workspace
Open the repository root (`FastMin`) in VS Code rather than only the `firmware` folder. This ensures all documentation, scripts, and configuration files are indexed and available.

> **Why it exists:** Improves navigation and enables workspace settings.
> **Who benefits:** All developers using VS Code.

## 9. Build Workflow
1. **Clone** the repository.
2. **Build** – use PlatformIO (`pio run`).
3. **Upload** – flash the firmware to the ESP32 (`pio run -t upload`).
4. **Serial Monitor** – view runtime logs (`pio device monitor`).

> **Why it exists:** Outlines the end‑to‑end development cycle.
> **Who benefits:** New developers learning how to compile and run the code.

## 10. Git Workflow
1. **Feature Branch** – `git checkout -b feature/<name>`
2. **Implementation** – develop code.
3. **Validation** – run tests, ensure build passes.
4. **Commit** – write a conventional commit message.
5. **Push** – `git push origin feature/<name>` and open a PR.

> **Why it exists:** Aligns with the project’s contribution process.
> **Who benefits:** Contributors and reviewers.

## 11. Troubleshooting Philosophy
When encountering issues, follow a systematic approach:
- Reproduce the problem consistently.
- Isolate the step (clone, build, upload, monitor).
- Check logs and error messages.
- Search the documentation and existing issues.
- Ask the community with a minimal reproducible example.

> **Why it exists:** Provides a reusable mindset for problem solving.
> **Who benefits:** All developers facing setup or build problems.

## 12. Future Evolution
The guide will be maintained as a living document. As the toolchain evolves (e.g., new PlatformIO versions, CI integration) or additional platforms are officially supported, updates will be appended without removing existing content.

> **Why it exists:** Ensures the guide remains accurate over time.
> **Who benefits:** The whole project community.

---
*This file is a living document; updates should be appended, never overwritten.*
