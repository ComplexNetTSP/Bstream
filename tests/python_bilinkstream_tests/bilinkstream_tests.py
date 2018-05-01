import unittest
import pybstream as pb
from pybstream import vertex_group


class TestBiLinkStream(unittest.TestCase):

    def test_BiLinkStream_constructor(self):
        """Tests bipartite LinkStream."""
        g = pb.BiLinkStream(0,10)
        g.add_vertex_w_group(vertex_group.top, "A")
        g.add_vertex_w_group(vertex_group.bottom, "B")
        g.add_vertex_w_group(vertex_group.top, "C")
        g.add_edge("A", "B")
        g.add_edge("C", "B")
        self.assertFalse(g.is_directed())
        self.assertEqual(g.num_vertices(), 3)
        self.assertEqual(g.num_edges(), 2)
        self.assertEqual(g.num_top_vertices(), 2)
        self.assertEqual(g.num_bottom_vertices(), 1)

    def test_BiLinkStream_constructor_bis(self):
        """Tests bipartite LinkStream."""
        g = pb.BiLinkStream()
        A = g.add_vertex_w_group(vertex_group.top)
        B = g.add_vertex_w_group(vertex_group.bottom)
        C = g.add_vertex_w_group(vertex_group.top)
        g.add_edge(A, B)
        g.add_edge(C, B)
        self.assertFalse(g.is_directed())
        self.assertEqual(g.num_vertices(), 3)
        self.assertEqual(g.num_edges(), 2)
        self.assertEqual(g.num_top_vertices(), 2)
        self.assertEqual(g.num_bottom_vertices(), 1)

    def test_BiLinkStream_add_edge(self):
        """Tests bipartite LinkStream."""
        g = pb.BiLinkStream(0,5)
        A = g.add_vertex_w_group(vertex_group.top)
        B = g.add_vertex_w_group(vertex_group.bottom)
        C = g.add_vertex_w_group(vertex_group.top)
        g.add_edge_w_time(A, B, 0, 5)
        g.add_edge_w_time(C, B, 0, 5)
        self.assertFalse(g.is_directed())
        self.assertEqual(g.num_vertices(), 3)
        self.assertEqual(g.num_edges(), 2)
        self.assertEqual(g.num_top_vertices(), 2)
        self.assertEqual(g.num_bottom_vertices(), 1)


    def test_BiLinkStream_exception(self):
        """Tests bipartite LinkStream."""
        g = pb.BiLinkStream()
        A = g.add_vertex_w_group(vertex_group.top)
        B = g.add_vertex_w_group(vertex_group.top)
        with self.assertRaises(RuntimeError) as ctx:
            g.add_edge_w_time(A, B, 0, 5)



if __name__ == '__main__':
    unittest.main()