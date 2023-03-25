import numpy as np

EPSILON = 10e-8


def bruteforce_neighbors_search(points: np.ndarray, search_radius: float) -> dict:
    """

    :param points: 2D np.ndarray of kind [[p0x, p0y], [p1x, p1y]]
    :param search_radius: float, minimal radius to become neighbors
    :return: dict of kind {point0_index: [neighbor1_index, neighbor2_index]}
    """
    neighbors = {i: [] for i in range(xy.shape[0])}

    for i in range(points.shape[0]):
        for j in range(i + 1, points.shape[0]):
            dist = np.linalg.norm(points[i] - points[j])

            if dist - search_radius < EPSILON:
                neighbors[i].append(j)
                neighbors[j].append(i)

    return neighbors


if __name__ == '__main__':
    # three points:
    # p0 = (0.1, 0.2),
    # p1 = (0.2, 0.2),
    # p2 = (0.3, 0.2)
    # search_radius = 0.15
    # Euclidian distance:
    # p0-p1 = 0.1 < search_radius -> neighbors
    # p0-p2 = 0.2 > search_radius
    # p1-p2 = 0.1 < search_radius -> neighbors
    # neighbors:
    # p0: p1,
    # p1: p0, p2
    # p2: p1

    search_radius = 0.15
    xy = np.array([[0.1, 0.2],
                   [0.2, 0.2],
                   [0.3, 0.2]])

    correct_neighbors = {0: [1],
                         1: [0, 2],
                         2: [1]
                         }

    print("Search radius: ", search_radius)
    print("Points:\n", xy)

    found_nb = bruteforce_neighbors_search(points=xy, search_radius=search_radius)

    print("Neighbors:\n", found_nb)

    print("Found neighbors are correct: ", correct_neighbors == found_nb)
