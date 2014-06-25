import sys

def main():
    args = sys.argv[1:]

    if len(args) is not 3:
        print("Please use command like this:\npython create-field.py filename.txt width height")
        sys.exit(1)

    filename = args[0]
    width = int(args[1])
    height = int(args[2])

    file = open(filename, "w+")

    for y in range(0, height):
        for x in range(0, width):
            file.write("0 ")
        file.write("\n")

    file.close()

if __name__ == "__main__":
    main()
