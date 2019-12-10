#!/usr/bin/python3

import sys


if len(sys.argv) != 2 :
    print("Usage log-to-cvs.py INPUT")
    exit(1)

log_file = open(sys.argv[1])


error = ""
file_name = ""
ln = "";
col = "";
func = ""
desc = ""

first_error = False

for line in log_file:
    if not first_error and not line.startswith("ERROR"):
        continue
    else:
        first_error = True

    if line.startswith("ERROR"):
        error = line
        file_name = ""
        ln = "";
        col = "";
        func = ""
        desc = ""
    elif line.startswith("---------------"):
        print('"{}","{}","{}",{},{},"{}"'.format(error.rstrip(),
                                         file_name.rstrip(),
                                         func.rstrip(),
                                         ln.rstrip(),
                                         col.rstrip(),
                                         desc.rstrip()))
        first_error = False
    elif line.startswith("File: "):
        file_name = line[len("File: "):]
    elif line.startswith("Line: "):
        ln = line[len("Line: "):]
    elif line.startswith("Col : "):
        col = line[len("Col : "):]
    elif line.startswith("Func: "):
        func = line[len("Func: "):]
    else:
        desc += line
