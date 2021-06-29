#!/usr/bin/env python3
import subprocess
import argparse
import sys


name = "./name"
hyphenate = "./hyphenate"
parse = "./parse"


def generate_line(base):
    cmd = lambda *x: subprocess.check_output(x).decode("utf-8").strip()
    gname = cmd(name, str(base))
    ghyphen = cmd(hyphenate, gname)
    gparse = cmd(parse, gname)
    return gname, ghyphen, gparse


def is_erroneous(base, gname, ghyphen, gparse):
    return str(base) != gparse or ghyphen.startswith("Could not")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Generate the names for a range of bases.")
    parser.add_argument("--start", "-s", type=int, default=0,
        help="Start of the range")
    parser.add_argument("--end", "-e", type=int, default=10,
        help="End of the range (inclusive)")
    parser.add_argument("--only-errors", "-o", action="store_true",
        help="Only print erroneous results")
    parser.add_argument("--update-interval", "-u", type=int, default=100,
        help="How often to update the progress number, 0 to disable")
    args = parser.parse_args()

    errors = 0

    # initial newline to prevent the progress from overwriting text
    if args.update_interval:
        print(file=sys.stderr)

    for i in range(args.start, args.end + 1):
        v = generate_line(i)
        is_error = is_erroneous(i, *v)
        errors += int(is_error)
        if (args.only_errors and is_error) or not args.only_errors:
            print("{}\t{}\t{}\t{}".format(i, *v))

        if args.update_interval and i % args.update_interval == 0:
            print(f"\033[F{i} ({i / args.end * 100:.2f}%)", file=sys.stderr)

    print(f"Checked {args.end + 1} bases, with {errors} errors"
           + f" ({errors / (args.end + 1) * 100:.2f}% erroneous)", file=sys.stderr)
