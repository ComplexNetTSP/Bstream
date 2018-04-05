import unittest
import pybstream


class TestGraph(unittest.TestCase):

    def test_Graph(self):
        """Tests the class Graph."""
        g = pybstream.Graph()
        self.assertFalse(g.is_directed())
        self.assertEqual(g.num_vertices(), 0)
        self.assertEqual(g.num_edges(), 0)

        g1 = pybstream.Graph(100)
        self.assertEqual(g1.num_vertices(), 100)
        self.assertEqual(g1.num_edges(), 0)

    def test_DiGraph(self):
        """Tests the class DiGraph."""
        g = pybstream.DiGraph()
        self.assertTrue(g.is_directed())
        self.assertEqual(g.num_vertices(), 0)
        self.assertEqual(g.num_edges(), 0)

        g1 = pybstream.DiGraph(100)
        self.assertEqual(g1.num_vertices(), 100)
        self.assertEqual(g1.num_edges(), 0)

    def test_Graph_add_vertex(self):
        """Tests the class Graph."""
        g = pybstream.Graph()
        g.add_vertex()
        self.assertEqual(g.num_vertices(), 1)
        self.assertEqual(g.num_edges(), 0)

    def test_Graph_add_edge(self):
        """Tests the class Graph."""
        g = pybstream.Graph()
        v1 = g.add_vertex()
        v2 = g.add_vertex()
        g.add_edge(v1, v2)
        self.assertTrue(g.has_edge(v1, v2))
        self.assertTrue(g.has_edge(v2, v1))
        self.assertEqual(g.num_vertices(), 2)
        self.assertEqual(g.num_edges(), 2)

    def test_Graph_degree(self):
        # Tests the Graph
        g = pybstream.Graph()
        v1 = g.add_vertex()
        v2 = g.add_vertex()
        v3 = g.add_vertex()
        g.add_edge(v1, v2)
        g.add_edge(v2, v3)
        g.add_edge(v3, v1)
        self.assertEqual(g.num_vertices(), 3)
        self.assertEqual(g.num_edges(), 6)
        self.assertEqual(g.degree(v1), 2)

        # Tests the Digraph
        g = pybstream.DiGraph()
        v1 = g.add_vertex()
        v2 = g.add_vertex()
        v3 = g.add_vertex()
        g.add_edge(v1, v2)
        g.add_edge(v2, v3)
        g.add_edge(v3, v1)
        self.assertEqual(g.num_vertices(), 3)
        self.assertEqual(g.num_edges(), 3)
        self.assertEqual(g.degree(v1), 2)

if __name__ == '__main__':
    unittest.main()