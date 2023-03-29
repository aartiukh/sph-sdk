import numpy as np

EPSILON = 10e-8
SEARCH_RADIUS = 0.2
FIELD_SIZE = 1.0


def find_cubes(points: np.ndarray, search_radius: float) -> np.ndarray:
    cols = xy[:, 0] // SEARCH_RADIUS
    rows = xy[:, 1] // SEARCH_RADIUS
    cube_size = FIELD_SIZE / SEARCH_RADIUS
    cube_ids = rows * cube_size + cols
    cube_ids = cube_ids.astype(int)
    return cube_ids


def _find_neighbor_cubes(cube_id: int, cube_size: float) -> list:
    cube_neighbors_ids = [
        cube_id - 1,
        cube_id + 1,
        cube_id - cube_size,
        cube_id + cube_size,
        cube_id + cube_size - 1,
        cube_id + cube_size + 1,
        cube_id - cube_size - 1,
        cube_id - cube_size + 1
    ]
    return cube_neighbors_ids


def find_neighbor_cubes(cube_ids: np.ndarray) -> np.ndarray:
    cube_size = FIELD_SIZE / SEARCH_RADIUS
    cubes_neighbors_ids = np.array([])
    for cube_id in cube_ids:
        neighbors = _find_neighbor_cubes(cube_id, cube_size)
        print(neighbors)
        cubes_neighbors_ids = np.append(cubes_neighbors_ids, neighbors)
    # cubes_neighbors_ids = [
    #     _find_neighbor_cubes(cube_id, cube_size) for cube_id in cube_ids]
    # cubes_neighbors_ids = np.ndarray(cubes_neighbors_ids)
    return cubes_neighbors_ids


if __name__ == '__main__':
    xy = np.array([
        [0.18, 0.2],
        [0.35, 0.15],
        [0.4, 0.1]
    ])

    cubes = find_cubes(xy, search_radius=SEARCH_RADIUS)
    print(cubes)

    cube_nb = find_neighbor_cubes(cubes)
    print(cube_nb)
