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
        self.hashed_box_id2points = {}
        self.box_id2hash = {}
        self._int_neighbor_boxes_ids = None
        self._box_neighbors = self._find_neighbor_boxes()

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
    def _get_hash(col: int, row: int) -> int:
        p1 = 73856093
        p2 = 19349663
        p3 = 83492791

        hashed_box_id = ((col * p1) ^ (row * p2))

        return hashed_box_id

    def _discretize_point_coords(self, point: list[float]) -> tuple[int, int]:
        """
        col = int((point[0] + sys.float_info.epsilon) // self.search_radius)
        row = int((point[1] + sys.float_info.epsilon) // self.search_radius)
        discretized_point_coords = [col, row]
        box_id = int(row * self._boxes_in_row + col)
        """
        # discretized_coords = []
        # for coord in point:
        #     discretized_coords.append(int((coord + sys.float_info.epsilon) // self.search_radius))

        col = int((point[0] + sys.float_info.epsilon) // self.search_radius)
        row = int((point[1] + sys.float_info.epsilon) // self.search_radius)

        return col, row

    def _calculate_box_id_by_discr_coords(self, discretized_coords: list[int]) -> int:
        """
        col = int((point[0] + sys.float_info.epsilon) // self.search_radius)
        row = int((point[1] + sys.float_info.epsilon) // self.search_radius)
        discretized_point_coords = [col, row]
        box_id = int(discretized_point_coords[1] * self._boxes_in_row + discretized_point_coords[0])
        """
        box_id = int(discretized_coords[1] * self._boxes_in_row + discretized_coords[0])
        return box_id

    def _calculate_row_col_by_box_id(self, box_id: int) -> tuple[int, int]:
        """
        col = box_id % n_boxes_in_row
        row = box_id // n_boxes_in_row
        discretized_point_coords = [col, row]
        box_id = int(row * self._boxes_in_row + col)
        """
        col = int(box_id % self._boxes_in_row)
        row = int(box_id // self._boxes_in_row)

        return col, row

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
                current_hashed_box_id = self._get_hash(row=row, col=col)
                hashed_neighbor_boxes_ids[current_hashed_box_id] = []
                self.box_id2hash[current_box_id] = current_hashed_box_id

                for x in range(max(0, row - 1), min(row + 1, self._boxes_in_row - 1) + 1):
                    for y in range(max(0, col - 1), min(col + 1, self._boxes_in_row - 1) + 1):
                        if x != row or y != col:
                            neighbor_box_id = x * self._boxes_in_row + y
                            neighbor_hashed_box_id = self._get_hash(col=y, row=x)
                            neighbor_boxes_ids[current_box_id].append(neighbor_box_id)
                            hashed_neighbor_boxes_ids[current_hashed_box_id].append(neighbor_hashed_box_id)

        self._int_neighbor_boxes_ids = neighbor_boxes_ids

        if self._verbose:
            for box_id, neighbor_boxes in enumerate(neighbor_boxes_ids):
                message = "BOX_ID = {b_id} HASHED_BOX_ID = {hb_id} NEIGHBORS: {nb_bx}".format(b_id=box_id,
                                                                                              hb_id=self.box_id2hash[
                                                                                                  box_id],
                                                                                              nb_bx=neighbor_boxes)
                LOG.debug(message)

        return hashed_neighbor_boxes_ids


if __name__ == '__main__':
    pass
