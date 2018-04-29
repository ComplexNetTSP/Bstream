.. _DiGraph:

=========================================
DiGraph - Directed graphs with self loops
=========================================

Summary
+++++++
.. currentmodule:: pybstream
.. autosummary::
   :nosignatures:

   DiGraph.__init__
   DiGraph.num_vertices
   DiGraph.num_edges
   DiGraph.adjacency
   DiGraph.add_vertex
   DiGraph.add_edge
   DiGraph.has_edge
   DiGraph.degree
   DiGraph.label
   DiGraph.read_csv
   DiGraph.vertices
   DiGraph.edges

Contents
++++++++

Constructors
------------
.. automethod:: DiGraph.__init__

Manipulating Graph
------------------
.. automethod:: DiGraph.num_vertices
.. automethod:: DiGraph.num_edges
.. automethod:: DiGraph.adjacency
.. automethod:: DiGraph.has_edge
.. automethod:: DiGraph.degree
.. automethod:: DiGraph.out_degree
.. automethod:: DiGraph.in_degree
.. automethod:: DiGraph.label

Adding and removing nodes and edges
-----------------------------------
.. automethod:: DiGraph.add_vertex
.. automethod:: DiGraph.add_edge

Graph iterators
---------------
.. automethod:: DiGraph.vertices
.. automethod:: DiGraph.edges

Reading and saving graph object
-------------------------------
.. automethod:: DiGraph.read_csv
