# Contributing Guide

## 1. Purpose
The purpose of this guide is to provide clear, step‑by‑step instructions for anyone who wants to contribute to FastMin. It lowers the entry barrier, ensures consistent quality, and aligns contributions with the project's engineering principles.

## 2. Who Should Read This Guide
- **New contributors** – developers, students, or hobbyists making their first pull request.
- **Experienced contributors** – maintainers and reviewers who need a reference for the contribution process.
- **External partners** – anyone submitting patches, bug reports, or documentation updates.

## 3. Relationship with `CONSTITUTION.md`
The guide reinforces the high‑level engineering principles defined in the Constitution (e.g., Open Collaboration, Living Documentation, Semantic Versioning). All contributions must respect those principles; any deviation must be justified and recorded.

## 4. Relationship with `WORKFLOW.md`
The contribution workflow mirrors the phases described in `WORKFLOW.md`. Each gate in the workflow (Architecture Review, Implementation Plan Review, Validation) has a corresponding action that contributors must perform, such as submitting a design document before implementation or obtaining reviewer approval before merging.

## 5. Repository Expectations
- The repository follows a **single‑maintainer** model with clear ownership of each module.
- All source files live under `firmware/src/` and documentation under `docs/`.
- CI runs automatically on every pull request to ensure the project builds cleanly.

## 6. Branch Naming Convention
Use the following prefixes for branch names:

- `feature/<name>` – new functionality or enhancements.
- `fix/<name>` – bug fixes.
- `docs/<name>` – documentation updates.
- `refactor/<name>` – structural code changes without new functionality.
- `test/<name>` – additions or changes to unit/integration tests.
- `chore/<name>` – housekeeping tasks (e.g., CI config, build scripts).

## 7. Coding Standards
- **Language** – Modern C++17.
- **Enums** – Use `enum class` for type safety.
- **constexpr** – Prefer `constexpr` for compile‑time constants.
- **Composition over inheritance** – Favor plain structs and composition.
- **Value semantics** – Pass objects by value when inexpensive; avoid owning raw pointers.
- **Dynamic allocation** – Prohibited unless absolutely necessary and documented.
- **Readability** – Write clear, self‑documenting code; avoid clever tricks.
- **Formatting** – Run `clang-format` with the project's style configuration before committing.

## 8. Documentation Standards
- Documentation is as important as source code.
- Every code change must be accompanied by an update to the relevant markdown file or inline comment.
- Follow the **living‑document** workflow: open → append → save. Never delete existing sections.
- Use `docs/implementation/<Milestone>.md` for implementation notes and `docs/CONSTITUTION.md` for high‑level principles.

## 9. Contribution Review
Contributions are reviewed through Pull Requests (PRs). While GitHub is the primary platform, the process is platform‑agnostic: any code‑hosting service that supports PR‑style reviews can be used.

## 10. Before Requesting Review
Checklist to run before assigning a reviewer:
- The implementation document (`docs/implementation/<Milestone>.md`) has been updated.
- The project compiles with **no new warnings**.
- All relevant documentation has been updated.
- The contribution respects the Constitution and Workflow.
- CI passes (build, lint, tests).

## 11. Reporting Bugs
When filing a bug, provide:
- **Description** – concise summary of the problem.
- **Steps to reproduce** – exact steps to trigger the bug.
- **Expected behavior** – what should happen.
- **Actual behavior** – what actually happens.
- Include environment details (ESP32 version, PlatformIO version, etc.).

## 12. Commit Message Convention
Follow **Conventional Commits**:
```
<type>(<scope>): <description>

[optional body]

Closes #<issue>
```
- Types: `feat`, `fix`, `docs`, `style`, `refactor`, `test`, `chore`.
- Example: `feat(connection): add I2C connection support`.

## 13. Future Evolution
This guide will evolve alongside the workflow. New sections (e.g., Security Review, Performance Guidelines) will be added as the project grows. All updates must follow the same append‑only policy.

---
*This file is a living document; updates should be appended, never overwritten.*
