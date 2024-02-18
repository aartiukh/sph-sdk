import unittest

from hash_table_search import HashBasedBoxSearch


class TestHashBasedBoxSearch(unittest.TestCase):

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

    def test_init(self):
        for case in self.init_cases:
            config = case['input']
            expected_output = case['expected_output']
            with self.subTest(config=case['input']):
                actual_box_search = HashBasedBoxSearch(search_radius=config['search_radius'],
                                                       domain_size=config['domain_size'])

                self.assertEqual(actual_box_search._boxes_in_row, expected_output['boxes_in_row'])
                self.assertEqual(actual_box_search._total_boxes, expected_output['total_boxes'])


if __name__ == '__main__':
    unittest.main()
