import unittest
import pybstream

class TestGraph(unittest.TestCase):

    def test_Graph(self):
        """Tests the class Graph constructor."""
        g = pybstream.Graph()
        self.assertFalse(g.is_directed())
        self.assertEqual(g.num_vertices(), 0)
        self.assertEqual(g.num_edges(), 0)

        g1 = pybstream.Graph(100)
        self.assertEqual(g1.num_vertices(), 100)
        self.assertEqual(g1.num_edges(), 0)

    def test_DiGraph(self):
        """Tests the class DiGraph constructor."""
        g = pybstream.DiGraph()
        self.assertTrue(g.is_directed())
        self.assertEqual(g.num_vertices(), 0)
        self.assertEqual(g.num_edges(), 0)

        g1 = pybstream.DiGraph(100)
        self.assertEqual(g1.num_vertices(), 100)
        self.assertEqual(g1.num_edges(), 0)

    def test_Graph_add_vertex(self):
        """Tests the class Graph add_vertex"""
        g = pybstream.Graph()
        g.add_vertex()
        self.assertEqual(g.num_vertices(), 1)
        self.assertEqual(g.num_edges(), 0)

    def test_Graph_add_edge(self):
        """Tests the class Graph add_edge."""
        g = pybstream.Graph()
        v1 = g.add_vertex()
        v2 = g.add_vertex()
        g.add_edge(v1, v2)
        self.assertTrue(g.has_edge(v1, v2))
        self.assertTrue(g.has_edge(v2, v1))
        self.assertEqual(g.num_vertices(), 2)
        self.assertEqual(g.num_edges(), 1)

    def test_Graph_degree(self):
        """Tests the class Graph degree."""
        g = pybstream.Graph()
        v1 = g.add_vertex()
        v2 = g.add_vertex()
        v3 = g.add_vertex()
        g.add_edge(v1, v2)
        g.add_edge(v2, v3)
        g.add_edge(v3, v1)
        self.assertEqual(g.num_vertices(), 3)
        self.assertEqual(g.num_edges(), 3)
        self.assertEqual(g.degree(v1), 2)

        # check and the Handshaking lemma
        sum = 0
        for v in g.vertices():
            sum += g.degree(v)
        self.assertEqual(sum, 2*g.num_edges())

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

        # check and the Handshaking lemma
        sum = 0
        for v in g.vertices():
            sum += g.degree(v)
        self.assertEqual(sum, 2*g.num_edges())

    def test_Graph_read_csv(self):
        """Tests the class Graph read_csv."""
        csv = pybstream.CSVReader()
        g = csv.read_graph("./tests/python_graph_tests/edges.csv")
        self.assertFalse(g.is_directed())
        self.assertEqual(g.num_vertices(), 4);
        self.assertEqual(g.num_edges(), 5);

    def test_Graph_adjacency(self):
        """Tests the class Graph adjacency."""
        result = [[0.0, 1.0, 1.0], [1.0, 0.0, 1.0], [1.0, 1.0, 0.0]]

        g = pybstream.Graph()
        v1 = g.add_vertex()
        v2 = g.add_vertex()
        v3 = g.add_vertex()
        g.add_edge(v3, v1)
        g.add_edge(v2, v3)
        g.add_edge(v1, v2)

        self.assertEqual(g.adjacency().tolist(), result)

    def test_Graph_read_csv(self):
        """Tests the class Graph read_csv."""
        g = pybstream.Graph()
        g.read_csv("./tests/python_graph_tests/edges.csv")

    def test_Graph_operator(self):
        """Tests the class Graph overloaded operators."""
        g = pybstream.Graph()
        g.add_edge("A", "B")

        self.assertListEqual(g.labels(), ["A", "B"])

        cpt = 0
        for l in g.labels():
            self.assertEqual(g[l], cpt)
            cpt += 1

        with self.assertRaises(RuntimeError):
            g["a"]

        res = iter(["A", "B"])
        for v in g.vertices():
            self.assertEqual(g[v], next(res))

        with self.assertRaises(RuntimeError):
            g[100]

if __name__ == '__main__':
    unittest.main()