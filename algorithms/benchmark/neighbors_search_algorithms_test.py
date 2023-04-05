import unittest


from bruteforce import bruteforce, optimized_bruteforce


class TestBenchmark2D(unittest.TestCase):

    def setUp(self):
        self.search_radius = 0.2
        self.epsilon = 10e-8
        self.square_len = 1.0
        self.all_points = [
            # 1 single point
            [
                [0.1, 0.9]
            ],
            # 2 points neighbors
            [
                [0.6, 0.8],
                [0.55, 0.65]
            ],
            # 2 points non-neighbors
            [
                [0.4, 0.1],
                [0.7, 0.3]
            ],
            # 3 points with 1 common neighbor
            [
                [0.18, 0.2],
                [0.35, 0.15],
                [0.4, 0.1]
            ],
            # 5 points: 3 points with 1 common neighbor and 2 different points neighbors
            [
                [0.18, 0.2],
                [0.35, 0.15],
                [0.4, 0.1],
                [0.7, 0.3],
                [0.85, 0.4]
            ],
            # all 10 points
            [
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
            ]
        ]
        self.answers = [
            # 1 single point
            [
                []
            ],
            # 2 points neighbors
            [
                [1],
                [0]
            ],
            # 2 points non-neighbors
            [
                [],
                []
            ],
            # 3 points with 1 common neighbor
            [
                [1],
                [0, 2],
                [1]
            ],
            # 5 points: 3 points with 1 common neighbor and 2 different points neighbors
            [
                [1],
                [0, 2],
                [1],
                [4],
                [3]
            ],
            # all 10 points
            [
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
            ]
        ]

    def test_bruteforce(self):
        for points, answer in zip(self.all_points, self.answers):
            with self.subTest(points=points):
                found_nb = bruteforce(points, self.search_radius, self.epsilon)
                found_nb = [sorted(neighbors) for neighbors in found_nb]
                self.assertEqual(found_nb, answer)

    def test_optimized_bruteforce(self):
        for points, answer in zip(self.all_points, self.answers):
            with self.subTest(points=points):
                found_nb = optimized_bruteforce(points, self.search_radius, self.epsilon)
                found_nb = [sorted(neighbors) for neighbors in found_nb]
                self.assertEqual(found_nb, answer)


if __name__ == '__main__':
    unittest.main()
