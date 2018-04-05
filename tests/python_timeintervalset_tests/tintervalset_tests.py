import unittest
import pybstream


class TestTIntervalSet(unittest.TestCase):

    def test_Constructor(self):
        """Test Constructor of TimeIntervalSet"""
        ti = pybstream.TimeIntervalSet()
        (l,h) = ti.interval_def()
        self.assertEqual(l, 0)
        self.assertEqual(h, 9223372036854775807)

        ti.set_interval_def(0, 10)
        (l,h) = ti.interval_def()
        self.assertEqual(ti.definition_length(), 10)
        self.assertEqual(l, 0)
        self.assertEqual(h, 10)

        ti = pybstream.TimeIntervalSet(0, 10)
        (l,h) = ti.interval_def()
        self.assertEqual(ti.definition_length(), 10)
        self.assertEqual(l, 0)
        self.assertEqual(h, 10)

    def test_Append(self):
        ti = pybstream.TimeIntervalSet(0, 10)
        ti.append(1, 2)
        self.assertEqual(ti.size(), 1)
        ti.append(6,8)
        self.assertEqual(ti.size(), 2)
        self.assertEqual(ti.length(), 3)

    def test_Erase(self):
        ti = pybstream.TimeIntervalSet(0, 10)
        ti.append(1, 2)
        ti.append(6,8)
        ti.erase()
        self.assertEqual(ti.size(), 0)
        self.assertEqual(ti.length(), 0)

if __name__ == '__main__':
    unittest.main()