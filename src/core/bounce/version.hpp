// SPDX-License-Identifier: GPL-3.0-only
// bounce-core — versioned identity of the engine and its ordering/contact rules.
// Authority: DELIVERABLE_B §3 (G-1/S-1), §5 (TB-1); PROJECT §9(c) (presets replay
// per engine version; rule changes are version bumps, never silent).
#pragma once

namespace bounce::core {

// Semantic version of bounce-core. Bumped by PM packet only.
const char* engine_version();

// Event-ordering tie-break rule version (DELIVERABLE_B §5).
const char* tie_break_version();

// Grazing / settle (Zeno-guard) contact rule versions (DELIVERABLE_B §3).
const char* contact_rule_version();

} // namespace bounce::core
