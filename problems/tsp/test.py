#!/usr/bin/python
# -*- coding: utf-8 -*-

import argparse, subprocess, glob, os, time, json

def make_output_directory(algo):
    try:
        os.makedirs("outputs/%s" % algo.lower())
    except OSError:
        pass

def get_output_path(algo, input_file):
    return "outputs/%s/%s" % (algo.lower(),
            os.path.basename(input_file).replace("inp", "outp"))

def run_with_time_limit(command_line, time_limit):
    start = time.time()
    process = subprocess.Popen(command_line)
    while True:
        now = time.time()
        if process.poll() != None or now > start + time_limit: break
        time.sleep(0.01)
    if process.returncode == None:
        process.kill()
        process.communicate()
        return None
    return now - start

def test_with(executable, time_limit, input_files):
    make_output_directory(executable)
    print "Testing", executable
    entry = {}
    for input_file in input_files:
        output_file = get_output_path(executable, input_file)
        runtime = run_with_time_limit([executable,
            input_file, output_file],
            time_limit)
        if runtime == None:
            runtime = "TLE"
            print "Time limit exceeded for %s." % input_file
        else:
            res = open(output_file).read().strip()
            print "Solved %s within %g seconds." % (input_file, runtime)
        entry[input_file] = runtime
        if runtime == "TLE": break
    return entry

def print_report(input_files, algos, report):
    max_len = max(map(len, algos))
    disp = map(os.path.basename, input_files)
    print "|".join([" "*max_len] + disp)
    for algo in algos:
        elems = [("%-" + str(max_len) + "s") % algo]
        for input_file, displayed in zip(input_files, disp):
            data = report[algo].get(input_file, "")
            if isinstance(data, float):
                data = "%.2lf" % data
            elems.append(("%-" + str(len(disp)) + "s") % data)
        print "|".join(elems)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("executables", nargs="+")
    parser.add_argument("-t", "--time-limit", default=10.0, type=float)
    args = parser.parse_args()

    log_entry = {}
    input_files = list(sorted(glob.glob("inputs/*.txt")))
    for exe in args.executables:
        log_entry[exe] = test_with(exe, args.time_limit, input_files)
    print_report(input_files, args.executables, log_entry)

if __name__ == "__main__":
    main()
