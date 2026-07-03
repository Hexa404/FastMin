# Template System README

## Purpose
The template system provides a **standard starting point** for all FastMin documentation artefacts. It ensures consistency, reduces duplicated effort, and enforces the architecture‑first, living‑documentation philosophy.

## When to Use Each Template
| Template | When to Use |
|----------|-------------|
| `architecture.md` | At the start of a milestone, after the idea phase, to capture high‑level design. |
| `implementation_plan.md` | After architecture approval, before any code is written. |
| `implementation_report.md` | During the Implementation phase to record what was actually built. |
| `validation.md` | After implementation, to document testing, metrics and final decision. |
| `retrospective.md` | After a milestone is closed, to capture lessons learned. |
| `adr.md` | Whenever a significant architectural decision is made. |

## Short Description of Each Template
- **architecture.md** – High‑level design, constraints, diagrams, risks.
- **implementation_plan.md** – Detailed task breakdown, dependencies, verification plan.
- **implementation_report.md** – Concrete record of code changes, rationales, deviations.
- **validation.md** – Checklist of compilation, warnings, documentation, tests, and final go/no‑go.
- **retrospective.md** – What worked, what can improve, new backlog items.
- **adr.md** – Architecture Decision Record format.

## Relationship with Core Documents
- **CONSTITUTION.md** – Templates operationalise its principles (Open Collaboration, Living Documentation, Architecture‑first). Each template references the Constitution to remind authors of the guiding philosophy.
- **WORKFLOW.md** – The workflow gates map directly to templates (`architecture.md` → Architecture Review, `implementation_plan.md` → Implementation Plan Review, `validation.md` → Validation Review). Templates make the required artefacts easy to produce.

---
*This file is a living document; updates should be appended, never overwritten.*
