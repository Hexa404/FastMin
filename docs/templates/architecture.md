# Architecture Template

## Purpose
Capture the high‑level design, constraints, diagrams, and key decisions *before* any code is written. This ensures an architecture‑first approach and provides a stable reference for all downstream work.

## When to Use
At the start of every milestone after the idea phase and before any implementation begins.

## Intended Audience
Architects, Technical Lead, Product Owner, and contributors who need to understand the overall system design.

## Typical Sections
- **Goal** – What the milestone aims to achieve.
- **Context Diagram** – Visual overview of the system and its environment.
- **Component Overview** – Description of major components and their responsibilities.
- **Interfaces & Connections** – Defined contracts between components (e.g., `ConnectionInfo` usage).
- **Non‑functional Requirements** – Performance, memory, power, security constraints.
- **Risks & Assumptions** – Potential issues and assumptions made.
- **Open Questions** – Points requiring clarification before implementation.

## Relationships
- Referenced by `implementation_plan.md` for concrete task derivation.
- Reviewed in the **Architecture Review** gate defined in `WORKFLOW.md`.
- Aligns with the principles in `CONSTITUTION.md` (architecture‑first, living documentation).

---
*This file is a living document; updates should be appended, never overwritten.*
