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
