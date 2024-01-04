import struct
from glob import iglob
from os import path

PLAYER = 0
PATH = 1
EMPTY = 2
WALL = 3
BOX = 4
GOAL = 5
FILL = 6
sI = struct.Struct("@ I")   # unsigned int, 4 bytes

PLAYER_C = "*"
PATH_C = EMPTY_C = " "
WALL_C = "/"
BOX_C = "#"
GOAL_C = "O"
FILL_C = "$"
lsc = [PLAYER_C, PATH_C, EMPTY_C, WALL_C, BOX_C, GOAL_C, FILL_C]
sc = struct.Struct("@ c")


def txt_to_bin(txt_file, bin_file):
    with open(txt_file, "r", encoding="utf-8") as f:
        map_ = [list(l)[:-1] for l in f]

    cnt = 0
    size_x, size_y = len(map_), max(len(l) for l in map_)
    bin_map = [[sc.pack(bytes((EMPTY,))) for y in range(size_y)] for x in range(size_x)]

    for x in range(size_x):
        y = 0
        while map_[x][y] == EMPTY_C and y < len(map_[x]):
            bin_map[x][y] = sc.pack(bytes((EMPTY,)))
            y += 1
        while y < len(map_[x]):
            index = lsc.index(map_[x][y])
            val = sc.pack(bytes((index,)))
            bin_map[x][y] = val
            y += 1
        y -= 1
        while y >= 0 and map_[x][y] == PATH:
            bin_map[x][y] = sc.pack(bytes((EMPTY,)))
            y -= 1

    with open(bin_file, "wb") as f:
        cnt += f.write(sI.pack(size_x))
        cnt += f.write(sI.pack(size_y))
        for x in range(size_x):
            for y in range(size_y):
                cnt += f.write(bin_map[x][y])

    return cnt


def bin_to_txt(bin_file, txt_file):
    with open(bin_file, "rb") as f:
        size_x, = sI.unpack(f.read(sI.size))
        size_y, = sI.unpack(f.read(sI.size))
        map_ = [[EMPTY_C for _ in range(size_y)] for _ in range(size_x)]

        c, = sc.unpack(f.read(sc.size))
        c = c[0]
        for x in range(size_x):
            y = 0
            while c == EMPTY and y < size_y:
                map_[x][y] = EMPTY_C
                val = f.read(sc.size)
                if val:
                    c, = sc.unpack(val)
                    c = c[0]
                    y += 1
                else:
                    break
            while y < size_y:
                map_[x][y] = lsc[c]
                val = f.read(sc.size)
                if val:
                    c, = sc.unpack(val)
                    c = c[0]
                    y += 1
                else:
                    break

    cnt = 0
    if txt_file is None:
        print(bin_file, size_x, size_y)
        print(*("".join(l) for l in map_), sep="\n")
    else:
        with open(txt_file, "w", encoding="utf-8") as f:
            for l in map_:
                cnt += f.write("".join(l))
                cnt += f.write("\n")

    return cnt


if __name__ == "__main__":
    # tmp = []
    # i = input("txt:")
    # o = input("bin:")
    # while o:
    #     print(txt_to_bin(i, o))
    #     tmp.append((i, o))
    #     i = input("txt:")
    #     o = input("bin:")
    # for o, i in tmp:
    #     print(bin_to_txt(i, None))
    for file in iglob("*.txt"):
        new_file = path.splitext(file)[0] + ".bin"
        print(txt_to_bin(file, new_file))
        print(bin_to_txt(new_file, None))
