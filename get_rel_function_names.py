import os
import sys

if len(sys.argv) != 2:
    print("Usage: python script.py <file_path>")
    sys.exit(1)

file_path = sys.argv[1]
lines_starting_with_fn = ""

with open(file_path, 'r') as file:
    for line in file:
        # Remove leading and trailing whitespaces
        line = line.strip()

        if line.startswith(".fn fn_"):
            # Remove ".fn " from the beginning of the line
            line = line[len(".fn "):]

            # Remove ", global" from the end of the line
            line = line.rstrip(', global')

            lines_starting_with_fn += "// " + line + '\n\n'

print(lines_starting_with_fn)
