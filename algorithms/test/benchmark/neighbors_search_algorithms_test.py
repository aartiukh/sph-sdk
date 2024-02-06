import unittest

from bruteforce import BruteForce, BruteForceOptimized
from box_search import BoxSearch
from hash_table_search import HashBasedBoxSearch


class TestBenchmark2D(unittest.TestCase):

    def setUp(self):
        self.search_radius = 0.2
        self.epsilon = 10e-8
        self.domain_size = 1.0
        self.test_data = [
            # 1 single point case
            ([  # input
                 [0.1, 0.9]
             ],
             [  # expected output
                 []
             ]),
            # 2 points neighbors
            ([  # input
                 [0.6, 0.8],
                 [0.55, 0.65]
             ],
             [  # expected output
                 [1],
                 [0]
             ]),
            # 2 points non-neighbors
            ([  # input
                 [0.4, 0.1],
                 [0.7, 0.3]
             ],
             [  # expected output
                 [],
                 []
             ]),
            # 3 points with 1 common neighbor
            ([  # input
                 [0.18, 0.2],
                 [0.35, 0.15],
                 [0.4, 0.1]
             ],
             [  # expected output
                 [1],
                 [0, 2],
                 [1]
             ]),
            # 5 points: 3 points with 1 common neighbor and 2 different points neighbors
            ([  # input
                 [0.18, 0.2],
                 [0.35, 0.15],
                 [0.4, 0.1],
                 [0.7, 0.3],
                 [0.85, 0.4]
             ],
             [  # expected output
                 [1],
                 [0, 2],
                 [1],
                 [4],
                 [3]
             ]),
            # all 10 test points combined
            ([  # input
                 [0.18, 0.2],
                 [0.35, 0.15],
                 [0.4, 0.1],
                 [0.7, 0.3],
                 [0.85, 0.4],
                 [0.3, 0.45],
                 [0.2, 0.6],
                 [0.55, 0.65],
                 [0.6, 0.8],
                 [0.1, 0.9]
             ],
             [  # expected output
                 [1],
                 [0, 2],
                 [1],
                 [4],
                 [3],
                 [6],
                 [5],
                 [8],
                 [7],
                 []
             ])
        ]

    def test_bruteforce(self):
        for points, expected_nb in self.test_data:
            with self.subTest(points=points):
                bf = BruteForce(search_radius=self.search_radius, epsilon=self.epsilon)
                actual_nb = bf.search(points)
                actual_nb = [sorted(neighbors) for neighbors in actual_nb]
                self.assertEqual(actual_nb, expected_nb)

    def test_optimized_bruteforce(self):
        for points, expected_nb in self.test_data:
            with self.subTest(points=points):
                bfo = BruteForceOptimized(search_radius=self.search_radius, epsilon=self.epsilon)
                actual_nb = bfo.search(points)
                actual_nb = [sorted(neighbors) for neighbors in actual_nb]
                self.assertEqual(actual_nb, expected_nb)

    def test_box_search(self):
        for points, expected_nb in self.test_data:
            with self.subTest(points=points):
                box_search = BoxSearch(search_radius=self.search_radius, epsilon=self.epsilon,
                                       domain_size=self.domain_size)
                actual_nb = box_search.search(points)
                actual_nb = [sorted(neighbors) for neighbors in actual_nb]
                self.assertEqual(actual_nb, expected_nb)

    def test_hashed_box_search(self):
        for points, expected_nb in self.test_data:
            with self.subTest(points=points):
                box_search = HashBasedBoxSearch(search_radius=self.search_radius, epsilon=self.epsilon,
                                                domain_size=self.domain_size)
                actual_nb = box_search.search(points)
                actual_nb = [sorted(neighbors) for neighbors in actual_nb]
                self.assertEqual(actual_nb, expected_nb)


if __name__ == '__main__':
    unittest.main()
