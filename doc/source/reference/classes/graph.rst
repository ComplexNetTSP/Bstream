.. _Graph:

=========================================
Graph - Undirected graphs with self loops
=========================================

Summary
+++++++
.. currentmodule:: pybstream
.. autosummary::
   :nosignatures:

   Graph.__init__
   Graph.num_vertices
   Graph.num_edges
   Graph.adjacency
   Graph.add_vertex
   Graph.remove_vertex
   Graph.add_edge
   Graph.has_edge
   Graph.degree
   Graph.label
   Graph.vertex
   Graph.read_csv
   Graph.vertices
   Graph.edges
   Graph.labels

Contents
++++++++

Constructors
------------
.. automethod:: Graph.__init__

Manipulating Graph
------------------
.. automethod:: Graph.num_vertices
.. automethod:: Graph.num_edges
.. automethod:: Graph.adjacency
.. automethod:: Graph.has_edge
.. automethod:: Graph.degree
.. automethod:: Graph.label
.. automethod:: Graph.vertex

Adding and removing nodes and edges
-----------------------------------
.. automethod:: Graph.add_vertex
.. automethod:: Graph.remove_vertex
.. automethod:: Graph.add_edge

Graph iterators
---------------
.. automethod:: Graph.vertices
.. automethod:: Graph.edges
.. automethod:: Graph.labels

Reading and saving graph object
-------------------------------
.. automethod:: Graph.read_csv
