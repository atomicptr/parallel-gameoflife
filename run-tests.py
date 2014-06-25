import subprocess
import sys

def main():
    args = sys.argv[1:]

    if len(args) is not 3:
        print("ERR: use command like this: \n\tpython run-tests.py filename.txt generations num_threads")
        sys.exit()

    filename = args[0]
    generations = args[1]
    num_threads = args[2]

    for i in range(1, int(num_threads) + 1):
        p = subprocess.Popen(["./gameoflife", filename, generations, str(i)])
        print("\n>>> Thread #%s started\n" % (i))
        p.communicate()

if __name__ == "__main__":
    main()
