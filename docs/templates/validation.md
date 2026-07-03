# Validation Template (Checklist)

## Purpose
Provide a concise checklist to verify that a milestone meets all quality gates before it is considered validated and ready for release.

## When to Use
After implementation work is complete and before the **Validation Review** gate in `WORKFLOW.md`.

## Intended Audience
Test engineers, contributors, and reviewers performing the final validation.

## Checklist
- [ ] **Architecture Review** – Confirm that the architecture documented in `architecture.md` was followed.
- [ ] **Compilation** – Project builds cleanly with PlatformIO, no errors.
- [ ] **Warnings** – No new compiler warnings; existing warnings are documented.
- [ ] **Documentation** – All code changes are reflected in relevant markdown files; `implementation_report.md` is complete.
- [ ] **Tests** – Unit and integration tests run successfully; coverage meets the milestone target.
- [ ] **Performance Metrics** – RAM, Flash, and power usage are recorded and within acceptable limits.
- [ ] **Final Decision** – Reviewer signs off that the milestone is ready to be closed or released.

## Relationships
- References `implementation_report.md` for concrete work details.
- Tied to the **Validation** gate in `WORKFLOW.md`.
- Follows the living‑documentation principle of `CONSTITUTION.md`; updates are appended.

---
*This file is a living document; updates should be appended, never overwritten.*
