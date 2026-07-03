# FastMin – Engineering Workflow

## 1. Purpose
Define the official engineering lifecycle that all FastMin milestones must follow. It ensures consistency, traceability, and alignment with the principles in `CONSTITUTION.md`.

## 2. Relationship with `CONSTITUTION.md`
The workflow enforces the high‑level engineering principles (e.g., Open Collaboration, Living Documentation, Semantic Versioning) defined in the Constitution. Any deviation from the workflow must be justified in the Constitution.

## 3. Engineering Workflow
```
Architecture
   ↓
Architecture Review
   ↓
APPROVED?
   ↓
Implementation Plan
   ↓
Implementation Plan Review
   ↓
APPROVED?
   ↓
Implementation
   ↓
Validation
   ↓
APPROVED?
   ↓
Git Commit
   ↓
Git Push
   ↓
Milestone Closed
   ↓
Release (when applicable)
```

## 4. Decision Gates
At each **APPROVED?** checkpoint a designated **Reviewer** must sign‑off before proceeding. The gate ensures that the work complies with the Constitution and the milestone’s objectives.

## 5. Milestone Lifecycle
```
Idea
   ↓
Architecture
   ↓
Planning
   ↓
Implementation
   ↓
Validation
   ↓
Closed
```
Each stage maps to a corresponding phase in the Engineering Workflow.

## 6. Roles and Responsibilities
- **Product Owner** – defines the milestone goal and validates that the outcome meets the product vision.
- **Technical Lead** – ensures technical feasibility, oversees Architecture Review and Implementation Plan Review.
- **Contributor** – performs the Implementation and Validation work.
- **Reviewer** – provides independent approval at each decision gate.

## 7. Documentation Workflow
```
CONSTITUTION.md
   ↓
WORKFLOW.md
   ↓
Templates
   ↓
Implementation Documents (e.g., `S0.2.md`)
   ↓
Validation Documents (test reports, test logs)
```
All documents are living; they are appended, never overwritten.

## 8. Living Documents
Every artifact (Constitution, Workflow, implementation plans) is version‑controlled and updated by appending new sections. Historical information remains immutable.

## 9. Milestone Documents
Each milestone has its own implementation plan (`docs/implementation/<Milestone>.md`) and a corresponding validation report. They reference the Workflow for required phases.

## 10. Cleanup Milestones
Periodic cleanup milestones remove outdated code, deprecated configuration, and obsolete documentation. They follow the same workflow but skip the Release step.

## 11. Release Workflow
When a milestone reaches **Milestone Closed** and is deemed production‑ready, a release is cut:
1. Bump version according to Semantic Versioning.
2. Generate changelog.
3. Tag the release in Git.
4. Publish artifacts (binary, docs).

## 12. Retrospective
After each release, the team records:
- What worked well.
- Areas for improvement.
- New backlog items.
These are stored in the milestone’s retrospective section.

## 13. Backlog Management
Backlog items are collected, prioritized, and scheduled for future milestones. They are never implemented directly without entering the milestone lifecycle.

## 14. Future Evolution
The workflow is designed to accommodate new phases (e.g., Security Review, Performance Review) by inserting them at appropriate points without breaking existing documentation.

---
*This file is a living document; updates should be appended.*
