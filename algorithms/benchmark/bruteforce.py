from dist_sqr import dist_sqr

EPSILON = 10e-8
SEARCH_RADIUS = 0.2


def bruteforce(points: list, search_radius: float) -> dict:
    """

    :param points: 2D np.ndarray of kind [[p0x, p0y], [p1x, p1y]]
    :param search_radius: float, minimal radius to become neighbors
    :return: dict of kind {point0_index: [neighbor1_index, neighbor2_index]}
    """
    shape = (len(points), len(points[0]))
    neighbors = {i: [] for i in range(shape[0])}

    for i in range(shape[0]):
        for j in range(shape[0]):
            if i == j:
                continue

            dist = dist_sqr(points[i], points[j])

            if dist - search_radius ** 2 < EPSILON:
                neighbors[i].append(j)

    return neighbors


def optimized_bruteforce(points: list, search_radius: float) -> dict:
    """

    :param points: 2D np.ndarray of kind [[p0x, p0y], [p1x, p1y]]
    :param search_radius: float, minimal radius to become neighbors
    :return: dict of kind {point0_index: [neighbor1_index, neighbor2_index]}
    """
    shape = (len(points), len(points[0]))
    neighbors = {i: [] for i in range(shape[0])}

    for i in range(shape[0]):
        for j in range(i + 1, shape[0]):
            dist = dist_sqr(points[i], points[j])

            if dist - search_radius ** 2 < EPSILON:
                neighbors[i].append(j)
                neighbors[j].append(i)

    return neighbors


if __name__ == '__main__':
    xy = [
        [0.18, 0.2],
        [0.35, 0.15],
        [0.4, 0.1]
    ]

    correct_neighbors = {0: [1],
                         1: [2, 0],
                         2: [1]
                         }

    correct_neighbors = {k: sorted(v) for k, v in correct_neighbors.items()}

    print("Search radius: ", SEARCH_RADIUS)
    print("Points:\n", xy)

    found_nb = bruteforce(points=xy, search_radius=SEARCH_RADIUS)

    print("Found neighbors:\n", found_nb)

    print("Correct neighbors:\n", correct_neighbors)

    print("Found neighbors are correct: ", correct_neighbors == found_nb)
