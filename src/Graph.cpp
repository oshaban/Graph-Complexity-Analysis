#include "Graph.h"

#include <iostream>
#include <vector> //used for vectors
#include <cstdlib>
#include <limits> //used for infinity
#include <stack> //used for stacks

using namespace std;

int infinity = std::numeric_limits<int>::max(); //max integer limit is used for infinity: DO NOT ADD TO INFINITY, OR OVERFLOW WILL OCCUR

/* Default Constructor
* Creates a Graph size 0x0, with source node =0 and destination node = 0
*/
Graph::Graph()
{
    nodes = 0;
    source = 0;
    dest = 0;
}

//Overloaded constructor to create a Graph
    //Creates a graph with n nodes source node s and destination node d
    //Edges weights are randomly generated in range [1,15]
Graph::Graph(int n, int s, int d)
{
    nodes = n;
    dest = d;
    source = s;
    createGraph(n);

}

// Prints a Graph represented by an adjacency matrix
void Graph::printGraph()
{
    for(int i=0; i<Matrix.size(); i++)
    {
        for(int j=0; j<Matrix[i].size(); j++)
        {
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


/* Creates a graph with n nodes, represented by an adjacency matrix.
* Edges weights are randomly generated in range [1,15]
* @param    n : number of nodes in the graph
*/
void Graph::createGraph(int n)
{
     //Creates a vector of all 0's, size nodes x nodes
    std::vector<std::vector<int> > vec(nodes,std::vector<int>(nodes));

    //Puts random edgeWeights in the matrix ranging from [1, 5]
    for(int i=0; i<nodes; i++)
    {
        for(int j=0; j<nodes; j++)
        {
            int edgeWeight = rand()%15 + 1; ///Changed to random edge weight in range [1,15]
            vec[i][j] = edgeWeight;
        }
    }

    /* Uncomment to set edge weights of 0 to infinity
    for(int i=0; i<Matrix.size(); i++)
    {
        for(int j=0; j<Matrix[i].size(); j++)
        {
            if(Matrix[i][j]==0)
            {
                Matrix[i][j] = infinity;
            }
        }
    }
    */

    Matrix = vec;

}

int Graph::getNodes(){return nodes;}//Gets the number of nodes
int Graph::getSource(){return source;}//Gets source node index
int Graph::getDest(){return dest;}//Gets destination node index

void Graph::setSource(int s){source = s;}//Sets the source node index
void Graph::setDest(int d){dest = d;}//Sets the destination node index



/* Finds the shortest path between a source and destination node, using Dijkstra's Algorithm
* @param    numHops: upon returning numHops will contain the number of Hops needed to go from source to destination
* @param    numOperations: upon returning numOperations will contain the number of operations performed by the function
* @return   int : returns distance of the shortest path from source to destination
*/
int Graph::Dijkstra(int &numHops, int &numOperations)
{
    numOperations =0; //initially the number of operations is 0

    std::vector<int> distance(nodes,0); //keep track of distances from the source to all other nodes,
    std::vector<int> visited(nodes,0);//keeps track of all the nodes we have visited, initially we haven't visited any nodes
        //0 means not visited
        //1 means visited
    std::vector<int> path(nodes,source); //stores the path of the shortest path

    numOperations +=3; //3 operations for assignments


    path[0]=source; //path starts off from source node
    distance = Matrix[source]; //set distance vector equal to first row of the Matrix
    distance[source] = 0; //distance from source to source is 0

    int currentNode = source; //initially start from the source

    bool allVisited = 0; //initially assume not all the nodes have been visited

    numOperations+=5; //5 operations for assignments

    ///This while loop finds the distances between the source and all other nodes
    numOperations++; //operation for comparison of while loop
    while(allVisited==0) //keep looping until we have visited all the nodes
    {
        numOperations++; //operation for comparison in while loop

        //For the current node, look at all of it's neighbors
            //find the distance from the neighbors to the source node
            //If this is less than the current distance from the neighbor to the source node, then update the distance

        numOperations+=2; //operation for assignment of tempDistance and i
        int tempDistance =0;
        for(int i=0; i<nodes; i++)
        {
            numOperations+=3; //operation for comparison of i, incrementing i, and comparison in if
            if(i!=currentNode)
            {
                numOperations++;//operation of assignment
                tempDistance = distance[currentNode] + Matrix[currentNode][i]; //find the distance from the neighbors to the source node

                //If this is less than the current distance from the neighbor to the source node, then update the distance
                numOperations++;//operation for comparison
                if(tempDistance<distance[i] && Matrix[currentNode][i]!=infinity &&distance[currentNode]!=infinity)
                {
                    distance[i] = tempDistance;
                    path[i] = currentNode;
                    numOperations+=2; //operations for assignment
                }

            }//end if

        }//end for

        numOperations+=2; //operation for assignment and comparison in if
        visited[currentNode] = 1; //mark the current node as visited

        if(visited[dest]==1) //if destination has been visited, then stop the algorithm
        {
            break;
        }

        //Find the next node to visit
            //Visit the node with the smallest distance from source, that has not already been visited
        int smallest = infinity;
        int smallestIndex = -1;
        numOperations+=2; //operations for assignment

        numOperations++;//operation for assignment of i

       for(int i=0; i<nodes; i++) //scan thru
       {
           numOperations+=3; //operation for comparison in for, and incrementing i, comparison in if

           if(visited[i]==0) //pick only the non visited nodes
           {
               numOperations++;//operation for comparison in if
                if(distance[i]<smallest)
                {
                    smallest = distance[i];
                    smallestIndex = i;
                    numOperations+=2; //operations for assignment
                }
           }

       }//end for

        currentNode = smallestIndex; //update the next node to visit when the loop starts over
        numOperations++; //operation for assignment


        allVisited=1; //assume all nodes have been visited
        numOperations++;
        //keep looping until we have visited all the nodes
        //Check if all the nodes have been visited

        numOperations++;
        for(int i=0; i<visited.size();i++)
        {
            numOperations+=3; //operation for comparison of i, incrementing i, comparison of vec[i]

            if(visited[i]==0)
            {
                allVisited=0; //not all the nodes have been visited
                numOperations++;
            }
        }

    }// end while

    //Calculate the number of hops based on the path vector
    numOperations++;
    if(distance[dest]!=infinity)//if distance to destination is infinity, then there is no path
    {
        //figures out the path to the destination
            //path is stored in reverse order in path, so push onto stack then pop to get the actual path
        stack<int> S;
        int j = dest;
        S.push(j);

        numOperations+=3;

        do
        {
            j = path[j];
            S.push(j);
            numOperations+=2;
        }while(j!=source);
        numOperations++;


        //Uncomment to print the path
        //cout << "Path: " << endl;
        int hops =0;
        numOperations++;

        while(S.empty()==0)
        {
            numOperations++;
            //cout << S.top();
            S.pop();

            //if(S.empty()==0){cout << " -> ";}
            hops++;

            numOperations+=2;
        }
        numOperations++;

        //cout << endl;

        numHops = --hops;
        numOperations++;
    }
    else//(distance[dest]==infinity)
    {
        numHops = -1; //-1 is returned for hops if no path to destination
        numOperations++;
        //cout << "There is no path to the destination" << endl;
    }

    return distance[dest]; //returns distance of the shortest path from source to destination

 }

 /* Finds the shortest path between a source and destination node using Floyd Warshall's Algorithm
* @param    numHops: upon returning numHops will contain the number of Hops needed to go from source to destination
* @param    numOperations: upon returning numOperations will contain the number of operations performed by the function
* @return   int : returns distance of the shortest path from source to destination
*/
int Graph::FloydWarshall(int &numHops, int &numOperations)
{
    numOperations =0; //initially the number of operations is 0

    std::vector<std::vector<int> > Path(nodes,std::vector<int>(nodes));
    numOperations++;
    //keeps track of the path
        //path[s][d] lets us know which node was taken last to go from s to d

    //go thru every iteration of the matrix
    numOperations++; //initializing k
    for(int k=0; k<nodes; k++)
    {
        numOperations+=2; //comparison & incrementing k

        numOperations++; //initializing i
        for(int i=0; i<nodes; i++)
        {
            numOperations+=2; //comparison and incrementing

            numOperations++; //initializing j
            for(int j=0; j<nodes; j++)
            {
                numOperations+=2; //comparison and incrementing

                numOperations++; //comparison in if
                if(Matrix[i][k] + Matrix[k][j] < Matrix[i][j] && Matrix[i][k]!=infinity && Matrix[k][j]!=infinity)
                {
                    Matrix[i][j] = Matrix[i][k] + Matrix[k][j]; //shorter path is found
                    Path[i][j] = k; //add it to the path matrix

                    numOperations+=2;
                }
            }
        }
    }

    //Using the path matrix, rebuild the path:

    numOperations++;
    vector<int> pathRev; //contains the path in reverse order

    numOperations++;
    if(Path[source][dest]==0 && Matrix[source][dest]==infinity) //case1: there is no path from source to dest
    {
        cout << "no path" << endl;
        return -1; //no path from source to destination
        numOperations++;
    }
    else if (Path[source][dest]==0 && Matrix[source][dest]!=infinity) //case2: a single hop is needed from source to dest
    {
        pathRev.push_back(dest);
        pathRev.push_back(source);
        numOperations+=2;
    }
    else //case3: there is a path from source to dest, use the Path matrix to construct the path; note path constructed in rev. order
    {
        numOperations+=2;
        pathRev.push_back(dest);

        int tempDest = dest;


        while(tempDest!=0)
        {
            numOperations++;

            tempDest = Path[source][tempDest];
            numOperations++;

            numOperations++;
            if(tempDest!=0)
            {
                pathRev.push_back(tempDest);
                numOperations++;
            }
        }
        numOperations++;

        pathRev.push_back(source);
        numOperations++;
    }

    numHops = pathRev.size()-1; //Number of hops is the number of nodes in path - 1
    numOperations++;


    return Matrix[source][dest]; //return the distance from source to destination if there is a path

}//end function


