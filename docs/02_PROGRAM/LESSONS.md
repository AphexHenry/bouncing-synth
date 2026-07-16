# LESSONS — Bounce (program lessons, L-09+)

```
doc_id:   LESSONS
layer:    program
audience: ALL
status:   ACTIVE
parent:   LESSONS_CORE
```

New program lessons begin at L-09. None yet.

L-09: A brief's halt-vs-record boundary must be total over its steps, and its BLOCKED triggers
must enumerate every workspace prerequisite — including version control itself. Any precondition
delegated to the Director must also appear as an agent-checkable failure mode, because the agent
is the only actor positioned to detect its violation at execution time. Origin: C-000-T1, where
the workspace lacked `.git` (Director setup step skipped); the brief exempted only steps 5–8 from
stop-on-surprise and omitted `.git` from its setup-incomplete trigger, so the agent could neither
block on the missing repository nor meet the P5 §5 branch/commit end-state (JRN-C000-6).

L-10: An OUT file must carry, inside itself, every piece of evidence its review needs — for
apply-only packets that means verbatim copies of every journal/register/log line applied plus a
digest (byte count and sha256) of every file written; "it can be checked in the repo" is not
review evidence because the PM has no repo access by design (P6 §2.2). Enforcement: every
packet's TASK section states an explicit OUT-REQUIREMENTS block, and an OUT missing any required
section is returned for repair, never accepted. Origin: OUT_2–OUT_4 lacked the P5 §5
journal-copies section and were accepted anyway; caught by the Director (a P6 §6.4 incident);
compounded by a parallel PM conversation independently drafting the same correction
(JRN-C000-9).

L-11: An acceptance criterion over workspace state must assert only conditions the packet's own
mechanics guarantee at execution time; any state contributed by the Director's dispatch steps or
inherited from prior cycles (e.g. untracked inbox/PACKET_*.md) is written into the criterion as
an explicitly tolerated pattern, never left as an implicit expectation. A brief's failure_modes
section may not offer "PM judges at review" as an escape from a binary criterion (P6 §4.1) —
the tolerance belongs in the criterion text itself. Origin: I-001-T1 criterion 5 demanded a
clean tree while dispatch mechanics leave packet files untracked and the branch inherited one
from the prior cycle, forcing AMEND + RETURN on otherwise sound work (JRN-I001-5). Second
occurrence of the workspace-state authoring class after L-09 → P6 §4 amendment proposed
(STATE open decision 2).

L-12: An OUT file cannot attest the hash of the commit that carries it: any BRANCH/COMMITS
line naming the OUT-carrying commit is stale-by-one by construction, and amending the commit
to "fix" the line only mints a new sibling hash. Therefore (i) OUT-carrying commits are never
amended to embed their own hash — the BRANCH/COMMITS paste is taken immediately before the
final OUT commit and ends with the literal terminator line "+ final OUT commit (hash not
self-listable)", and the Director verifies the final hash as the branch tip at merge; and
(ii) packet preconditions and review pins anchor on ancestor commits (e.g. the packet's apply
commit) or on content checks, never on an OUT-reported tip hash. Origin: PACKET 9's
precondition pinned OUT_8's self-listed tip f8f15fa0…, unattainable after the agent's
hash-correcting amend (true tip d421a09…), forcing BLOCKED OUT_9 (JRN-I001-7).

L-13: Workspace-cleanliness criteria assert only over the agent-writable surface — src/,
tests/, config/, data/, reports/, docs/, outbox/ — asserting no modified tracked entries
anywhere and no untracked entries within that surface beyond the files the task is required
to write. The Director courier surface (repository root and inbox/) is pasted verbatim for
the record and never asserted: the set of Director courier artifacts (packet files, docs
zips, OS metadata) is open, so tolerated-pattern enumeration cannot be made total — each
enumeration fix (L-11's inbox/PACKET_*.md) fails on the next artifact class (docs.zip,
OUT_10). Surface scoping replaces enumeration. Origin: I-001-T1-R1 FAILED honestly on an
untracked Director courier zip after two prior defects of the same class (JRN-I001-11).

L-14: The PM authors judges, never contestants. Specs, interface declarations, fixtures, oracle
values, pre-registered gate thresholds, and acceptance-test files may be PM-authored;
implementation code under test — and above all any Law 7 named baseline — is agent-authored
from the spec. A packet whose FILES section carries implementation translation units converts
review into the PM checking its own output and voids the P6 §2.2 / L-10 premise that the PM has
no repo access; pre-registered digests of agent deliverables are the tell. Corollary: the PM
does not build or execute the repository — P6 §7.4 "pre-verifying acceptance outputs" means
deriving expected oracle values from specifications, never running the codebase. Enforcement:
any packet carrying src/ implementation content, and any journal entry showing PM-executed
build/test output, is a P6 incident. Origin: C-001-T1–T10 (packets 25–34), where .cpp/.hpp
implementation rode packet FILES sections with digests pre-registered and test counts pre-built;
surfaced at Director review of OUT_34; second occurrence of the PM-authoring class after the
I-002 fixture-generator correction → P6 §4.6 amendment proposed per P6 §6.3 (JRN-C001-42).

L-15: Review proportionality for evidence defects. A miss on a substantive acceptance
criterion (a registered number, bound, or behavior) is always REJECT. A miss on evidence
completeness where the underlying datum appears byte-verbatim elsewhere in the same OUT
(e.g., digests present in a command paste but absent from the FILE DIGESTS section) is
ACCEPT with a mandatory remediation step at the top of the next dispatched task; the
remediation re-derives the missing evidence and asserts it against the OUT's existing
copies — any mismatch is a BLOCK. Evidence absent from the OUT entirely is REJECT. Rationale:
re-running a substantively perfect task to reformat evidence is process worship, but leaving
the ledger incomplete silently rots L-10; the remediation step closes the ledger at the cost
of one command, not one cycle. Origin: OUT_39 (I-003-T2-R1), FILE DIGESTS carrying 2 of 16
fixture entries while all 16 sha256s appeared verbatim in the step-4 generator paste.

L-15 v2 (refines L-15; origin OUT_41): between L-15's remediation branch and its REJECT
branch sits a third case — a substantive bound whose aggregate satisfaction appears as
byte-verbatim, machine-emitted tool output in the OUT (with exit=0 gating, and the checking
tool demonstrably fail-loud), while the per-item values are absent from the OUT but
recoverable from committed artifacts. Ruling: ACCEPT with mandatory remediation that
re-derives the per-item table from the committed artifacts and asserts the aggregate against
the OUT's verbatim claim; any mismatch is a BLOCK. Standing tooling rule: check tools print
per-item tables by default; a summary line never substitutes for the table in evidence.
Absent BOTH the verbatim machine assertion and recoverable per-item artifacts, the REJECT
branch stands unchanged.

L-16: The OUT is the review surface. Every acceptance criterion's artifact appears
byte-verbatim inside the OUT itself; a pointer to a repo file (TR or otherwise) is
inadmissible as evidence, because model-B review independence (P6 §2.2, L-14) rests on the
PM having no repo access. Truncated digests are not digests — every sha256 appears in full.
The TR is pasted verbatim into the OUT's REPORT section AND listed in FILE DIGESTS.
PM-side corollary (owned contributing factor, packets 39–44): OUT-REQUIREMENTS are restated
in full in every packet — never by reference to a prior serial; requirement-by-reference
decays across fresh agent instances. Review ladder for the record: substantive criterion
miss → REJECT (OUT_38); partial completeness with the aggregate byte-verbatim in the OUT →
ACCEPT + remediation (OUT_39, OUT_41, L-15/v2); wholesale evidence absence or repo-pointer
evidence → REJECT (OUT_44). Origin: OUT_44.

L-17: A gate dispatch's pre-flight must exercise the full verdict pipeline — execution AND
checking — end-to-end on non-held-out data that mirrors every registered data shape of the
held-out corpus (reference numeric formats, empty/zero-event shapes, every curve family the
checkers must read). Engine-side smoke alone is insufficient: the judge is part of the gate
infrastructure, and a judge that has never read the corpus's data shapes fails at first
contact exactly like an engine that hasn't. Enforcement: every gate packet's pre-flight
criteria include a committed checker shape self-test (fail-loud, with at least one
deliberate over-tolerance vector) run before the first held-out contact. Origin: three
same-class halts — OUT_46 (loader vs held-out fixture shapes, JRN-C001-63), OUT_48
(zero-event write shape, JRN-C001-71), OUT_50 (checker vs rational reference fields,
JRN-C001-79); the third occurrence triggered this entry per P6 §6.3, with a P6 §4 amendment
proposal riding the open-decision-2 bundle.

L-13 v2 (refines L-13; origin OUT_51/JRN-C001-83): workspace-cleanliness criteria assert
only the untracked DELTA a dispatch introduces — entries within the agent-writable surface
that first appear after the dispatch's CLAIM commit must be limited to files the task
creates pre-commit. The absolute untracked state is pasted byte-verbatim for the record but
never asserted: inter-dispatch residue (a prior dispatch's post-status scratch, evidence
directories, caches) makes absolute assertions over the surface unattainable by the current
agent, exactly as courier artifacts did outside it (L-13). Pre-existing untracked entries
within the surface are identified as inherited with a stated disposition (commit or delete)
executed in this or the next packet — never silently tolerated, so residue cannot
accumulate. Origin: OUT_51, where inherited docs/.../reports/gate_r2_evidence/ (created by
the R2 dispatch after its own status paste) rendered T15's criterion 7 unsatisfiable;
fourth instance of the workspace-state authoring class (L-09 → L-11 → L-13 → this).

L-18: An acceptance criterion may bind a numeric expectation only when the number is
derived from the semantics of the run that criterion governs, with the derivation stated
in the criterion or brief. Numbers imported from a different measurement context — a
reference comparison window, a prior task's horizon, an expected failure signature on
parameters not yet chosen — are guesses wearing thresholds' clothes: when they fire they
block sound work, and when they don't they certify nothing. Where no derivation exists,
the criterion asserts internal consistency and honest reporting of the measured value, and
routes any cross-context comparison through the instrument registered for it (checker,
test suite). Enforcement: at authoring, every numeric expectation carries a one-line
derivation; at review, a numeric criterion without one is a PM authoring defect. Origin:
PACKET 54 c3 ("E1 zero events" — expected failure signature on fresh parameters,
JRN-C001-95) and PACKET 55 c6 ("events=12" — reference-window count bound to a
settle-semantics run, JRN-I008-4); second occurrence per P6 §6.3, with the companion P6 §4
amendment proposal riding open decision 2.

L-19: Every binding clause of the spec a task delivers against must be operationalized as
at least one acceptance criterion at dispatch, or explicitly waived in the packet with a
reason. A clause without a criterion will be optimized away — twice now the letter of the
criteria was met while the clause died (S11 confinement, JRN-I008-18; S11 scene
definitions, JRN-I008-21). At authoring, the PM walks the spec clause-by-clause and asks
"which criterion would fail if this clause were violated?"; a clause with no answer gets a
criterion or a written waiver. At review, a discovered clause-without-criterion is a PM
authoring defect; conformance is re-established by amendment and repair, never by silent
reinterpretation. Companion P6 §4 amendment proposal rides open decision 2. Origin:
JRN-I008-18, JRN-I008-21; second occurrence per P6 §6.3.
