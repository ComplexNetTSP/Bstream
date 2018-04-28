import unittest
import pybstream


class TestBipartite(unittest.TestCase):

    def test_Bipartite(self):
        """Tests bipartite graph."""
        g = pybstream.Bipartite()
        g.add_vertex_w_group(1, "A")
        g.add_vertex_w_group(2, "B")
        g.add_vertex_w_group(1, "C")
        g.add_edge("A", "B")
        g.add_edge("C", "B")
        self.assertFalse(g.is_directed())
        self.assertEqual(g.num_vertices(), 3)
        self.assertEqual(g.num_edges(), 2)

        gproj = pybstream.projected_graph(1, g)
        self.assertEqual(gproj.num_vertices(), 2)
        self.assertEqual(gproj.num_edges(), 1)


if __name__ == '__main__':
    unittest.main()