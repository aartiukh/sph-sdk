import numpy as np

EPSILON = 10e-8
SEARCH_RADIUS = 0.2
FIELD_SIZE = 1.0
CUBES_IN_ROW = int(FIELD_SIZE / SEARCH_RADIUS)


def find_points_cubes(points: list, search_radius: float, field_size: float) -> list[list]:
    # cols = points[:, 0] // search_radius
    # rows = points[:, 1] // search_radius
    # cube_size = field_size / search_radius
    # cube_ids = rows * cube_size + cols
    # cube_ids = cube_ids.astype(int)
    number_cubes_in_row = int(field_size / search_radius)
    cube_indexes = [[] for cube in range(number_cubes_in_row ** 2)]

    for point_index, point in enumerate(points):
        col = point[0] // search_radius
        row = point[1] // search_radius
        cube_id = int(row * number_cubes_in_row + col)
        cube_indexes[cube_id].append(point_index)

    return cube_indexes


def _find_one_cube_neighbors(cube_id: int, cubes_in_row: int) -> list[int]:
    if cube_id % cubes_in_row == 0:
        possible_neighbors = [
            cube_id + 1,
            cube_id - cubes_in_row,
            cube_id + cubes_in_row,
            cube_id + cubes_in_row + 1,
            cube_id - cubes_in_row + 1
        ]
    elif cube_id % cubes_in_row == (cubes_in_row - 1):
        possible_neighbors = [
            cube_id - 1,
            cube_id - cubes_in_row,
            cube_id + cubes_in_row,
            cube_id + cubes_in_row - 1,
            cube_id - cubes_in_row - 1
        ]
    else:
        possible_neighbors = [
            cube_id - 1,
            cube_id + 1,
            cube_id - cubes_in_row,
            cube_id + cubes_in_row,
            cube_id + cubes_in_row - 1,
            cube_id + cubes_in_row + 1,
            cube_id - cubes_in_row - 1,
            cube_id - cubes_in_row + 1
        ]
    cube_neighbors_ids = [neighbor_id for neighbor_id in possible_neighbors if (0 <= neighbor_id < cubes_in_row ** 2)]
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
                print(cube_points_ids)
                neighbor_cube_points = cube_ids[neighbor_cube_id]

                for cube_point_id in cube_points_ids:
                    for neighbor_point_id in neighbor_cube_points:
                        dist = np.linalg.norm(points[cube_point_id] - points[neighbor_point_id])

                        if dist - search_radius < EPSILON:
                            neighbors[cube_point_id].append(neighbor_point_id)
                            neighbors[neighbor_point_id].append(cube_point_id)

    return neighbors


def main(points: np.ndarray, search_radius: float, field_size: float):

    cubes, cube2points = find_points_cubes(points=points, search_radius=search_radius, field_size=field_size)
    print("CUBES:\n", cubes, "CUBE2POINTS:\n", cube2points)

    cube_nb = _find_neighbor_cubes(cube_ids=cubes, search_radius=search_radius, field_size=field_size)
    print("CUBE NEIGHBORS:\n", cube_nb)

    nb = search_neighbor_cubes(points, search_radius, cubes, cube_nb, cube2points)
    print("POINT NEIGHBORS:\n", nb)

    return nb


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

    # res = main(points=xy, search_radius=SEARCH_RADIUS, field_size=FIELD_SIZE)

    cubes = find_points_cubes(points=xy, search_radius=SEARCH_RADIUS, field_size=FIELD_SIZE)
    print("CUBES:\n", cubes)

    cube_nb = _find_neighbor_cubes(search_radius=SEARCH_RADIUS, field_size=FIELD_SIZE)
    for cube_id, nb in enumerate(cube_nb):
        print(f"CUBE ID: {cube_id} CUBE NEIGHBORS: {nb}")

    print(cube_nb)

    points_nb = search_neighbor_cubes(xy, SEARCH_RADIUS, cubes, cube_nb)
    print("POINT NEIGHBORS:\n", points_nb)

    print("Correct neighbors:\n", correct_neighbors)
