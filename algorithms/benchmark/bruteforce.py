from dist_sqr import dist_sqr


class BruteForce:
    def __init__(self, search_radius: float, epsilon: float):
        self.search_radius = search_radius
        self.epsilon = epsilon

    def search(self, points: list[list]) -> list[list]:
        """

        :param points: 2D list of kind [[p0x, p0y], [p1x, p1y]]
        :return: list of neighbor points indexes for each point
        """
        points_number = len(points)
        neighbors = [[] for i in range(points_number)]

        for i in range(points_number):
            for j in range(points_number):
                if i == j:
                    continue

                dist = dist_sqr(points[i], points[j])

                if dist - self.search_radius ** 2 < self.epsilon:
                    neighbors[i].append(j)

        return neighbors


class BruteForceOptimized:
    def __init__(self, search_radius: float, epsilon: float):
        self.search_radius = search_radius
        self.epsilon = epsilon

    def search(self, points: list[list]) -> list[list]:
        """

        :param points: 2D list of kind [[p0x, p0y], [p1x, p1y]]
        :return: list of neighbor points indexes for each point
        """
        points_number = len(points)
        neighbors = [[] for i in range(points_number)]

        for i in range(points_number):
            for j in range(i + 1, points_number):
                dist = dist_sqr(points[i], points[j])

                if dist - self.search_radius ** 2 < self.epsilon:
                    neighbors[i].append(j)
                    neighbors[j].append(i)

        return neighbors
