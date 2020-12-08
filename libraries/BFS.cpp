#include "graph.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#pragma once 

using namespace std;

class Graph {
    int V;
    list<int> *adjacent;  

    public:
    Graph(int v); //graph constructor (redundant?)
    void BFS(int source);

};

    Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::BFS(int source)
{
    bool *isVisited = new bool[V];
    for(int i = 0; i < V; i++){
        isVisited[i] = false;
    }

    list<int> queue; // for BFS
 
    isVisited[source] = true;
    queue.push_back(source); //enqueue node
 
    list<int>::iterator i; // to find adjacent vertices
 
    while(queue.empty() == false){
        source = queue.front();
        cout << source << " ";
        queue.pop_front(); // dequeue
        for (i = adj[source].begin(); i != adj[source].end(); ++i){
            if (!isVisited[*i]){
                isVisited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}
 
int main()
{
    Graph(true, 4, 69); //ignore line - insert graph specification....69 is the seed fyi...4 is num_vertices
    Graph.addEdge(0, 1);
    Graph.addEdge(0, 2);
    Graph.addEdge(1, 2);
    Graph.addEdge(2, 0);
    Graph.addEdge(2, 3);
    Graph.addEdge(3, 3);
 
    Graph.BFS(1);
    return 0;
}