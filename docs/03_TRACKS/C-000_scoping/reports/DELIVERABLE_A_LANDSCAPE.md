# DELIVERABLE (a) — Prior-art landscape: physics-based sequencers & instruments

```
doc_id:   C-000-DELIV-A
layer:    track
audience: Director (Phase-0 gate), PM
status:   DRAFT (pending Phase-0 gate approval)
parent:   C-000-BRIEF / PROJECT §3(a)
```

Method: PM desk research, 2026-07-06, public web sources (URLs cited per entry). This is a plan
document, not gate-bearing data; no provenance tiers apply. Scope: products and works where
simulated physics of moving/bouncing bodies generates musical events.

## 1. Closest neighbors (bouncing bodies → MIDI)

**BounceBud** — Cem Olcay, 2023. iOS/macOS (Apple Silicon), standalone + AUv3 MIDI plugin.
Balls bounce in an arena whose four sides are configurable keyboards; a collision with a key emits
a MIDI note; per-side MIDI outputs; key/scale, velocity and octave ranges; deliberate randomization
of ball size/speed ("happy accidents", "different, interesting sequences every time").
No determinism or replay-identity claim; mobile-first; closed source.
Sources: https://keybudapp.com/bouncebud.html ·
https://synthanatomy.com/2023/09/bouncebud-new-midi-generative-sequencer-brings-physics-to-ios-and-macos.html ·
https://www.synthtopia.com/content/2023/09/21/bouncebud-for-ios-lets-you-generate-midi-with-physics/

**Droplets** — Finn Mitchell-Anyon, 2024. Desktop plugin + standalone, built-in synth + MIDI out.
Droplets fall from tempo-synced "drippers" and bounce off user-placed/rotated/stretched bars; bar
length sets pitch; physics section includes Wind (explicitly random deflection), gravity, tilt; a
quantize control pulls note onsets toward 16th/12th grid — evidence that raw game-physics timing
is felt as unmusical and is corrected after the fact. Closed source, paid.
Sources: https://www.soundonsound.com/news/droplets-physics-based-sequencer-plug ·
https://gearspace.com/board/new-product-alert-2-older-threads/1429821-droplets-physics-based-sequencer-plugin-out-now.html

**Musyc / Musyc2** — Fingerlab, 2013 / 2026. iOS/macOS, Musyc2 adds AUv3 + MIDI in/out.
Draw shapes; bodies bounce among them under a game-style "ultra-realistic" physics engine with
playful objects (planet, black hole, modulator); 55 sound kits; can act as generative MIDI
sequencer for external instruments. Emphasis on play and organic unpredictability; community
review notes it feels "more like a game … than something consistently productive" — control of
outcomes is weak by design. Closed source, paid.
Sources: https://www.fingerlab.net/portfolio/musyc ·
https://synthanatomy.com/2026/01/fingerlab-musyc2-brings-physics-driven-music-creation-to-ios-macos.html ·
https://forum.loopypro.com/discussion/67292/new-release-and-walkthrough-fingerlab-musyc2-ipad-iphone-mac-standalone-auv3

**Bouncy Notes** — Dillon Bastan / Ableton "Inspired by Nature", 2021. Max for Live MIDI effect
(Live 11+). Each incoming MIDI note drops a ball that bounces vertically on a piano roll under a
gravity simulation; each floor hit emits the note under the ball; wrap/random/delete edge
behaviors; speed/friction controls. One-dimensional bouncing on a discrete note grid; timing
follows the Max scheduler, not sample-accurate event computation; requires Live + Max.
Sources: https://www.ableton.com/en/packs/inspired-nature/ ·
https://dillonbastan.com/inspiredbynature_manuals/ (Bouncy Notes User Manual)

**BallSequencer** — UplandToys. Windows VST (freeware/follow-ware). 1–6 balls bounce in a
rectangle; wall hits emit MIDI from per-ball note strips. Rectangle-only geometry, utility-grade.
Source: https://www.kvraudio.com/product/ballsequencer-by-uplandtoys

**Gravity Pack** — LDM Design. Max for Live MIDI delays whose repeat timing follows bouncing-ball
kinematics (contracting/expanding intervals). Physics as a timing curve only — no simulated space,
no collisions. Included as evidence that "bouncing-ball time" is a recognized musical gesture.
Source: https://isotonikstudios.com/product/gravity-pack/

## 2. Lineage (art/web archetype)

**BallDroppings** — Josh Nimoy, 2003; C++ original, later openFrameworks/Processing/JS ports;
source on GitHub under a Creative Commons license. The archetype of Bounce's interaction: balls
fall from an emitter and bounce off user-drawn *straight line segments*, each impact sounding a
note with pitch tied to impact speed. Player feedback across ports records the core frustration
Bounce's C-003 addresses: users could not choose the mapping (pitch followed ball speed, not a
user-controlled property), making intentional composition nearly impossible. Physics is a simple
fixed-step integrator over line segments.
Sources: https://github.com/jtnimoy/BallDroppings ·
https://inverted-audio.com/visual/balldroppings/ · https://acid-play.com/download/balldroppings

## 3. What the landscape establishes

1. The interaction concept (bouncing bodies → notes) is established and commercially alive from
   2003 (BallDroppings) through 2026 (Musyc2). Bounce is not proposing a novel *interaction*.
2. Every surveyed system computes physics with a game-style fixed-timestep integrator over
   discrete geometry (segments, boxes, piano-roll rows, polygon shapes). None advertises exact
   analytic collision solving, and none makes any of Bounce's three product guarantees:
   bit-identical preset replay, zero-drift periodic orbits, sample-accurate collision→MIDI timing.
   Determinism is nowhere a marketed property; randomness is typically a *feature*.
3. Curved, user-shaped *mathematical* surfaces are absent: the surveyed geometry vocabulary is
   segments, bars, rectangles, polygons, and note grids.
4. Platform/product gap: the closest neighbors are iOS AUv3 apps (BounceBud, Musyc2) or Max for
   Live devices (Bouncy Notes, Gravity Pack); the desktop entries are closed-source (Droplets) or
   rectangle-toy freeware (BallSequencer). No FOSS, curve-based, deterministic VST3 exists in the
   surveyed field.
5. Design lesson for Phase 2 (recorded, not decided): two independent products converge on
   correcting or constraining raw physics timing toward musical grids (Droplets' quantize;
   scale/key constraints in BounceBud/Bouncy Notes). Bounce's periodic-orbit + user-shaped-curve
   bet is a different answer to the same musicality problem; the mapping engine (C-003) should
   treat mapping configurability as first-class — the oldest recorded user complaint in this
   lineage (BallDroppings) is a hardwired mapping.

## 4. What Bounce does differently (claim of record)

Exactness as the product: closed-form ballistic flight between events; collision instants found by
root-solving on the true curve equation (never a polyline approximation); deterministic event
ordering with versioned tie-breaking; therefore bit-identical replay, drift-free periodic orbits,
and sample-accurate MIDI as *gated guarantees* (PROJECT §8), delivered as a GPLv3 JUCE VST3 with
live visual interface. The Law-7 baseline (naive fixed-timestep + polyline engine) is precisely
the architecture the entire surveyed field uses — beating it at matched compute is the program's
central verifiable claim.

## 5. Residual risks the landscape does not settle

- No surveyed source demonstrates that analytic root-solving for multi-ball scenes fits the
  real-time audio budget — that is exactly Phase 1's `realtime_budget` gate, not assumable.
- Grazing/tangential collision handling is not discussed anywhere in the surveyed field; it
  remains the named domain risk of PROJECT §9(a), to be settled in deliverable (b).
