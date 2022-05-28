#!/usr/bin/python3

import sys
from pathlib import Path


def eprint(*args, **kwargs):
    print(*args, file=sys.stderr, **kwargs)


SAMPLE_IGNORE_LIST = [
    # Allow all apps to use '-' since they may be command line utilities
    "samples/apps/*"
]

CHECKED_FILE_EXTENSIONS = [ "jakt", "out", "error" ]

REPO_BASE = Path(__file__).resolve().parent.parent


def warn_about_samples_with_dashes(bases):
    bad_samples = set()

    def remove_repo_base(path):
        return path.relative_to(REPO_BASE)

    for base in bases:
        base = (REPO_BASE / base)
        for ext in CHECKED_FILE_EXTENSIONS:
            bad_samples.update(map(remove_repo_base, base.rglob(f'*-*.{ext}')))

    for ignored in map(lambda glob: REPO_BASE.rglob(glob),SAMPLE_IGNORE_LIST):
        bad_samples -= set(map(remove_repo_base, ignored))

    has_bad_samples = len(bad_samples) > 0
    if has_bad_samples:
        eprint("Some of your samples contain a dash (-) in their filename, please consider replacing with an underscore (_)")
        eprint("If you want to disable this check for your file add it to the SAMPLE_INGORE_LIST in meta/lint_samples.py")
        eprint()
        eprint("| --------------------------------------------- Bad files --------------------------------------------- |")
        for path in bad_samples:
            eprint(f"| > \033[1m{str(path)}\033[0m")

    return has_bad_samples


def main() -> int:
    return 1 if warn_about_samples_with_dashes(["tests", "samples"]) else 0


if __name__ == "__main__":
    sys.exit(main())
