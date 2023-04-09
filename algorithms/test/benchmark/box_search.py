from dist_sqr import dist_sqr


class BoxSearch:
    def __init__(self, search_radius: float, epsilon: float, field_size: float):
        """

        :param search_radius: minimal distance for particles to become neighbors
        :param epsilon: distance calculation precision
        :param field_size: working field upper bounder
        """
        self.search_radius = search_radius
        self.epsilon = epsilon
        self.field_size = field_size
        self._boxes_in_row = int(self.field_size / self.search_radius)
        self._total_boxes = self._boxes_in_row ** 2
        self._box_neighbors = self._find_neighbor_boxes()

    def _find_points_boxes(self, points: list[list]) -> list[list]:
        box_indexes = [[] for box in range(self._total_boxes)]

        for point_index, point in enumerate(points):
            col = round(point[0] / self.search_radius)
            row = round(point[1] / self.search_radius)
            box_id = int(row * self._boxes_in_row + col)
            box_indexes[box_id].append(point_index)

        return box_indexes

    def _find_one_box_neighbors(self, box_id: int) -> list[int]:
        col = box_id % self._boxes_in_row
        row = round(box_id / self._boxes_in_row)
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
        box_neighbors_ids = [row * self._boxes_in_row + col for row, col in possible_neighbors
                             if (0 <= col < self._boxes_in_row) and (0 <= row < self._boxes_in_row)]

        return box_neighbors_ids

    def _find_neighbor_boxes(self) -> list[list]:
        """
        Finds neighbor boxes indexes for all boxes of the field size.
        :return: list of neighbor boxes indexes for each box.
        """
        boxes_neighbors_ids = [[] for box in range(self._total_boxes)]
        for row in range(self._boxes_in_row):
            for col in range(self._boxes_in_row):
                current_cube_id = row * self._boxes_in_row + col

                for x in range(max(0, row - 1), min(row + 1, self._boxes_in_row - 1) + 1):
                    for y in range(max(0, col - 1), min(col + 1, self._boxes_in_row - 1) + 1):
                        if x != row or y != col:
                            neighbor_cube_id = x * self._boxes_in_row + y
                            boxes_neighbors_ids[current_cube_id].append(neighbor_cube_id)

        return boxes_neighbors_ids

    def search(self, points: list[list]) -> list[list]:
        neighbors = [[] for point in range(len(points))]
        points_boxes = self._find_points_boxes(points)

        for box_id, box_points_ids in enumerate(points_boxes):
            curr_box_neighbors = self._box_neighbors[box_id]

            for neighbor_box_id in curr_box_neighbors:
                if neighbor_box_id >= box_id:
                    neighbor_box_points = points_boxes[neighbor_box_id]

                    for box_point_id in box_points_ids:
                        for neighbor_point_id in neighbor_box_points:
                            dist = dist_sqr(points[box_point_id], points[neighbor_point_id])
                            if dist - self.search_radius ** 2 < self.epsilon:
                                neighbors[box_point_id].append(neighbor_point_id)
                                neighbors[neighbor_point_id].append(box_point_id)

        return neighbors
