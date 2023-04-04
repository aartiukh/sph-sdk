EPSILON = 10e-8
SEARCH_RADIUS = 0.2
FIELD_SIZE = 1.0
CUBES_IN_ROW = int(FIELD_SIZE / SEARCH_RADIUS)


def squared_norm(point_1, point_2):
    squares_sum = 0
    for axis in range(len(point_1)):
        squares_sum += (point_1[axis] - point_2[axis])**2
    return squares_sum


def find_points_cubes(points: list, search_radius: float, field_size: float) -> list[list]:
    number_cubes_in_row = int(field_size / search_radius)
    cube_indexes = [[] for cube in range(number_cubes_in_row ** 2)]

    for point_index, point in enumerate(points):
        col = point[0] // search_radius
        row = point[1] // search_radius
        cube_id = int(row * number_cubes_in_row + col)
        cube_indexes[cube_id].append(point_index)

    return cube_indexes


def _find_one_cube_neighbors(cube_id: int, cubes_in_row: int) -> list[int]:
    col = cube_id % cubes_in_row
    row = cube_id // cubes_in_row
    possible_neighbors = [
        (row, col + 1),
        (row, col - 1),
        (row + 1, col),
        (row - 1, col),
        (row + 1, col + 1),
        (row - 1, col + 1),
        (row + 1, col - 1),
        (row - 1, col - 1),
    ]
    cube_neighbors_ids = [row * cubes_in_row + col for row, col in possible_neighbors if (0 <= col < cubes_in_row)
                                                                                      and (0 <= row < cubes_in_row)]

    return cube_neighbors_ids


def _find_neighbor_cubes(search_radius: float, field_size: float) -> list[list]:
    number_cubes_in_row = int(field_size / search_radius)
    cubes_neighbors_ids = [_find_one_cube_neighbors(cube_id, number_cubes_in_row)
                           for cube_id in range(number_cubes_in_row ** 2)]
    return cubes_neighbors_ids


def search_neighbor_cubes(points, search_radius, cube_ids, cube_neighbors) -> list[list]:
    neighbors = [[] for i in range(len(points))]
    for cube_id, cube_points_ids in enumerate(cube_ids):
        current_neighbors = cube_neighbors[cube_id]
        for neighbor_cube_id in current_neighbors:
            if neighbor_cube_id >= cube_id:
                neighbor_cube_points = cube_ids[neighbor_cube_id]

                for cube_point_id in cube_points_ids:
                    for neighbor_point_id in neighbor_cube_points:
                        dist = squared_norm(points[cube_point_id], points[neighbor_point_id])
                        if dist - search_radius ** 2 < EPSILON:
                            neighbors[cube_point_id].append(neighbor_point_id)
                            neighbors[neighbor_point_id].append(cube_point_id)

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

    print(f"POINTS:\n{xy}")

    cubes = find_points_cubes(points=xy, search_radius=SEARCH_RADIUS, field_size=FIELD_SIZE)
    print("CUBES:\n", cubes)

    cube_nb = _find_neighbor_cubes(search_radius=SEARCH_RADIUS, field_size=FIELD_SIZE)
    for cube_id, nb in enumerate(cube_nb):
        print(f"CUBE ID: {cube_id} CUBE NEIGHBORS: {nb}")

    print(cube_nb)

    points_nb = search_neighbor_cubes(xy, SEARCH_RADIUS, cubes, cube_nb)
    print("POINT NEIGHBORS:\n", points_nb)

    print("Correct neighbors:\n", correct_neighbors)
