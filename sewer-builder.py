
import json
import math
from vectors import *


distance_on_line = 5.0



def dist_to_line(x1,y1, x2,y2, x3,y3): # x3,y3 is the point
    px = x2-x1
    py = y2-y1

    something = px*px + py*py

    u =  ((x3 - x1) * px + (y3 - y1) * py) / float(something)

    if u > 1:
        u = 1
    elif u < 0:
        u = 0

    x = x1 + u * px
    y = y1 + u * py

    dx = x - x3
    dy = y - y3

    # Note: If the actual distance does not matter,
    # if you only want to compare what this function
    # returns to other results of this function, you
    # can just return the squared distance instead
    # (i.e. remove the sqrt) to gain a little performance

    dist = math.sqrt(dx*dx + dy*dy)

    return dist


def ntuples(lst, n):
    return zip(*[lst[i:]+lst[:i] for i in range(n)])


def main():
    with open("world_nodes.json", "r") as f:
        nodes = json.loads(f.read())["features"]

    with open("Centerlines.json", "r") as f:
        lines = json.loads(f.read())["features"]


    l = len(lines)


    for i, line_string in enumerate(lines):

        # print("%d, %d" % (l, i))
        line_points = line_string["geometry"]["coordinates"]

        # iterate through centerline points in pairs
        for line in list(ntuples(line_points, 2))[:-1]:

            ax = line[0][0]
            ay = line[0][1]
            bx = line[1][0]
            by = line[1][1]

            # skip lines that go outside of our bounds

            if((ax < 1396527) or (bx > 1402226)):
                continue
            if((bx < 1396527) or (bx > 1402226)):
                continue
            if((ay < 1150970) or (by > 1156770)):
                continue
            if((by < 1150970) or (by > 1156770)):
                continue

            nodes_on_line = []

            for node in nodes:
                node = node["geometry"]["coordinates"]
                dist = dist_to_line(line[0][0], line[0][1], line[1][0], line[1][1], node[0], node[1])

                if(dist <= distance_on_line):
                    nodes_on_line.append(node)








if __name__ == "__main__":
    main()
