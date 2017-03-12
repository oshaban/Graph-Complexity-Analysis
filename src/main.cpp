/**
    PMII Project 2: Project Type IB.

    Purpose:    Investigates the shortest path problem.
                    Implements the Dijkstra's and the  Floyd Warshall's Algorithm
                    Generates 100 graphs for with nodes = 64, 128, 256,..., 8192
                    Edge weights are randomly generates in range [1,15]
                    Randomly generates a source and destination node
                    Displays number of hops as well as the numerical distance from source to destination

    @author   Omar Shaban
*/

#include <iostream>
#include <ctime> //used to seed based off time
#include <cstdlib> //used for rand()
#include <vector> //used for vectors
#include <stack> //used for stacks
#include <iomanip> //used for setw()
#include "Graph.h"

using namespace std;

/* Prints a 1D vector of integers
* @param    vec: vector to print
*/
void printVector(vector<int> vec)
{
    for(int i=0; i<vec.size();i++)
    {
        cout << vec[i] << " ";
    }
    cout << endl;
}


int main()
{
    srand(time(NULL)); //seeds based off time

    //Declaring & initializing counters
    int hops_D=0;
    int shortestDistance_D=0;
    int hops_F=0;
    int shortestDistance_F=0;

    //Displays header
    cout << "---------------------------------------------------------------------------------------------------------" << endl;
    cout<<  "         ||      Dijkstra's                             ||                Floyd Warshall               ||" << endl;
    cout << " Nodes   ||  Avg. Dist.  |  Avg. Hops | Avg. Operations ||  Avg. Dist.  |  Avg. Hops | Avg. Operations ||" << endl;
    cout << "---------------------------------------------------------------------------------------------------------" << endl;

    ///Create 100 random graphs, from 64, 128, 256, 512, 1024, 2048, 4096, 8192
    for(int nodes=64; nodes<=8192; nodes*=2)
    {
        //keeps track of average number of hops for Dijkstra's and Floyd
        double avgHops_D=0;
        double avgDistance_D=0;
        double avgOperations_D =0; //average the number of operations over the 100 graphs

        double avgHops_F=0;
        double avgDistance_F=0;
        double avgOperations_F =0; //average the number of operations over the 100 graphs

        //Create 100 random graphs, from 64, 128, 256, ... to 8192
        int numGraphs = 100;

        for(int i=0; i<numGraphs; i++)
        {
            int source=rand()%nodes; //create a source node
            int dest=rand()%nodes; //create destination node

            int operationCounter_D = 0; //create a counter to keep track of operations for Dijkstra's
            int operationCounter_F = 0; //create a counter to keep track of operations for Floyd

            //Initializing counters
            hops_D=0;
            shortestDistance_D=0;
            hops_F=0;
            shortestDistance_F=0;

            Graph g(nodes,source,dest); //Creates a graph of size nodes x nodes, with a source node and a destination node

            //Algorithms return the shortest path
            shortestDistance_D = g.Dijkstra(hops_D,operationCounter_D);
            shortestDistance_F = g.FloydWarshall(hops_F,operationCounter_F);

            //Update totals for Dijkstra's Alg.
            avgHops_D+=hops_D;
            avgDistance_D+=shortestDistance_D;
            avgOperations_D+=operationCounter_D;

            //Update totals for Floyd Alg.
            avgHops_F+=hops_F;
            avgDistance_F+=shortestDistance_F;
            avgOperations_F+=operationCounter_F;

        }//end for

        //Calculate the averages
        avgHops_D=avgHops_D/static_cast<double>(numGraphs);
        avgDistance_D = avgDistance_D/static_cast<double>(numGraphs);
        avgOperations_D = avgOperations_D/static_cast<double>(numGraphs);

        avgHops_F=avgHops_F/static_cast<double>(numGraphs);
        avgDistance_F = avgDistance_F/static_cast<double>(numGraphs);
        avgOperations_F = avgOperations_F /static_cast<double>(numGraphs);

        //Displays the number of nodes, average distance and average hops
        cout << setw(6) << nodes << setw(15) << avgDistance_D << setw(15) << avgHops_D << setw(20) << avgOperations_D <<
            setw(12) << avgDistance_F << setw(12) << avgHops_F << setw(23) << avgOperations_F << endl;

    }

    return 0;
}
