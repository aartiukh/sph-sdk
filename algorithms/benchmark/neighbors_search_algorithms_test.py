import unittest

import numpy as np

from bruteforce import bruteforce, optimized_bruteforce


class TestBenchmark2D(unittest.TestCase):

    def setUp(self):
        self.search_radius = 0.2
        self.square_len = 1.0
        self.all_points = [
            # no points
            np.array([

            ]),
            # 1 single point
            np.array([
                [0.1, 0.9]
            ]),
            # 2 points neighbors
            np.array([
                [0.6, 0.8],
                [0.55, 0.65]
            ]),
            # 2 points non-neighbors
            np.array([
                [0.4, 0.1],
                [0.7, 0.3]
            ]),
            # 3 points with 1 common neighbor
            np.array([
                [0.18, 0.2],
                [0.35, 0.15],
                [0.4, 0.1]
            ]),
            # 5 points: 3 points with 1 common neighbor and 2 different points neighbors
            np.array([
                [0.18, 0.2],
                [0.35, 0.15],
                [0.4, 0.1],
                [0.7, 0.3],
                [0.85, 0.4]
            ]),
            # all 10 points
            np.array([
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
            ])
        ]
        self.answers = [
            # no points
            {

            },
            # 1 single point
            {
                0: []
            },
            # 2 points neighbors
            {
                0: [1],
                1: [0]
            },
            # 2 points non-neighbors
            {
                0: [],
                1: []
            },
            # 3 points with 1 common neighbor
            {
                0: [1],
                1: [0, 2],
                2: [1]
            },
            # 5 points: 3 points with 1 common neighbor and 2 different points neighbors
            {
                0: [1],
                1: [0, 2],
                2: [1],
                3: [4],
                4: [3]
            },
            # all 10 points
            {
                0: [1],
                1: [0, 2],
                2: [1],
                3: [4],
                4: [3],
                5: [6],
                6: [5],
                7: [8],
                8: [7],
                9: []
            }
        ]

    def test_bruteforce(self):
        for points, answer in zip(self.all_points, self.answers):
            with self.subTest(points=points):
                found_nb = bruteforce(points, self.search_radius)
                found_nb = {k: sorted(v) for k, v in found_nb.items()}
                self.assertEqual(found_nb, answer)

    def test_opti_bruteforce(self):
        for points, answer in zip(self.all_points, self.answers):
            with self.subTest(points=points):
                found_nb = optimized_bruteforce(points, self.search_radius)
                found_nb = {k: sorted(v) for k, v in found_nb.items()}
                self.assertEqual(found_nb, answer)


if __name__ == '__main__':
    unittest.main()
