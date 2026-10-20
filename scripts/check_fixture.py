#!/usr/bin/env python3
"""Check a MatamStory sample against the coursework's output-diff rules."""

import pathlib
import subprocess
import sys


def normalized(text: str) -> list[str]:
    # Match diff --strip-trailing-cr -B -Z: disregard CR, blank lines
    # and whitespace at the end of each line; preserve other whitespace.
    return [
        line.rstrip()
        for line in text.replace("\r\n", "\n").replace("\r", "\n").split("\n")
        if line.strip()
    ]


def main() -> int:
    if len(sys.argv) != 6:
        print(
            "Usage: check_fixture.py <executable> <events> <players> "
            "<expected_output> <expected_exit_code>",
            file=sys.stderr,
        )
        return 2

    executable, events, players, expected_path, expected_code = sys.argv[1:]
    try:
        result = subprocess.run(
            [executable, events, players],
            capture_output=True,
            text=True,
            check=False,
            timeout=10,
        )
    except subprocess.TimeoutExpired:
        print("FAIL: game did not terminate within 10 seconds", file=sys.stderr)
        return 1

    actual = result.stdout + result.stderr
    expected = pathlib.Path(expected_path).read_text(encoding="utf-8")
    if result.returncode != int(expected_code):
        print(
            f"FAIL: exit code {result.returncode} != {expected_code}",
            file=sys.stderr,
        )
        print(actual, file=sys.stderr)
        return 1
    if normalized(actual) != normalized(expected):
        import difflib

        print("FAIL: output differs from expected fixture", file=sys.stderr)
        for line in difflib.unified_diff(
            normalized(expected),
            normalized(actual),
            fromfile="expected",
            tofile="actual",
            lineterm="",
        ):
            print(line, file=sys.stderr)
        return 1

    print(f"PASS: {pathlib.Path(expected_path).name}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
