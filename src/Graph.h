#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iomanip>
#include <limits> //used for infinity

using namespace std;

class Graph
{
    public:

        Graph(); //Creates a Graph size 0x0, with source node =0 and destination node = 0

        //Overloaded constructor to create a Graph
            //Creates a graph with n nodes, with source node s and destination node d
        Graph(int n, int s, int d);

        void createGraph(int n); //Creates a graph, and randomizes the source node, destination node, and the number of nodes
        void printGraph(); //Prints a Graph represented by an adjacency matrix

        int getNodes(); //Gets the number of nodes
        int getSource(); //Gets source node index
        int getDest(); //Gets destination node index

        void setSource(int s); //Sets the source node index
        void setDest(int d); //Sets the destination node index

        //Finds the shortest path between a source and destination node, using Dijkstra's Algorithm
        int Dijkstra(int &numHops, int &numOperations);
        //Finds the shortest path between a source and destination node, using Floyd Warshall's Algorithm
        int FloydWarshall(int &numHops, int &numOperations);

    protected:

    private:
        vector< vector<int> > Matrix; //Adjacency Matrix representation of a Graph
        int source; //source node
        int dest; //destination node
        int nodes; //stores the number of nodes

};

#endif // GRAPH_H
