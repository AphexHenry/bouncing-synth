#!/usr/bin/env python3
"""Exact reference-number parsing and comparison helpers for gate checkers."""
from __future__ import annotations

from decimal import Decimal, InvalidOperation
from fractions import Fraction
from typing import Any

TOL_T: Fraction = Fraction(1, 10**9)
TOL_S: Fraction = Fraction(1, 10**9)


def parse_reference_number(text: str) -> Fraction:
    """Parse a reference numeric string exactly into a rational."""
    raw = text.strip()
    if not raw:
        raise ValueError("empty numeric string")

    lower = raw.lower()
    if "/" in raw and not lower.startswith(("0x", "-0x", "+0x")):
        left, right = raw.split("/", 1)
        return Fraction(int(left.strip()), int(right.strip()))

    if lower.startswith(("0x", "-0x", "+0x")):
        value = float.fromhex(raw)
        return Fraction(*value.as_integer_ratio())

    try:
        return Fraction(Decimal(raw))
    except InvalidOperation as exc:
        raise ValueError(f"cannot parse reference number: {raw!r}") from exc


def engine_event_fraction(event: dict[str, Any], value_key: str, hex_key: str) -> Fraction:
    """Read an engine event field as the exact binary64 value it denotes."""
    if hex_key in event:
        value = float.fromhex(str(event[hex_key]))
        return Fraction(*value.as_integer_ratio())
    if value_key in event:
        value = float(event[value_key])
        return Fraction(*value.as_integer_ratio())
    if value_key == "s":
        contact = event.get("contact", {})
        if "x" in contact:
            value = float(contact["x"])
            return Fraction(*value.as_integer_ratio())
    return Fraction(0)


def compare_event_deltas(ref: dict[str, Any], event: dict[str, Any]) -> tuple[Fraction, Fraction]:
    """Return exact |Δt| and |Δs| between one reference event and one engine event."""
    rt = parse_reference_number(str(ref["t"]))
    et = engine_event_fraction(event, "t", "t_hex")
    rs = parse_reference_number(str(ref["contact"]["x"]))
    es = engine_event_fraction(event, "s", "s_hex")
    return abs(et - rt), abs(es - rs)
