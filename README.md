# DS2_Project

Direction to Run:

- Open main.cpp
- in line 7; enter file name containing graph data as 
startingNode endingNode weightOfEdge
- in line 8; enter number of nodes
- in line 9; enter number of edges
- in line 12; enter source node

# Overview
This is an academic technical project presented by team analyzed-structures of CS-201 at Habib University. We have implemented and used Van Emde Boas Tree (a.k.a VEB) in C++ to solve nearest node problem in the best efficient way possible and incorporate its GUI using html.

# Problem Statement
Finding Nearest Node from a source node in O(log(log U)) time complexity.

# Application
Searching for the nearest node from a source node find its application in number of brands and organizations such as in food delivery applications, navigational applictions etc. It play a vital role in these zones and hence opting the most efficient way to serve this purpose is very essential. This project provides a skeleton and prototype of one such application using Van Emde Boas Tree as the primary data structure at back end. We have tried to use the con of VEB including traversal and search in O(log log U) time complexity.  Our goal is to establish that indeed if VEB is used to find nearest node at the back end then it can greatly enhance the overall time complexity of the system. This prototype can be incorporated in any other system which includes finding of nearest node.

# Approach
We have selected Dijsktra Algorithm to find the nearest node as it is a single-source optimized algortithm hence is best suited for our purpose. Van Emde Boass Tree class has been implemented in veb.cpp. This class is being used in dijsktra_on_VEB.cpp, in which we have the running function that takes, source as input and returns the nearest node from this source using Dijsktra Algorithm. The GUI for this prototypte is a html webpage which displays the graph of interest and a search box and a submit button where user must enter the source node i.e. node whose nearest node one has to search for. Following are some snippets of our GUI:
<img src="/doc/3.png" alt="Loadin Graph"/>
<img src="/doc/1.png" alt=""/>
<img src="/doc/2.png" alt=""/>
