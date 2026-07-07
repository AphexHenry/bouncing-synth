# DIRECTOR'S MANUAL — How to run this system

```
doc_id: DIRECTOR-MANUAL · layer: protocol (framework) · audience: Director (you) · status: ACTIVE v1.0 · parent: P0
kind:   FRAMEWORK — reused verbatim. The only domain-specific reference is PROJECT §11.
```

You run a three-actor system: **you** (Director — final authority and courier), a **PM** (an AI
instance that decides strategy, writes packets, reviews results), and **agents** (Cursor workers that
process one packet each). You never write research instructions and never judge results — you carry
**one file each way** and approve the few things only a human should approve (the domain list is
`00_PROJECT.md §11`).

---

## 1. One-time setup

1. Create the code workspace (git repo). Extract the brain zip into `docs/`. Move `AGENTS.md`,
   `inbox/`, and `outbox/` from `docs/` to the **workspace root** (Cursor auto-reads AGENTS.md there).
2. Commit everything. The repo is now the program's single source of truth — chats are disposable, the
   repo is not.
3. Confirm `docs/00_PROJECT.md` has no gate-bearing `TBD` slots (§5, §6, §8, §10). If it does, the
   PM's first packet fills them before any track runs.
4. Answer the Open Decisions in `docs/00_STATE.md`. Tell the PM your answers; it will return a packet.

## 2. The cycle (this is 90% of your job)

```
①  PM emits ONE file: PACKET_<n>.md
②  you SAVE it to inbox/ and open a new Cursor chat with one line:
        Process inbox/PACKET_<n>.md per AGENTS.md.
③  the agent applies the packet, does the task, and commits ONE file: outbox/OUT_<n>….md
④  you UPLOAD that one file to the PM  →  PM reviews  →  next packet. Repeat.
```

**① Receive a packet.** Every real PM decision ends with one complete `PACKET_<serial>.md`. A PM reply
*without* a packet is just conversation — nothing to do. You never edit a packet; if something looks
wrong, say so and the PM re-emits it.

**② Save and dispatch.** Save the file at exactly `inbox/PACKET_<serial>.md`. If the packet's TASK
section states a precondition (a single yes/no check), check it. Open a **fresh** agent chat — one chat
per packet, never reused — and type the one line. That's the whole dispatch; the agent commits the
packet's contents itself.

**③ Wait for the agent's end state.** The legal ending is exactly one committed `outbox/OUT_<serial>….md`
marked DONE, BLOCKED, FAILED, or APPLIED. All are fine — blocked is a working outcome, not a failure.
If an agent chats at you instead of committing its OUT file, reply only: *"Commit your OUT file per
AGENTS.md and end."* Do not answer its questions in chat — questions belong in BLOCKED reports for the
PM.

**④ Forward to the PM.** Same PM conversation → upload just the OUT file. Fresh PM instance → zip the
current `docs/` folder and upload it **plus** the OUT file; the new PM will bootstrap itself (P0 §6)
and tell you when it's caught up. When unsure whether the PM's picture is current: send the zip. That's
the cheap insurance against the loop's main failure mode (a PM deciding on stale state).

## 3. What only you do (and what you never do)

**Yours alone:**
- Approve P0/P2 protocol changes and `00_PROJECT.md` changes (they instantiate P0/P2), budgets,
  purchases, credentials, any account creation, and anything leaving the loop. The domain specifics
  are `00_PROJECT.md §11`.
- Put credentials into the environment (env vars named in briefs). They never go in files, chats, or
  reports.
- Merge `task/<id>` branches — but **only after** a packet's VERDICT says "accept."
- Kill switch: you can stop anything at any time; tell the PM why so it lands in the journal.

**Never yours (route to the PM instead):**
- Writing or editing packets, briefs, criteria, thresholds, or model parameters.
- Answering an agent's substantive question in chat.
- Editing STATE, the module, registers, journals, or protocols by hand.
- Declaring a task done, a capability VERIFIED, or a result good. Especially that last one: a result
  that matches the data is a *suspect* until the PM's red-team packet says it survived held-out data
  and a matched-complexity baseline (P0 Law 9).

## 4. Starting a brand-new PM instance

Upload the `docs/` zip with this message:

> "You are the PM of this research program. Bootstrap per `01_PROTOCOLS/P0_MASTER.md` §6 (read
> `00_PROJECT.md` in full as step 2), then answer the sufficiency self-check in it before doing
> anything else. Pending review: [attach any waiting OUT files, or 'none']."

If the PM can't pass the self-check from the documents alone, that is a documentation bug — its first
packet should repair it. That property is the whole point of the system: any PM is replaceable at any
moment because the repo, not the conversation, is the memory.

## 5. Troubleshooting

| Symptom | Do |
|---|---|
| Agent worked around a problem instead of blocking (e.g. invented a missing value) | Forward its OUT file to the PM flagged "protocol violation" — the PM invalidates the task and re-dispatches fresh. Never keep the work. |
| Agent's report is thin (claims without pasted evidence) | Forward anyway; the PM returns it for repair with a fresh packet. Not your call to accept. |
| Agent refuses the packet: serial mismatch | You skipped or double-sent a packet. Tell the PM the last line of `inbox/APPLIED.log`; it re-issues with the right serial. |
| Same task blocks repeatedly on "ambiguity" | The packet/brief is at fault, not the agent. Tell the PM: "brief feedback, T-x blocked twice" — it amends via packet. |
| You forgot whether a packet was processed | Look at `inbox/APPLIED.log` — one line per applied packet. If in doubt, send the PM the docs zip and say so. |
| Two PM conversations gave conflicting instructions | The repo wins. Zip `docs/`, start one fresh PM, mention the conflict; it reconciles via a CORRECTION packet. |
| A result looks exciting | Do nothing except forward it. No sharing, no releasing, no extending. P0 Law 9 exists for exactly this moment. |
| Anything touching publication, dataset release, licensed material leaving the machine, or a human study | Out of scope for the loop. A PASSED gate authorizes a *proposal to you*, nothing more — and releases touching copyrighted material or human-subjects work deserve a real legal/ethics read beyond this research loop (`00_PROJECT.md §11`). |

## 6. Pocket summary

Save the packet. Type the one line. Upload the OUT file. Approve money, credentials, releases, and
P0/P2/module changes — nothing else. When in doubt, zip `docs/` and ask the PM. The repo is the brain;
you are its hands.
