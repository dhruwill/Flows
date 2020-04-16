/** @file */ 
/*! \mainpage Algorithm: Ford Fulkerson
 *
 * 
 *
 * @section Made_by
        Dhruvil Shah 2017A7PS1566H \n
        Daivik Purani 2017A7PS0166H \n
        Vivek Soni 2017A7PS0173H \n
 *
 * @section Description
    The algorithm finds maximum matchin in a Bipartite graph using a FordFulkerson approach with an average case complexity of O(edges*interations) \n 
    The steps involved can be described as folows: \n
        E number of edge 
        f(e) flow of edge 
        C(e) capacity of edge 

        1) Initialize : max_flow = 0  
                        f(e) = 0 for every edge 'e' in E 
                    
        2) Repeat search for an s-t path P while it exists.   
           a) Find if there is a path from s to t using BFS
              or DFS. A path exists if f(e) < C(e) for 
              every edge e on the path.
           b) If no path found, return max_flow.
           c) Else find minimum edge value for path P
                
              // Our flow is limited by least remaining
              // capacity edge on path P.
              (i) flow = min(C(e)- f(e)) for path P ]
                     max_flow += flow
              (ii) For all edge e of path increment flow 
                     f(e) += flow

        3) Return max_flow 
 *
 * @section Input
        > First line should contain the name of the input file. \n
        > Second line should contain the name of the output file. \n
 *
 * @section File
        > First line should contain 2 integers, the number of nodes(n) and edges(m) in the graph, seperated by a space \n
        > The next m lines should contain 2 integers x and y denoting that there is an edges from x to y ( x --> y)  \n
 *
 */

#pragma GCC optimize ("-O3")
#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
#include <map>
#define IOS ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
#include<vector>
#include<queue>
#include <cstring>
#include <unordered_map>
#define pb push_back
using namespace std;
#include <chrono>
using namespace std::chrono;
#include "bp.h" /*!< Including the Flow class to create the graph and perform necessary operations on it */
int main()
{
    // char inp[50];  /*!< Input file name */
    // char outp[50]; /*!< Output file name */
    // printf("Enter input filename: ");
    // scanf("%s",inp);
    // printf("Enter output filename: ");
    // scanf("%s",outp);
    // const char *cinp = inp;
    // const char *coutp = outp;
    freopen("inp1b.txt","r",stdin);
    freopen("out.txt","w",stdout);
    IOS;
    int nodes; /*!< nodes: Number of nodes in the graph */
    int edges; /*!< edges: Number of edges in the graph */
    cin>>nodes>>edges;
    int val=0;  /*!< Val variable is used to reorder the nodes since many can be missing*/
    int inp1;   /*!< Inp1 stores the node having outgoing edge i.e inp1 --> inp2 */
    int inp2;   /*!< Inp2 stores the node having incoming edge */
    Flow diG(nodes,edges);  /*!< Object dig of glass Flow is createdand initialised with number of nodes*/

    for(int i = 1;i<= edges;i++)
    {
        cin>>inp1>>inp2;
        diG.reorder[inp1]=inp1;
        diG.reorder[inp2]=inp2;
     //   if(!diG.reorder[inp1])
     //       diG.reorder[inp1]=++val,diG.rehash[val]=inp1;  /*!< If Inp1 has not occurred before then change its value to the current max possible value*/
     //   if(!diG.reorder[inp2])
     //       diG.reorder[inp2]=++val,diG.rehash[val]=inp2;  /*!< If Inp2 has not occurred before then change its value to the current max possible value*/
        diG.addEdge(diG.reorder[inp1],diG.reorder[inp2]); /*!< Task 1: Creating Adjacency list*/
    }
    
    auto start = high_resolution_clock::now();   /*!< Start the timer to analyse complexity of code*/
    diG.printSTpartition(0,nodes+1); /*!< Task 1&2: Applying the ford-fulkerson approach*/
    auto stop = high_resolution_clock::now();   /*!< End the Timer*/
    auto duration = duration_cast<microseconds>(stop - start); /*!< Duration gives the time taken by the Algorithm to complete the process */
    cout << "\nTime taken by function: "
         << (double)duration.count()/1000<< " ms" << endl;
}
