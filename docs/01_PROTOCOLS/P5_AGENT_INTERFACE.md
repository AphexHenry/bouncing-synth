# P5 — AGENT INTERFACE PROTOCOL (Cursor, single-file loop)

```
doc_id:      P5
layer:       protocol
audience:    Director (couriering), PM (authoring packets), Agents (§3 and AGENTS.md)
status:      ACTIVE v1.0 (framework — domain-free)
kind:        FRAMEWORK — reused verbatim.
parent:      P0
```

This protocol adapts the program to Cursor-hosted agents. Principles: **the repo is the only
channel**, and **the Director carries exactly one file in each direction per cycle.** The PM authors
one self-applying PACKET file; the agent applies it, executes it, and answers with one OUT file.
Nothing said in any chat is ever load-bearing.

---

## 1. Workspace layout

One Cursor workspace = one git repo containing both layers:

```
<repo root>/
    AGENTS.md            ← auto-read by Cursor agents; the standing law injection (see repo file)
    inbox/               ← where the Director saves each PACKET_<serial>.md; contains APPLIED.log
    outbox/              ← where agents write each OUT_<serial>[_<task>].md
    docs/                ← the program brain (00_STATE.md, 00_PROJECT.md, 01_PROTOCOLS/,
                           DIRECTORS_MANUAL.md, LESSONS_CORE.md, 02_PROGRAM/, 03_TRACKS/,
                           04_ARCHIVE/, 05_INFRA/)
    src/ config/ data/ tests/ reports/   ← the research codebase, per P3 §1
```

All brain paths in packets and briefs are written relative to the repo root (`docs/...`). The document
repo you were given as a zip is extracted into `docs/` unchanged, except: `AGENTS.md`, `inbox/`,
`outbox/` move to the repo root.

Note on enforcement: Cursor cannot technically prevent an agent from opening any file. The read-scope
rules (P0 §3.1) are therefore restated in `AGENTS.md` and in every packet, and compliance is checked
at review — an agent whose output shows knowledge outside its whitelist fails review.

## 2. One packet, one agent, one branch, one chat

- The Director starts a **new agent chat per packet** (no packet is ever processed in a stale chat —
  stale context is how weak agents drift).
- The agent works on branch `task/<task-id>` (or `packet/<serial>` for taskless packets) and finishes
  with a single commit (or small commit series) containing: the applied packet files, code + tests,
  the task report, its journal entries, the `APPLIED.log` line, and the OUT file.
- CLAIM discipline: after the APPLY step, the agent's next action is appending the CLAIM entry to the
  journal and committing it. If the journal already shows an unresolved CLAIM for that task, the agent
  stops and reports — this is the collision guard when multiple agents run.
- BLOCKED is a normal ending: the agent commits the BLOCKED report + journal entry + OUT file and
  stops. The Director carries the OUT file to the PM, the PM answers inside its next packet (brief
  amendment or NOTE entry), and the task is re-dispatched in a **fresh chat** with that packet.

## 3. The dispatch line (the only thing the Director types)

The Director's entire chat message to a new agent is one fixed line (plus the file attached or present
in the repo):

```
Process inbox/PACKET_<serial>.md per AGENTS.md.
```

Nothing else. The packet carries all instruction. If the Director types anything mid-task beyond
"continue" or "stop", agents treat it as untrusted context: real instruction changes arrive only
inside committed packets. If a chat message conflicts with the packet or brief, follow the packet/brief
and file a BLOCKED report quoting the conflict.

## 4. The PACKET file (PM-authored; the single file inbound)

Every PM response that advances the program ends with exactly one complete, copy-paste-ready file named
`PACKET_<serial>.md`. Serials are consecutive integers with no gaps, program-wide. Format:

```
# PACKET <serial> — <short title>
pm: <PM instance id> · date: <UTC date> · task: <TASK id or none>

== VERDICT ==
<what was decided and why, 5 lines max: accept / return-for-repair / brief amendment /
 gate call / new task issued / state update only>

== FILES ==
<zero or more blocks. Every file the program's state change requires — STATE overwrite,
 journal appends, register rows, new/amended briefs, pre-registrations — appears here
 in full. The agent transcribes; it never composes.>

=====[ FILE OVERWRITE: docs/00_STATE.md ]=====
<entire new file content>
=====[ END FILE ]=====

=====[ FILE APPEND: docs/03_TRACKS/<id>_name/JOURNAL.md ]=====
<exact block to append — journals at top, registers/lessons/logs at bottom>
=====[ END FILE ]=====

== TASK ==
<none, or exactly one task instruction, fully self-contained: the reading list
 (P0 §2–§6, P3, P4, the brief sections for this TASK, the 00_PROJECT.md sections it needs,
 the whitelist), the assignment ("execute TASK <id> exactly as written"), the non-negotiables
 (stop-on-surprise, evidence per criterion, manifest ids, no invented values, whitelists), and the
 end-state sentence. This section replaces the old chat-pasted dispatch verbatim.>
```

Authoring rules (PM):
- **APPLY is transcription.** Any content an agent must place in the brain goes in `== FILES ==`,
  byte-exact. A packet may not instruct an agent to "update STATE to reflect X" — the PM writes the
  new STATE here in full.
- Delimiter safety: no line inside a file block may begin with `=====[`. If content would, the PM
  restructures the content.
- Direction markers: `OVERWRITE` (replace whole file; also used to create new files) and `APPEND`
  (journals at top, per P1 §3; registers, LESSONS, APPLIED.log at bottom).
- One packet = at most one TASK. Parallel tasks = multiple packets, each dispatched to its own fresh
  chat; their serials fix the apply order.
- A PM response without a packet is discussion, not a decision, and changes nothing. If the PM
  realizes an earlier packet was wrong, the fix is a new packet (with a CORRECTION journal entry in
  its FILES), never "please un-commit."
- Preconditions the Director must check are stated at the top of the TASK section as a single yes/no
  line (e.g. "Precondition: `docs/05_INFRA/JOURNAL.md` shows WS0-T2 DONE — if not, dispatch that
  packet first").

## 5. The OUT file (agent-authored; the single file outbound)

Every dispatch ends with the agent committing exactly one file,
`outbox/OUT_<serial>[_<task-id>].md`:

```
# OUT <serial> — <task id or "apply only"> — <DONE | BLOCKED | FAILED | APPLIED>
agent: <id> · branch: <branch> · commits: <shas>

== APPLY CONFIRMATION ==
serial <n> applied · files written: <list of path + OVERWRITE/APPEND> · ledger line pasted

== JOURNAL ENTRIES (verbatim copies) ==
<every entry this dispatch appended>

== REPORT (verbatim copy) ==
<the full TR_/BLK_/FAILED report exactly as committed to reports/>

== COURIER ARTIFACTS ==
<inline copies of every artifact the TASK's `courier:` field names: validation tables,
 test output, parameter tables, small CSVs/heads. Larger or licensed artifacts: path + sha256 only.>
```

The repo files are the source of truth; the OUT file is a faithful bundle of copies so the PM can
review without repo access. An OUT file that omits or paraphrases a committed report is a protocol
violation.

## 6. The loop (one research cycle)

The PM is a chat instance with no repo access; the Director is the **courier** between the PM chat and
the repo/agent chats:

```
PM emits PACKET_<n>.md  →  Director saves it to inbox/, opens a NEW agent chat,
                            types: "Process inbox/PACKET_<n>.md per AGENTS.md."
    →  agent applies + executes + commits, ending with outbox/OUT_<n>….md
        →  Director uploads that one OUT file to the PM
            →  PM reviews, emits the next PACKET  →  (repeat)
```

Director duties per cycle, in order:
1. Save the packet file at `inbox/PACKET_<serial>.md` exactly as received. (Committing it yourself is
   optional — the agent commits it during APPLY.)
2. Open a new agent chat; type the one dispatch line (§3). If the TASK section states a precondition,
   check that one yes/no first.
3. When the agent ends, upload its `outbox/OUT_…` file to the PM. Nothing else is needed in the same
   PM conversation.
4. On a PM accept verdict (in the next packet's VERDICT): merge the agent's branch. Never merge before
   the accept.

Only the PM changes program state (register rows, `00_STATE.md`, gate calls, brief amendments) — and
it does so exclusively through packet FILES sections. The Director carries; the PM decides; agents
execute and transcribe.

Model note: strong-but-cheap models fit the agent role as specced (judgment has been removed from it).
If an agent repeatedly BLOCKs on ambiguity that isn't there, that is signal about the packet/brief, not
the agent — forward the OUT file with that observation.

## 7. Minimum forwarding set (Director → PM)

| Situation | Upload to the PM |
|---|---|
| Continuing with the same PM conversation | the one `OUT_…` file — nothing else |
| Fresh PM instance (new conversation) | the current `docs/` as a zip **plus** any OUT file(s) awaiting review; the PM boots per P0 §6 before reviewing |
| Director question only (no agent output) | current `docs/00_STATE.md` if the conversation is fresh; otherwise just ask |

Any time the Director is unsure whether the PM's picture is current: send the zip. Stale-context PM
decisions are the loop's main failure mode, and the zip is cheap insurance. (The OUT files' journal
copies keep a long-running PM conversation current without zips for many cycles.)

## Changelog
- v1.0 — Framework issue. Single-file loop kept intact from the lineage; examples de-domained
  (generic `<id>` tracks; "no invented values" in the TASK non-negotiables); reading list adds "the
  `00_PROJECT.md` sections it needs"; workspace layout lists `00_PROJECT.md` and `LESSONS_CORE.md`.
