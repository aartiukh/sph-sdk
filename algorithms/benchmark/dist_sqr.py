def dist_sqr(point_1: list[float], point_2: list[float]) -> float:
    """
    Calculates square of Euclidian distance for two points.
    :param point_1: first point of kind list[float]
    :param point_2: second point of kind list[float]
    :return: float
    """
    squares_sum = 0
    for axis, _ in enumerate(point_1):
        squares_sum += (point_1[axis] - point_2[axis]) ** 2
    return squares_sum
