

import cv2
import numpy as np

HEIGHT = 103
WIDTH = 101
def render(map: dict, t: int):
    #greyscale black and white image
    img = np.zeros((HEIGHT, WIDTH, 3), dtype=np.uint8)
    
    count = 0
    connect_map = {}
    for item in map:
        img[map[item][1], map[item][0]] = 255
        connect_map[(map[item][0], map[item][1])] = 1
    
    for item in connect_map:
        x = item[0]
        y = item[1]
        if (x, y + 1) in connect_map:
            count += 1
        elif (x, y - 1) in connect_map:
            count += 1
        elif (x + 1, y) in connect_map:
            count += 1
        elif (x - 1, y) in connect_map:
            count += 1
    if count > 100:
        # Paint the black canvas red
        img[np.all(img == [0, 0, 0], axis=-1)] = [0, 0, 255]    
        
    cv2.imwrite(f'./imgs/img{t}.png', img)

def safety_factor():
    with open("./input", "r") as file:
        lines = file.readlines()
    positions = {}
    robots = []
    index = 0
    for line in lines:
        line = line.strip()
        if not line:
            continue

        # Parse position and velocity strings
        s_pos = line.find(' ')
        p_string = line[:s_pos]
        v_string = line[s_pos + 1:]

        c_pos_p = p_string.find(',')
        c_pos_v = v_string.find(',')

        # Extract x, y, vx, vy
        x = int(p_string[2:c_pos_p])
        y = int(p_string[c_pos_p + 1:])
        vx = int(v_string[2:c_pos_v])
        vy = int(v_string[c_pos_v + 1:])

        positions[index] = (x, y)
        robots.append((vx, vy))
        index+= 1
    render(positions, 0)

    test = {}
    idx =0
    for i in range(50):
        for j in range(3):
            test[idx] = (i,j)
            idx += 1
    render(test, -2)

    for t in range(1, 10000):
        print(t)
        newmap = {}
        for item in positions:
            x = positions[item][0]
            y = positions[item][1]
            x = (x + robots[item][0] + WIDTH) % WIDTH
            y = (y + robots[item][1] + HEIGHT) % HEIGHT
            newmap[item] = (x, y)
        positions = newmap
        render(positions, t)
    ans = 0
    return ans

if __name__ == "__main__":
    safety_factor_value = safety_factor()
    print(safety_factor_value)