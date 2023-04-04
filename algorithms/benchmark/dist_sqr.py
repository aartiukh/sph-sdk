def dist_sqr(point_1: list[float], point_2: list[float]) -> float:
    squares_sum = 0
    for axis in range(len(point_1)):
        squares_sum += (point_1[axis] - point_2[axis])**2
    return squares_sum
