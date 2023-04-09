import unittest

from dist_sqr import dist_sqr


class TestDistSqr(unittest.TestCase):

    def setUp(self):
        self.decimal_places = 4
        self.test_data = [
            # 2D points
            ([  # input
                 [0.18, 0.2],
                 [0.35, 0.15],
             ],
             0.0314),
            # 3D points
            ([  # input
                 [0.18, 0.2, 0.5],
                 [0.35, 0.15, 0.1],
             ],
             0.1914),
        ]

    def test_dist_sqr(self):
        for points, expected_dist_sqr in self.test_data:
            with self.subTest(points=points):
                actual_dist_sqr = round(dist_sqr(*points), self.decimal_places)
                self.assertEqual(actual_dist_sqr, expected_dist_sqr)


if __name__ == '__main__':
    unittest.main()
