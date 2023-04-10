import logging

from dist_sqr import dist_sqr


class BoxSearch:
    def __init__(self, search_radius: float, domain_size: float, epsilon: float = 10e-8, verbose: bool = False):
        """
        Initialize the box-based neighbors search algorithm.
        :param search_radius: minimal distance for particles to become neighbors
        :param epsilon: precision for distance calculation, set to 10e-8 by default
        :param domain_size: upper bound for the working domain
        """
        print("START BOX SEARCH")
        self.search_radius = search_radius
        self.epsilon = epsilon
        self.domain_size = domain_size
        self.LOG = logging.getLogger(__name__)
        self._verbose = verbose
        self._boxes_in_row = round(self.domain_size / self.search_radius)
        self._total_boxes = self._boxes_in_row ** 2
        self._box_neighbors = self._find_neighbor_boxes()
        # if self._verbose:
        #     self.LOG.setLevel(level=logging.DEBUG)
        #     message = eval(f"search_radius={self.search_radius}, domain_size{self.domain_size}, epsilon={self.epsilon}, boxes_in_row={self._boxes_in_row}, _total_boxes={self._total_boxes}")
        #     self.LOG.debug(message)

    def _find_neighbor_boxes(self) -> list[list]:
        """
        Finds neighbor boxes indexes for all boxes of the provided domain size.
        :return: 2D list of neighbor boxes indexes for each box.
        """
        neighbor_boxes_ids = [[] for box in range(self._total_boxes)]
        for row in range(self._boxes_in_row):
            for col in range(self._boxes_in_row):
                current_box_id = row * self._boxes_in_row + col

                for x in range(max(0, row - 1), min(row + 1, self._boxes_in_row - 1) + 1):
                    for y in range(max(0, col - 1), min(col + 1, self._boxes_in_row - 1) + 1):
                        if x != row or y != col:
                            neighbor_box_id = x * self._boxes_in_row + y
                            neighbor_boxes_ids[current_box_id].append(neighbor_box_id)
        # if self._verbose:
        #     for box_id, neighbor_boxes in enumerate(neighbor_boxes_ids):
        #         message = eval(f"BOX {box_id} NEIGHBORS: {neighbor_boxes}")
        #         self.LOG.debug(message)

        return neighbor_boxes_ids

    def _put_points_into_boxes(self, points: list[list]) -> list[list]:
        """
        Assigns a box index for each point based on its coordinates and returns list of associated points for each box
        of the domain.
        :param points: 2D list of kind [[p0x, p0y], [p1x, p1y], ...]
        :return: 2D list of kind [[point_index, point_index, ...], [point_index, point_index, ...], ...],
                where the list index is the index of the according associated box.
        """
        points_in_boxes = [[] for box in range(self._total_boxes)]

        for point_index, point in enumerate(points):
            col = round(point[0] / self.search_radius)
            row = round(point[1] / self.search_radius)
            box_id = int(row * self._boxes_in_row + col)
            points_in_boxes[box_id].append(point_index)

        return points_in_boxes

    def search(self, points: list[list]) -> list[list]:
        """
        Performs the box-based neighbors search on the passed points.
        :param points: 2D list of kind [[p0x, p0y], [p1x, p1y], ...]
        :return: 2D list of kind [[neighbor_point_index, neighbor_point_index, ...],  ...],
                where the list index is the index of the according point.
        """
        neighbors = [[] for point in range(len(points))]
        points_in_boxes = self._put_points_into_boxes(points)

        for box_id, box_points_ids in enumerate(points_in_boxes):
            curr_box_neighbors = self._box_neighbors[box_id]

            for neighbor_box_id in curr_box_neighbors:
                if neighbor_box_id >= box_id:
                    neighbor_box_points = points_in_boxes[neighbor_box_id]

                    for box_point_id in box_points_ids:
                        for neighbor_point_id in neighbor_box_points:
                            dist = dist_sqr(points[box_point_id], points[neighbor_point_id])
                            if dist - self.search_radius ** 2 < self.epsilon:
                                neighbors[box_point_id].append(neighbor_point_id)
                                neighbors[neighbor_point_id].append(box_point_id)

        return neighbors
