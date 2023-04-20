import unittest

from box_search import BoxSearch


class TestBoxSearch(unittest.TestCase):

    def setUp(self):
        self.search_radius = 0.2
        self.epsilon = 10e-8
        self.domain_size = 1.0
        self._boxes_in_row = int(self.domain_size / self.search_radius)
        self._total_boxes = self._boxes_in_row ** 2
        self.init_cases = [
            {  # 2x2 boxes
                'input': {
                    'search_radius': 0.2,
                    'domain_size': 0.4,
                    'epsilon': 10e-8,
                },
                'expected_output': {
                    'boxes_in_row': 2,
                    'total_boxes': 4
                }
            },
            {  # 3x3 boxes
                'input': {
                    'search_radius': 0.4,
                    'domain_size': 1.2,
                    'epsilon': 10e-8,
                },
                'expected_output': {
                    'boxes_in_row': 3,
                    'total_boxes': 9
                }
            },
            {  # 4x4 boxes
                'input': {
                    'search_radius': 0.3,
                    'domain_size': 1.2,
                    'epsilon': 10e-8,
                },
                'expected_output': {
                    'boxes_in_row': 4,
                    'total_boxes': 16
                }
            },
            {  # 5x5 boxes
                'input': {
                    'search_radius': 0.2,
                    'domain_size': 1.0,
                    'epsilon': 10e-8,
                },
                'expected_output': {
                    'boxes_in_row': 5,
                    'total_boxes': 25
                }
            }
        ]
        self.neighbor_boxes_cases = [
            {  # 2x2 boxes
                'input': {
                    'search_radius': 0.2,
                    'domain_size': 0.4,
                    'epsilon': 10e-8,
                },
                'expected_output': [
                    # box neighbors
                    [1, 2, 3],  # 0
                    [0, 2, 3],  # 1
                    [0, 1, 3],  # 2
                    [0, 1, 2],  # 3
                ]

            },
            {  # 3x3 boxes
                'input': {
                    'search_radius': 0.4,
                    'domain_size': 1.2,
                    'epsilon': 10e-8,
                },
                'expected_output': [
                    # box neighbors
                    [1, 3, 4],                  # 0
                    [0, 2, 3, 4, 5],            # 1
                    [1, 4, 5],                  # 2
                    [0, 1, 4, 6, 7],            # 3
                    [0, 1, 2, 3, 5, 6, 7, 8],   # 4
                    [1, 2, 4, 7, 8],            # 5
                    [3, 4, 7],                  # 6
                    [3, 4, 5, 6, 8],            # 7
                    [4, 5, 7],                  # 8
                ]

            },
            {  # 4x4 boxes
                'input': {
                    'search_radius': 0.3,
                    'domain_size': 1.2,
                    'epsilon': 10e-8,
                },
                'expected_output': [
                    # box neighbors
                    [1, 4, 5],                      # 0
                    [0, 2, 4, 5, 6],                # 1
                    [1, 3, 5, 6, 7],                # 2
                    [2, 6, 7],                      # 3
                    [0, 1, 5, 8, 9],                # 4
                    [0, 1, 2, 4, 6, 8, 9, 10],      # 5
                    [1, 2, 3, 5, 7, 9, 10, 11],     # 6
                    [2, 3, 6, 10, 11],              # 7
                    [4, 5, 9, 12, 13],              # 8
                    [4, 5, 6, 8, 10, 12, 13, 14],   # 9
                    [5, 6, 7, 9, 11, 13, 14, 15],   # 10
                    [6, 7, 10, 14, 15],             # 11
                    [8, 9, 13],                     # 12
                    [8, 9, 10, 12, 14],             # 13
                    [9, 10, 11, 13, 15],            # 14
                    [10, 11, 14],                   # 15
                ]
            },
            {  # 5x5 boxes
                'input': {
                    'search_radius': 0.2,
                    'domain_size': 1.0,
                    'epsilon': 10e-8,
                },
                'expected_output': [
                    # box neighbors
                    [1, 5, 6],                          # 0
                    [0, 2, 5, 6, 7],                    # 1
                    [1, 3, 6, 7, 8],                    # 2
                    [2, 4, 7, 8, 9],                    # 3
                    [3, 8, 9],                          # 4
                    [0, 1, 6, 10, 11],                  # 5
                    [0, 1, 2, 5, 7, 10, 11, 12],        # 6
                    [1, 2, 3, 6, 8, 11, 12, 13],        # 7
                    [2, 3, 4, 7, 9, 12, 13, 14],        # 8
                    [3, 4, 8, 13, 14],                  # 9
                    [5, 6, 11, 15, 16],                 # 10
                    [5, 6, 7, 10, 12, 15, 16, 17],      # 11
                    [6, 7, 8, 11, 13, 16, 17, 18],      # 12
                    [7, 8, 9, 12, 14, 17, 18, 19],      # 13
                    [8, 9, 13, 18, 19],                 # 14
                    [10, 11, 16, 20, 21],               # 15
                    [10, 11, 12, 15, 17, 20, 21, 22],   # 16
                    [11, 12, 13, 16, 18, 21, 22, 23],   # 17
                    [12, 13, 14, 17, 19, 22, 23, 24],   # 18
                    [13, 14, 18, 23, 24],               # 19
                    [15, 16, 21],                       # 20
                    [15, 16, 17, 20, 22],               # 21
                    [16, 17, 18, 21, 23],               # 22
                    [17, 18, 19, 22, 24],               # 23
                    [18, 19, 23]                        # 24
                ]
            }
        ]
        self.points_cases = [
            {  # 2x2 boxes
                'input': {
                    'search_radius': 0.2,
                    'domain_size': 0.4,
                    'epsilon': 10e-8,
                    'points': [
                        [0.1, 0.2],     # 0
                        [0.3, 0.1],     # 1
                        [0.2, 0.2]      # 2
                    ]
                },
                'expected_output': [
                    # box points
                    [],     # 0
                    [1],    # 1
                    [0],    # 2
                    [2],    # 3
                ]

            },
            {  # 3x3 boxes
                'input': {
                    'search_radius': 0.4,
                    'domain_size': 1.2,
                    'epsilon': 10e-8,
                    'points': [
                        [0.4, 0.5],   # 0
                        [0.9, 0.3],   # 1
                        [0.5, 0.4],   # 2
                        [0.2, 1.0],   # 3
                    ]
                },
                'expected_output': [
                    # box points
                    [],      # 0
                    [],      # 1
                    [1],     # 2
                    [],      # 3
                    [0, 2],  # 4
                    [],      # 5
                    [3],     # 6
                    [],      # 7
                    [],      # 8
                ]

            },
            {  # 4x4 boxes
                'input': {
                    'search_radius': 0.3,
                    'domain_size': 1.2,
                    'epsilon': 10e-8,
                    'points': [
                        [0.5, 0.5],  # 0
                        [0.6, 0.3],  # 1
                        [1.0, 0.7],  # 2
                        [0.4, 0.6],  # 3
                        [0.8, 0.8],  # 4
                    ]
                },
                'expected_output': [
                    # box points
                    [],   # 0
                    [],   # 1
                    [],   # 2
                    [],   # 3
                    [],   # 4
                    [0],  # 5
                    [1],  # 6
                    [],   # 7
                    [],   # 8
                    [3],  # 9
                    [4],  # 10
                    [2],   # 11
                    [],   # 12
                    [],   # 13
                    [],   # 14
                    [],   # 15
                ]

            },
            {  # 5x5 boxes
                'input': {
                    'search_radius': 0.2,
                    'domain_size': 1.0,
                    'epsilon': 10e-8,
                    'points': [
                        [0.2, 0.2],   # 0
                        [0.5, 0.4],   # 1
                        [0.5, 0.6],   # 2
                        [0.2, 0.7],   # 3
                        [0.9, 0.75],  # 4
                        [0.6, 0.35],  # 5
                        [0.45, 0.5],  # 6
                    ]
                },
                'expected_output': [
                    # box points
                    [],  # 0
                    [],  # 1
                    [],  # 2
                    [],  # 3
                    [],  # 4
                    [],  # 5
                    [0],  # 6
                    [],  # 7
                    [5],  # 8
                    [],  # 9
                    [],  # 10
                    [],      # 11
                    [1, 6],  # 12
                    [],  # 13
                    [],  # 14
                    [],  # 15
                    [3],  # 16
                    [2],  # 17
                    [],  # 18
                    [4],  # 19
                    [],  # 20
                    [],  # 21
                    [],  # 22
                    [],  # 23
                    []  # 24
                ]

            },
        ]

    def test_init(self):
        for case in self.init_cases:
            config = case['input']
            expected_output = case['expected_output']
            with self.subTest(config=case['input']):
                actual_box_search = BoxSearch(search_radius=config['search_radius'],
                                              domain_size=config['domain_size'])

                self.assertEqual(actual_box_search._boxes_in_row, expected_output['boxes_in_row'])
                self.assertEqual(actual_box_search._total_boxes, expected_output['total_boxes'])

    def test_find_neighbor_boxes(self):
        for case in self.neighbor_boxes_cases:
            config = case['input']
            expected_nb = case['expected_output']
            with self.subTest(config=config):
                actual_box_nb = BoxSearch(search_radius=config['search_radius'],
                                          domain_size=config['domain_size'])._box_neighbors
                actual_box_nb = [sorted(neighbors) for neighbors in actual_box_nb]

                self.assertEqual(actual_box_nb, expected_nb)

    def test_put_points_into_boxes(self):
        for case in self.points_cases:
            config = case['input']
            expected_bp = case['expected_output']
            with self.subTest(config=config):
                actual_bp = BoxSearch(search_radius=config['search_radius'],
                                      domain_size=config['domain_size'], verbose=True)._put_points_into_boxes(config['points'])
                actual_bp = [sorted(box_points) for box_points in actual_bp]

                self.assertEqual(actual_bp, expected_bp)


if __name__ == '__main__':
    unittest.main()
