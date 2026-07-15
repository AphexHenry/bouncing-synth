# DIAG C-001-T16 — Forensic diagnostic of executed P1-A check (read-only; no verdict)

```
doc_id:   DIAG-C-001-T16
layer:    track
audience: PM, Director
status:   DONE
parent:   C-001-T16 / PACKET 53
```

## Step 3 — Chain of custody

Command:

```bash
python3 - <<'PY'
import hashlib, json, os
REPO = "/Users/baptistebohelay/Dev/research/bouncing-synth"
manifest = json.load(open(os.path.join(REPO, "tools/gaterunner/manifests/P1-A.json")))
events_dir = os.path.join(REPO, "tools/gaterunner/events/P1-A")
ok = 0
for s in manifest["scenarios"]:
    path = os.path.join(events_dir, s["scenario_id"] + ".jsonl")
    h = hashlib.sha256(open(path, "rb").read()).hexdigest()
    if h == s["event_file_sha256"]:
        ok += 1
    else:
        print("MISMATCH", s["scenario_id"], s["event_file_sha256"], h)
print(f"custody ok {ok}/{len(manifest['scenarios'])}")
PY
```

Output:

```
custody ok 32/32
```

## Step 4 — D1 COUNT TABLE

Registered_window: 12 for quasi-chaotic cells (v1.3 C1); otherwise `min(200, reference_events)`.
Executed_window transcribed from OUT_52 GATE-P1-R3 checker report (lines 362–393).
Engine header field: `engine_events` in `bounce-events-v1` schema line.

| scenario_id | engine_hdr | engine_body | hdr=body | ref_events | reg_window | exec_window | short_side |
|---|---:|---:|---|---:|---:|---:|---|
| HO-bezier-periodic-1 | 200 | 200 | OK | 1 | 1 | 1 | reference |
| HO-bezier-periodic-2 | 21 | 21 | OK | 1 | 1 | 1 | reference |
| HO-bezier-settle-1 | 6 | 6 | OK | 1 | 1 | 1 | reference |
| HO-bezier-settle-2 | 12 | 12 | OK | 2 | 2 | 2 | reference |
| HO-bezier-settle-3 | 18 | 18 | OK | 3 | 3 | 3 | reference |
| HO-flat-periodic-1 | 70 | 70 | OK | 6 | 6 | 6 | reference |
| HO-flat-periodic-2 | 112 | 112 | OK | 4 | 4 | 4 | reference |
| HO-flat-periodic-3 | 140 | 140 | OK | 8 | 8 | 8 | reference |
| HO-flat-settle-1 | 15 | 15 | OK | 6 | 6 | 6 | reference |
| HO-flat-settle-2 | 16 | 16 | OK | 6 | 6 | 6 | reference |
| HO-flat-settle-3 | 30 | 30 | OK | 8 | 8 | 8 | reference |
| HO-flat-settle-4 | 44 | 44 | OK | 9 | 9 | 9 | reference |
| HO-graze-parabola-1 | 0 | 0 | OK | 0 | 0 | 0 | neither |
| HO-graze-parabola-2 | 1 | 1 | OK | 1 | 1 | 1 | neither |
| HO-graze-parabola-3 | 2 | 2 | OK | 2 | 2 | 2 | neither |
| HO-parabola-periodic-1 | 0 | 0 | OK | 6 | 6 | 0 | engine |
| HO-parabola-periodic-2 | 0 | 0 | OK | 6 | 6 | 0 | engine |
| HO-parabola-settle-1 | 2 | 2 | OK | 4 | 4 | 2 | engine |
| HO-parabola-settle-2 | 2 | 2 | OK | 4 | 4 | 2 | engine |
| HO-parabola-settle-3 | 4 | 4 | OK | 6 | 6 | 4 | engine |
| HO-parabola-settle-4 | 6 | 6 | OK | 6 | 6 | 6 | neither |
| HO-poly-double-root-1 | 12 | 12 | OK | 5 | 5 | 5 | reference |
| HO-poly-periodic-1 | 15 | 15 | OK | 8 | 8 | 8 | reference |
| HO-poly-periodic-2 | 1 | 1 | OK | 8 | 8 | 1 | engine |
| HO-poly-quasichaotic-1 | 2 | 2 | OK | 25 | 12 | 2 | engine |
| HO-poly-quasichaotic-2 | 2 | 2 | OK | 25 | 12 | 2 | engine |
| HO-poly-quasichaotic-3 | 3 | 3 | OK | 25 | 12 | 3 | engine |
| HO-poly-quasichaotic-4 | 3 | 3 | OK | 25 | 12 | 3 | engine |
| HO-poly-settle-3 | 2 | 2 | OK | 12 | 12 | 2 | engine |
| HO-poly-settle-4 | 3 | 3 | OK | 12 | 12 | 3 | engine |
| HO-poly-settle-5 | 3 | 3 | OK | 2 | 2 | 2 | reference |
| HO-poly-settle-6 | 3 | 3 | OK | 12 | 12 | 3 | engine |

All 32 header/body counts agree. No fixture horizon-metadata vs reference-length contradiction
flagged (reference stream lengths embody settle per I-002-T2/T3a).

## Step 5 — D2 WINDOW AUDIT

Verbatim window-derivation code (`tools/gaterunner/check_p1a.py`):

```84:88:tools/gaterunner/check_p1a.py
def confirmatory_window(scenario_id: str, ref_len: int, eng_len: int) -> int:
    base = min(200, ref_len if ref_len else eng_len, eng_len)
    if scenario_id in QUASI_IDS:
        return min(QUASI_WINDOW, base, ref_len, eng_len)
    return min(200, ref_len if ref_len else eng_len, eng_len)
```

Constants (lines 28–36): `QUASI_WINDOW = 12`, `QUASI_IDS` = four `HO-poly-quasichaotic-*`.

**Executed formula:**

- Non-quasi-chaotic: `window = min(200, ref_len, eng_len)`
- Quasi-chaotic: `window = min(12, ref_len, eng_len)`

**Registered procedure (PREREG §1 + v1.3 C1):**

- Non-quasi-chaotic: `H = min(200 events, settle per S-1)` — reference streams embody settle;
  confirmatory window should be `min(200, reference_events)` when `eng_len ≥` that horizon.
- Quasi-chaotic (v1.3 C1): confirmatory window = **first 12 events**; events 13–25 computed and
  reported as exploratory (excluded from primary criterion).

**Deviation:**

1. The checker **always caps** the comparison window at `eng_len` via `min(..., eng_len)`. When
   `eng_len < registered_window`, the executed window shrinks to the engine stream length
   instead of retaining the registered horizon and surfacing a count/seq failure per §1
   ("ball_id and seq exactly equal per event" — a stream-length mismatch must surface as a
   count/seq failure, not silent truncation).
2. For quasi-chaotic cells, registered confirmatory window is 12 (v1.3 C1) but executed windows
   were 2–3 (OUT_52); the mandatory events 13–25 exploratory tables were empty because
   `min(EXPLORATORY_END, len(refs), len(eng))` loop bound is `min(25, 25, 2) = 2` (lines
   167–177) — no events at indices ≥12 are compared.
3. When `eng_len ≥ registered_window` and `ref_len ≥ registered_window`, executed window
   equals registered window (no shrinkage). No scenario in this corpus has both streams
   covering the quasi-chaotic 12-event confirmatory window while executed window falls short.

## Step 6 — D3 PAIRING AUDIT

Verbatim pairing/comparison loop (`tools/gaterunner/check_p1a.py`):

```109:139:tools/gaterunner/check_p1a.py
def compare_reference_agreement(
    refs: list[dict[str, Any]],
    eng: list[dict[str, Any]],
    window: int | None = None,
) -> tuple[bool, float, float]:
    """Compare reference events to engine events using exact rational tolerances."""
    if len(refs) == 0 and len(eng) == 0:
        return True, 0.0, 0.0

    if window is None:
        window = min(200, len(refs) if refs else len(eng), len(eng))

    worst_dt = Fraction(0)
    worst_ds = Fraction(0)
    ok = True
    if len(refs) < window or len(eng) < window:
        ok = False
    else:
        for i in range(window):
            ref = refs[i]
            ev = eng[i]
            if int(ref["ball_id"]) != int(ev.get("ball_id", -1)):
                ok = False
            if int(ref["seq"]) != int(ev.get("seq", -1)):
                ok = False
            dt, ds = compare_event_deltas(ref, ev)
            worst_dt = max(worst_dt, dt)
            worst_ds = max(worst_ds, ds)
            if dt > EXACT_TOL_T or ds > EXACT_TOL_S:
                ok = False
    return ok, float(worst_dt), float(worst_ds)
```

**Seq / count enforcement disposition:**

- Pairing is **by positional index** `i` over `range(window)` — not by `(ball_id, seq)` lookup.
- `ball_id` and `seq` mismatches set `ok = False` but comparison **continues**; values are still
  compared at the mismatched index.
- When `len(refs) < window` or `len(eng) < window`, `ok = False` with **no per-event deltas**
  computed — but `confirmatory_window()` pre-shrinks `window` to `min(ref, eng)`, so this branch
  is bypassed in practice: streams are zip-truncated silently to the shorter length rather than
  failing at the registered horizon.
- §1 requirement ("ball_id and seq exactly equal per event"; count mismatch must surface) is
  **not enforced** as a hard stop before value comparison.

**s-comparison / wrap disposition** (`tools/gaterunner/ref_parse.py`):

```50:56:tools/gaterunner/ref_parse.py
def compare_event_deltas(ref: dict[str, Any], event: dict[str, Any]) -> tuple[Fraction, Fraction]:
    """Return exact |Δt| and |Δs| between one reference event and one engine event."""
    rt = parse_reference_number(str(ref["t"]))
    et = engine_event_fraction(event, "t", "t_hex")
    rs = parse_reference_number(str(ref["contact"]["x"]))
    es = engine_event_fraction(event, "s", "s_hex")
    return abs(et - rt), abs(es - rs)
```

- `s` is compared as **raw parameter values** with no domain-period normalization or endpoint-wrap
  handling. A discrepancy of exactly the inter-ball initial offset (or domain length) at a
  ball_id phase inversion therefore appears as a large `|ds|` even when `|dt|` is at rounding
  scale.

## Step 7 — D4 EXCERPTS

### HO-flat-periodic-3 (first |ds|-anomalous event, seq 0)

Reference (fixture `data/scenarios/heldout/HO-flat-periodic-3.json`, events 0–7):

```json
{"ball_id": 0, "contact": {"x": "0.70710678118654752440084436210484903928483593768847", "y": "0.0"}, "seq": 0, "t": "0.70710678118654752440084436210484903928483593768847", "tier": 1}
{"ball_id": 1, "contact": {"x": "1.7071067811865475244008443621048490392848359376885", "y": "0.0"}, "seq": 1, "t": "0.70710678118654752440084436210484903928483593768847", "tier": 1}
{"ball_id": 0, "contact": {"x": "2.1213203435596425732025330863145471178545078130654", "y": "0.0"}, "seq": 2, "t": "2.1213203435596425732025330863145471178545078130654", "tier": 1}
{"ball_id": 1, "contact": {"x": "3.1213203435596425732025330863145471178545078130654", "y": "0.0"}, "seq": 3, "t": "2.1213203435596425732025330863145471178545078130654", "tier": 1}
{"ball_id": 0, "contact": {"x": "3.5355339059327376220042218105242451964241796884424", "y": "0.0"}, "seq": 4, "t": "3.5355339059327376220042218105242451964241796884424", "tier": 1}
{"ball_id": 1, "contact": {"x": "4.5355339059327376220042218105242451964241796884424", "y": "0.0"}, "seq": 5, "t": "3.5355339059327376220042218105242451964241796884424", "tier": 1}
{"ball_id": 0, "contact": {"x": "4.9497474683058326708059105347339432749938515638193", "y": "0.0"}, "seq": 6, "t": "4.9497474683058326708059105347339432749938515638193", "tier": 1}
{"ball_id": 1, "contact": {"x": "5.9497474683058326708059105347339432749938515638193", "y": "0.0"}, "seq": 7, "t": "4.9497474683058326708059105347339432749938515638193", "tier": 1}
```

Engine (`tools/gaterunner/events/P1-A/HO-flat-periodic-3.jsonl`, events 0–7):

```json
{"t_hex":"0x1.6a09e667f3bccp-1","t":0.70710678118654746,"ball_id":1,"s_hex":"0x1.b504f333f9de6p+0","s":1.7071067811865475,"impact_speed_hex":"0x1.6a09e667f3bccp+1","impact_speed":2.8284271247461898,"normal_x_hex":"-0x0p+0","normal_x":-0,"normal_y_hex":"0x1p+0","normal_y":1,"seq":0,"schema_version":1}
{"t_hex":"0x1.6a09e667f3bcdp-1","t":0.70710678118654757,"ball_id":0,"s_hex":"0x1.6a09e667f3bcdp-1","s":0.70710678118654757,"impact_speed_hex":"0x1.6a09e667f3bcdp+1","impact_speed":2.8284271247461903,"normal_x_hex":"-0x0p+0","normal_x":-0,"normal_y_hex":"0x1p+0","normal_y":1,"seq":1,"schema_version":1}
{"t_hex":"0x1.0f876ccdf6cd9p+1","t":2.1213203435596424,"ball_id":1,"s_hex":"0x1.8f876ccdf6cd9p+1","s":3.1213203435596424,"impact_speed_hex":"0x1.6a09e667f3bccp+1","impact_speed":2.8284271247461898,"normal_x_hex":"-0x0p+0","normal_x":-0,"normal_y_hex":"0x1p+0","normal_y":1,"seq":2,"schema_version":1}
{"t_hex":"0x1.0f876ccdf6cdap+1","t":2.1213203435596428,"ball_id":0,"s_hex":"0x1.0f876ccdf6cdap+1","s":2.1213203435596428,"impact_speed_hex":"0x1.6a09e667f3bcfp+1","impact_speed":2.8284271247461912,"normal_x_hex":"-0x0p+0","normal_x":-0,"normal_y_hex":"0x1p+0","normal_y":1,"seq":3,"schema_version":1}
{"t_hex":"0x1.c48c6001f0acp+1","t":3.5355339059327378,"ball_id":1,"s_hex":"0x1.22463000f856p+2","s":4.5355339059327378,"impact_speed_hex":"0x1.6a09e667f3bdp+1","impact_speed":2.8284271247461916,"normal_x_hex":"-0x0p+0","normal_x":-0,"normal_y_hex":"0x1p+0","normal_y":1,"seq":4,"schema_version":1}
{"t_hex":"0x1.c48c6001f0ac4p+1","t":3.5355339059327395,"ball_id":0,"s_hex":"0x1.c48c6001f0ac4p+1","s":3.5355339059327395,"impact_speed_hex":"0x1.6a09e667f3bd9p+1","impact_speed":2.8284271247461956,"normal_x_hex":"-0x0p+0","normal_x":-0,"normal_y_hex":"0x1p+0","normal_y":1,"seq":5,"schema_version":1}
{"t_hex":"0x1.3cc8a99af5454p+2","t":4.9497474683058336,"ball_id":1,"s_hex":"0x1.7cc8a99af5454p+2","s":5.9497474683058336,"impact_speed_hex":"0x1.6a09e667f3bdp+1","impact_speed":2.8284271247461916,"normal_x_hex":"-0x0p+0","normal_x":-0,"normal_y_hex":"0x1p+0","normal_y":1,"seq":6,"schema_version":1}
{"t_hex":"0x1.3cc8a99af5458p+2","t":4.9497474683058371,"ball_id":0,"s_hex":"0x1.3cc8a99af5458p+2","s":4.9497474683058371,"impact_speed_hex":"0x1.6a09e667f3bd7p+1","impact_speed":2.8284271247461947,"normal_x_hex":"-0x0p+0","normal_x":-0,"normal_y_hex":"0x1p+0","normal_y":1,"seq":7,"schema_version":1}
```

Finding: at every index `i`, `seq` matches but `ball_id` is phase-inverted (ref alternates 0,1; eng
alternates 1,0); |ds|=1.000000e+00 exact at |dt|≈4.4e-15 rounding scale — positional pairing
compares the wrong ball's `s` against each reference `contact.x`.

### HO-poly-quasichaotic-1 (first divergence)

Reference (events 0–2):

```json
{"ball_id": 0, "contact": {"x": "0.47987945881452564442343543243092457012876206385975", "y": "0.0033144285325011670120304232864307043756905887421849"}, "seq": 0, "t": "1.1996986470363141110585885810773114253219051596494", "tier": 2}
{"ball_id": 0, "contact": {"x": "0.077229513919786739454117246823814600711253015317363", "y": "0.0000022233775849149221840928219732002445802161562327475"}, "seq": 1, "t": "3.2904784726757343836817629363165337068904141775083", "tier": 2}
{"ball_id": 0, "contact": {"x": "-0.30999699427945856625592632893074872861859390063186", "y": "0.00057717823947041103572868190269461142236661320128912"}, "seq": 2, "t": "5.2769537141117656152158898662645351001953046599288", "tier": 2}
```

Engine (events 0–1 — entire committed stream):

```json
{"t_hex":"0x1.331f735613901p+0","t":1.1996986470363142,"ball_id":0,"s_hex":"0x1.eb65855685b35p-2","s":0.47987945881452571,"impact_speed_hex":"0x1.601f726cf3c93p+3","impact_speed":11.003838742062987,"normal_x_hex":"-0x1.c47893a93d921p-6","normal_x":-0.027616638374604045,"normal_y_hex":"0x1.ffce01ef0cd1p-1","normal_y":0.99961858790485003,"seq":0,"schema_version":1}
{"t_hex":"0x1.331f7356138fcp+0","t":1.1996986470363131,"ball_id":0,"s_hex":"0x1.eb65855685b39p-2","s":0.47987945881452593,"impact_speed_hex":"0x1.4e84464de7991p+3","impact_speed":10.453646804959847,"normal_x_hex":"-0x1.c47893a93d92bp-6","normal_x":-0.027616638374604079,"normal_y_hex":"0x1.ffce01ef0cd1p-1","normal_y":0.99961858790485003,"seq":1,"schema_version":1}
```

Finding: seq 0 agrees; at seq 1 reference expects t≈3.29 but engine emits a second contact at
t≈1.1997 (duplicate-time event) — missing events on engine side from seq 1 onward; worst |dt|
reported as 2.090780e+00.

### HO-parabola-settle-2 (first divergence)

Reference (events 0–3):

```json
{"ball_id": 0, "contact": {"x": "1.4221363894199316741431946939163380457512602881771", "y": "0.50561797752808988764044943820224719101123595505618"}, "seq": 0, "t": "0.94809092627995444942879646261089203050084019211805", "tier": 1}
{"ball_id": 0, "contact": {"x": "-1.4648895033085741854501220289012847485720351352566", "y": "0.53647531422591029485513405208482890110861690808959"}, "seq": 1, "t": "1.3725138221939640875917196012368508395401397935883", "tier": 1}
{"ball_id": 0, "contact": {"x": "-2.5261113952622430128663691363219662029621783777234", "y": "1.5953096953184390377976261932189212691479251565011"}, "seq": 2, "t": "2.2455735640253350879900211425952070118098831028438", "tier": 1}
{"ball_id": 0, "contact": {"x": "-1.3146037451166154370916664872894337973452295378911", "y": "0.43204575166865780141615812628286239044866172430113"}, "seq": 3, "t": "2.7139144358416243360543561868633403630269229818606", "tier": 1}
```

Engine (events 0–1 — entire committed stream):

```json
{"t_hex":"0x1.e56c2c840374fp-1","t":0.9480909262799545,"ball_id":0,"s_hex":"0x1.6c1121630297bp+0","s":1.4221363894199317,"impact_speed_hex":"0x1.1311d127bebf5p+3","impact_speed":8.5959249283095946,"normal_x_hex":"-0x1.28b44c085ab1ap-1","normal_x":-0.57950055696469183,"normal_y_hex":"0x1.a143fd478e653p-1","normal_y":0.81497184275139956,"seq":0,"schema_version":1}
{"t_hex":"0x1.e56c2c840374fp-1","t":0.9480909262799545,"ball_id":0,"s_hex":"0x1.6c1121630297bp+0","s":1.4221363894199317,"impact_speed_hex":"0x1.6ec26c34fe544p+2","impact_speed":5.7306166188730607,"normal_x_hex":"-0x1.28b44c085ab1ap-1","normal_x":-0.57950055696469183,"normal_y_hex":"0x1.a143fd478e653p-1","normal_y":0.81497184275139956,"seq":1,"schema_version":1}
```

Finding: seq 0 matches; at seq 1 engine repeats the seq-0 contact (identical t and s) instead of
the reference's second bounce at t≈1.37 — missing genuine second contact on engine side.

## Step 8 — D5 CLASSIFICATION

Anomalous scenarios: OUT_52 FAIL rows (14 transcribed) + vacuous window-0 PASS rows
(HO-parabola-periodic-1, HO-parabola-periodic-2).

| scenario_id | rule | basis (D1+D4) |
|---|---|---|
| HO-parabola-periodic-1 | R-a | eng=0 < reg=6; ref=6 ≥ reg; exec=0 |
| HO-parabola-periodic-2 | R-a | eng=0 < reg=6; ref=6 ≥ reg; exec=0 |
| HO-parabola-settle-1 | R-a | eng=2 < reg=4; D4 pattern (engine short) |
| HO-parabola-settle-2 | R-a | eng=2 < reg=4; D4: missing second contact on engine |
| HO-parabola-settle-3 | R-a | eng=4 < reg=6 |
| HO-poly-periodic-2 | R-a | eng=1 < reg=8 |
| HO-poly-quasichaotic-1 | R-a | eng=2 < reg=12; D4: missing events from seq 1 |
| HO-poly-quasichaotic-2 | R-a | eng=2 < reg=12 |
| HO-poly-quasichaotic-3 | R-a | eng=3 < reg=12 |
| HO-poly-quasichaotic-4 | R-a | eng=3 < reg=12 |
| HO-poly-settle-3 | R-a | eng=2 < reg=12 |
| HO-poly-settle-4 | R-a | eng=3 < reg=12 |
| HO-poly-settle-6 | R-a | eng=3 < reg=12 |
| HO-bezier-settle-3 | R-d | eng=18 ≥ reg=3, ref=3; paired window=3; value disagreement |
| HO-parabola-settle-4 | R-d | eng=6 ≥ reg=6, ref=6; full window; value disagreement |
| HO-flat-periodic-3 | R-e | D4: |ds|=1.000000e+00 exact at |dt|≈4.4e-15; ball_id phase inversion under index pairing |

**Per-rule summary:** R-a=13 · R-b=0 · R-c=0 · R-d=2 · R-e=1

(R-c: no scenario satisfies `eng ≥ reg AND ref ≥ reg AND exec < reg` with this corpus; harness
shrinkage co-occurs with engine shortfall where `eng < reg`.)

## TR affirmations (H1–H4)

- **H1:** Zero engine invocations during this task. `wc -l data/scenarios/heldout/ACCESS_LOG.jsonl` → **88** (unchanged).
- **H2:** No `check_p1a.py --check` (or equivalent) invoked; checker source read only.
- **H3:** Modifications limited to `reports/`, journal, `outbox/` (this DIAG report).
- **H4:** Reference values exposed only in the three D4 excerpts above (≤8 events per side each);
  all other fixture reads were counts only.

## Step 9 — Workspace status and L-13 v2

```
## task/C-001-T16
 M docs/03_TRACKS/C-001_exact_collision_engine/JOURNAL.md
?? docs/03_TRACKS/C-001_exact_collision_engine/reports/DIAG_C-001-T16.md
?? docs/03_TRACKS/C-001_exact_collision_engine/reports/gate_r3_evidence/
?? inbox/PACKET_13.md
?? inbox/PACKET_15.md
?? inbox/PACKET_16.md
?? inbox/PACKET_17.md
?? inbox/PACKET_18.md
?? inbox/PACKET_19.md
?? inbox/PACKET_20.md
?? inbox/PACKET_21.md
?? inbox/PACKET_22.md
?? inbox/PACKET_23.md
?? inbox/PACKET_24.md
?? inbox/PACKET_25.md
?? inbox/PACKET_26.md
?? inbox/PACKET_27.md
?? inbox/PACKET_28.md
?? inbox/PACKET_29.md
?? inbox/PACKET_30.md
?? inbox/PACKET_31.md
?? inbox/PACKET_32.md
?? inbox/PACKET_33.md
?? inbox/PACKET_34.md
?? inbox/PACKET_35.md
?? inbox/PACKET_36.md
?? inbox/PACKET_37.md
?? inbox/PACKET_38.md
?? inbox/PACKET_39.md
?? inbox/PACKET_40.md
?? inbox/PACKET_41.md
?? inbox/PACKET_42.md
?? inbox/PACKET_43.md
?? inbox/PACKET_44.md
?? inbox/PACKET_45.md
?? inbox/PACKET_46.md
?? inbox/PACKET_47.md
?? inbox/PACKET_48.md
?? inbox/PACKET_49.md
?? inbox/PACKET_50.md
?? inbox/PACKET_51.md
?? inbox/PACKET_52.md
?? inbox/PACKET_53.md
?? tools/refsim/__pycache__/
?? tools/scenarios/__pycache__/
```

**L-13 v2 disposition (post-CLAIM delta):** delta limited to `reports/DIAG_C-001-T16.md`,
`outbox/OUT_53_C-001-T16.md`, and journal DONE entry. Inherited untracked entries outside
agent write surface (`inbox/PACKET_*.md`, `__pycache__/`, `docs/.../gate_r3_evidence/`) —
not asserted; disposition inherited from OUT_52.
