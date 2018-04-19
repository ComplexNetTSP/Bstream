import unittest
import pybstream

class TestLinkStream(unittest.TestCase):
    """Tests the class LinkStream."""

    def test_LinkStream(self):
        g = pybstream.LinkStream()
        g.set_definition(0, 10)
        self.assertFalse(g.is_directed())
        self.assertEqual(g.num_vertices(), 0)
        self.assertEqual(g.num_edges(), 0)
        self.assertEqual(g.definition(), (0,10))

        g1 = pybstream.LinkStream(100)
        self.assertEqual(g1.num_vertices(), 100)
        self.assertEqual(g1.num_edges(), 0)

    def test_LinkStream_density(self):
        g = pybstream.LinkStream(0, 10)
        g.add_vertex("A")
        g.add_vertex("B")
        g.add_vertex("C")
        g.add_edge_w_time("A", "B", 0, 5)
        g.add_edge_w_time("B", "C", 0, 5)
        g.add_edge_w_time("C", "A", 0, 5)
        density = 2 * g.num_edges() / (g.num_vertices() * (g.num_vertices() - 1))
        self.assertEqual(g.density(), density) # 0.5
        self.assertEqual(g.num_vertices(), 3)
        self.assertEqual(g.num_edges(), 1.5)



if __name__ == '__main__':
    unittest.main()