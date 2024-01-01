from z3 import *
from parse import *

inputs = [
    # ([19, 13, 30], [-2,  1, -2]),
    # ([18, 19, 22], [-1, -1, -2]),
    # ([20, 25, 34], [-2, -2, -4]),
    # ([12, 31, 28], [-1, -2, -1]),
    # ([20, 19, 15], [ 1, -5, -3]),
    # ([232488932265751, 93844132799095, 203172424390144], [64, 273, 119]),
    # ([258285813391475, 225317967801013, 306162724914014], [14, -10, -22]),
    # ([377519381672953, 343737262245611, 485395777725108], [-182, -80, -373]),
]

def part_1(inputs):
    ans = 0
    BOX_MIN = 200000000000000
    BOX_MAX = 400000000000000
    s = Solver()
    for i in range(len(inputs)):
        for j in range(i + 1, len(inputs)):
            s.reset()
            t = Real('t')
            u = Real('u')
            s.add(t >= 0)
            s.add(u >= 0)
            for d in range(0, 2):
                s.add(inputs[i][0][d] + t * inputs[i][1][d] == inputs[j][0][d] + u * inputs[j][1][d])
                s.add(BOX_MIN <= inputs[i][0][d] + t * inputs[i][1][d])
                s.add(inputs[i][0][d] + t * inputs[i][1][d] <= BOX_MAX)

            if s.check() != sat:
                continue
            # m = s.model()
            # t = m[t].as_fraction()
            # u = m[u].as_fraction()
            # if t <= 0 or u <= 0:
            #     continue
            # x = inputs[i][0][0] + t * inputs[i][1][0]
            # if x < BOX_MIN or x > BOX_MAX:
            #     continue
            # y = inputs[i][0][1] + t * inputs[i][1][1]
            # if y < BOX_MIN or y > BOX_MAX:
            #     continue
            ans += 1
            # print(ans)
    return ans

def part_2(inputs):
    sx = Real('sx')
    sy = Real('sy')
    sz = Real('sz')
    dx = Real('dx')
    dy = Real('dy')
    dz = Real('dz')

    s = Solver()

    for i in range(len(inputs)):
        t = Real(f't{i}')
        s.add(sx + t * dx == inputs[i][0][0] + t * inputs[i][1][0])
        s.add(sy + t * dy == inputs[i][0][1] + t * inputs[i][1][1])
        s.add(sz + t * dz == inputs[i][0][2] + t * inputs[i][1][2])
        s.add(t >= 0)

    assert(s.check() == sat)
    m = s.model()
    # print(f"{m[sx]} {m[sy]} {m[sz]} @ {m[dx]} {m[dy]} {m[dz]}")

    ans = 0
    for item in [sx, sy, sz]:
        assert(m[item].denominator_as_long() == 1)
        ans += m[item].numerator_as_long()
    return ans

if __name__ == "__main__":
    with open('input.txt', 'r') as file:
        for line in file:
            p = parse("{}, {}, {} @ {}, {}, {}", line)
            inputs.append(([int(p[0]), int(p[1]), int(p[2])],
                        [int(p[3]), int(p[4]), int(p[5])]))

    # print(part_1(inputs))
    print(part_2(inputs))
