import logging
import sys

from dist_sqr import dist_sqr

LOG = logging.getLogger(__name__)
logging.basicConfig(format='%(asctime)s[%(name)s:%(lineno)d] %(levelname)s %(message)s')


class HashBasedBoxSearch:
    def __init__(self, search_radius: float, domain_size: float,
                 cell_size: float = None, epsilon: float = 10e-8,
                 verbose: bool = False):
        """
        Initialize the box-based neighbors search algorithm.
        :param search_radius: minimal distance for particles to become neighbors
        :param epsilon: precision for distance calculation, set to 10e-8 by default
        :param domain_size: upper bound for the working domain
        """

        self.search_radius = search_radius
        self.epsilon = epsilon
        self.domain_size = domain_size
        self._verbose = verbose
        self.box_size = cell_size if cell_size is not None else self.search_radius

        self._boxes_in_row = round(self.domain_size / self.search_radius)
        self._total_boxes = self._boxes_in_row ** 2
        self.box_id2hash = {}
        self._box_neighbors_dict = self._find_neighbor_boxes()

        if self._verbose:
            LOG.setLevel(level=logging.DEBUG)
            message = "Initialized HashedBoxSearch: search_radius={sr}, domain_size={ds}, epsilon={eps}, " \
                      "boxes_in_row={bxs}, total_boxes={tbxs}".format(sr=self.search_radius,
                                                                      ds=self.domain_size,
                                                                      eps=self.epsilon,
                                                                      bxs=self._boxes_in_row,
                                                                      tbxs=self._total_boxes)
            LOG.debug(message)

    @staticmethod
    def _get_hash(self, discretized_coords: list[int], discretize: bool = False, raw_box_id: int = None) -> int:
        p1 = 73856093
        p2 = 19349663
        p3 = 83492791
        int_box_id = self._calculate_box_id(discretized_coords[0])
        hashed_box_id = ((discretized_coords[0] * p1) ^ (discretized_coords[1] * p2))
        LOG.debug(f"")

        return hashed_box_id

    def _find_neighbor_boxes(self) -> dict[int, list]:
        """
        Finds neighbor boxes indexes for all boxes of the provided domain size.
        :return: 2D list of neighbor boxes indexes for each box.
        """
        neighbor_boxes_ids = [[] for box in range(self._total_boxes)]
        hashed_neighbor_boxes_ids = {}
        for row in range(self._boxes_in_row):
            for col in range(self._boxes_in_row):
                current_box_id = row * self._boxes_in_row + col
                current_hashed_box_id = self._get_hash([row, col])
                hashed_neighbor_boxes_ids[current_hashed_box_id] = []
                self.box_id2hash[current_box_id] = current_hashed_box_id

                for x in range(max(0, row - 1), min(row + 1, self._boxes_in_row - 1) + 1):
                    for y in range(max(0, col - 1), min(col + 1, self._boxes_in_row - 1) + 1):
                        if x != row or y != col:
                            neighbor_box_id = x * self._boxes_in_row + y
                            neighbor_boxes_ids[current_box_id].append(neighbor_box_id)
                            hashed_neighbor_boxes_ids[current_hashed_box_id].append(neighbor_box_id)

        if self._verbose:
            for box_id, neighbor_boxes in enumerate(neighbor_boxes_ids):
                message = "BOX_ID = {b_id} HASHED_BOX_ID = {hb_id} NEIGHBORS: {nb_bx}".format(b_id=box_id,
                                                                                              hb_id=self.box_id2hash[
                                                                                                  box_id],
                                                                                              nb_bx=neighbor_boxes)
                LOG.debug(message)

        return hashed_neighbor_boxes_ids

    def _discretize_coords(self, point: list[float]) -> list[int]:
        """
        col = point_x + EPS // search_radius
        row = col = point_y + EPS // search_radius
        discretized_coords = [col, row]
        """
        discretized_coords = []
        for coord in point:
            discretized_coords.append(int((coord + sys.float_info.epsilon) // self.search_radius))

        return discretized_coords

    def _calculate_box_id(self, discretized_coords: list[int]) -> int:
        """
        discretized_coords = [col, row]
        box_id = int(row * self._boxes_in_row + col)
        """
        box_id = int(discretized_coords[1] * self._boxes_in_row + discretized_coords[0])
        return box_id

    def _put_points_into_boxes(self, points: list[list]) -> dict[int, list]:
        """
        Assigns a box index for each point based on its coordinates and returns list of associated points for each box
        of the domain.
        :param points: 2D list of kind [[p0x, p0y], [p1x, p1y], ...]
        :return: 2D list of kind [[point_index, point_index, ...], [point_index, point_index, ...], ...],
                where the list index is the index of the according associated box.
        """
        points_in_boxes = [[] for box in range(self._total_boxes)]
        points_in_hashed_boxes = {}

        for point_index, point in enumerate(points):
            discretized_coords = self._discretize_coords(point)
            box_id = self._calculate_box_id(discretized_coords)
            hashed_box_id = self.box_id2hash[box_id]
            points_in_boxes[box_id].append(point_index)  # regular box search

            if hashed_box_id not in points_in_hashed_boxes.keys():
                points_in_hashed_boxes[hashed_box_id] = [point_index]
            else:
                points_in_hashed_boxes[hashed_box_id].append(point_index)

            if self._verbose:
                message = ("POINT_{p_idx}({point}): COL = {col} ROW = {row} BOX_ID = {box_id} "
                           "HASHED_BOX_ID = {hashed_box_id}").format(p_idx=point_index,
                                                                     point=point,
                                                                     col=discretized_coords[0],
                                                                     row=discretized_coords[1],
                                                                     box_id=box_id,
                                                                     hashed_box_id=hashed_box_id)
                LOG.debug(message)

        if self._verbose:
            message = "TOTAL BOXES: {n_boxes}".format(n_boxes=len(points_in_boxes))
            LOG.debug(message)
            for box_id, points_ids in enumerate(points_in_boxes):
                message = "BOX {box} POINTS: {pts_idx}".format(box=box_id,
                                                               pts_idx=points_ids)
                LOG.debug(message)

        return points_in_hashed_boxes

    def search(self, points: list[list]) -> list[list]:
        """
        Performs the box-based neighbors search on the passed points.
        :param points: 2D list of kind [[p0x, p0y], [p1x, p1y], ...]
        :return: 2D list of kind [[neighbor_point_index, neighbor_point_index, ...],  ...],
                where the list index is the index of the according point.
        """
        neighbors = [[] for point in range(len(points))]
        points_in_boxes = self._put_points_into_boxes(points)

        for box_id, box_points_ids in points_in_boxes.items():
            curr_box_neighbors = self._box_neighbors_dict[box_id]

            for neighbor_box_id in curr_box_neighbors:
                # if neighbor_box_id >= box_id:
                neighbor_box_points = points_in_boxes[neighbor_box_id]

                for box_point_id in box_points_ids:
                    for neighbor_point_id in neighbor_box_points:
                        dist = dist_sqr(points[box_point_id], points[neighbor_point_id])
                        if dist - self.search_radius ** 2 < self.epsilon:
                            neighbors[box_point_id].append(neighbor_point_id)
                            neighbors[neighbor_point_id].append(box_point_id)

        return neighbors


if __name__ == '__main__':
    pass