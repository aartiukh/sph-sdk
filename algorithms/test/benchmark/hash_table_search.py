import logging
import sys

from dist_sqr import dist_sqr

LOG = logging.getLogger(__name__)
logging.basicConfig(format='%(asctime)s[%(name)s:%(lineno)d] %(levelname)s %(message)s')


class HashBasedBoxSearch:
    def __init__(self, search_radius: float, domain_size: float, cell_size: float = None, epsilon: float = 10e-8, verbose: bool = False):
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
        self._box_neighbors = self._find_neighbor_boxes()
        self.hash_map = {}

        if verbose:
            LOG.setLevel(level=logging.DEBUG)
            message = "Initialized BoxSearch: search_radius={sr}, domain_size={ds}, epsilon={eps}, " \
                      "boxes_in_row={bxs}, total_boxes={tbxs}".format(sr=self.search_radius,
                                                                      ds=self.domain_size,
                                                                      eps=self.epsilon,
                                                                      bxs=self._boxes_in_row,
                                                                      tbxs=self._total_boxes)
            LOG.debug(message)

    def _find_neighbor_boxes(self) -> list[list]:
        pass

    def _put_points_into_boxes(self, points: list[list]) -> list[list]:
        pass

    def search(self, points: list[list]) -> list[list]:
        pass

