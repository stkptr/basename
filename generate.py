#!/usr/bin/env python3
import subprocess
import argparse


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
    args = parser.parse_args()

    for i in range(args.start, args.end + 1):
        v = generate_line(i)
        if (args.only_errors and is_erroneous(i, *v)) or not args.only_errors:
            print("{}\t{}\t{}\t{}".format(i, *v))
