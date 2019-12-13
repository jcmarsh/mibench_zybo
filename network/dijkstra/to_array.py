import sys

# Read input.dat from the dijkstra benchmark, print out as int array in a c header

if len(sys.argv) < 2:
    print("Usaged: python3 to_array.py <input.dat>")
    exit()

input_file = open(sys.argv[1], "rt")

# print c header start stuff...
print("// This file is generated by to_array.py : " + sys.argv[1] + "\n")
print("#define NUM_NODES 100")
print("int AdjMatrix[NUM_NODES][NUM_NODES] = {")

# Read / output each line
for line in input_file.readlines():
    outstring = "    { "
    for value in line.strip().split():
        outstring += value + ", "
    outstring = outstring[:-2] # cut off last two chars ", "
    outstring += "},"
    print(outstring)
print("};")