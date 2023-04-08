from dist_sqr import dist_sqr


def bruteforce(points: list[list], search_radius: float, epsilon: float) -> list[list]:
    """

    :param points: 2D list of kind [[p0x, p0y], [p1x, p1y]]
    :param search_radius: float, minimal radius to become neighbors
    :param epsilon: precision for neighbors computation
    :return: list of kind [[neighbor1_index, neighbor2_index]]
    """
    points_number = len(points)
    neighbors = [[] for i in range(points_number)]

    for i in range(points_number):
        for j in range(points_number):
            if i == j:
                continue

            dist = dist_sqr(points[i], points[j])

            if dist - search_radius ** 2 < epsilon:
                neighbors[i].append(j)

    return neighbors


def optimized_bruteforce(points: list[list], search_radius: float, epsilon: float) -> list[list]:
    """

    :param points: 2D list of kind [[p0x, p0y], [p1x, p1y]]
    :param search_radius: float, minimal radius to become neighbors
    :param epsilon: precision for neighbors computation
    :return: list of kind [[neighbor1_index, neighbor2_index]]
    """
    points_number = len(points)
    neighbors = [[] for i in range(points_number)]

    for i in range(points_number):
        for j in range(i + 1, points_number):
            dist = dist_sqr(points[i], points[j])

            if dist - search_radius ** 2 < epsilon:
                neighbors[i].append(j)
                neighbors[j].append(i)

    return neighbors
