import unittest
import pybstream as pb


class TestBipartite(unittest.TestCase):

    def test_Bipartite(self):
        """Tests bipartite graph."""
        g = pb.Bipartite()
        g.add_vertex_w_group(pb.vertex_group.top, "A")
        g.add_vertex_w_group(pb.vertex_group.bottom, "B")
        g.add_vertex_w_group(pb.vertex_group.top, "C")
        g.add_edge("A", "B")
        g.add_edge("C", "B")
        self.assertFalse(g.is_directed())
        self.assertEqual(g.num_vertices(), 3)
        self.assertEqual(g.num_edges(), 2)

        gproj = pb.projected_graph(pb.vertex_group.top, g)
        self.assertEqual(gproj.num_vertices(), 2)
        self.assertEqual(gproj.num_edges(), 1)


if __name__ == '__main__':
    unittest.main()