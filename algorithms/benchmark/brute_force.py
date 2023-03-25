import numpy as np

np.random.seed(42)

x_len = 1.0
y_len = 1.0
n_points = 5
random_seed = 42
search_radius = x_len / 2

x = np.random.uniform(high=x_len, size=n_points)
y = np.random.uniform(high=y_len, size=n_points)

xy = np.array([x, y]).transpose()

print("points:\n", xy)

neighbors = {}

for i in range(xy.shape[0]):
    loc_neighbors = []

    for j in range(i+1, xy.shape[0]):
        dist = np.linalg.norm(xy[i] - xy[j])
        print(f"For points {i} and {j} dist {xy[i]} - {xy[j]} = {dist}")

        if dist <= search_radius:
            loc_neighbors.append(j)

    neighbors[i] = loc_neighbors

print("Neighbors:\n", neighbors)
