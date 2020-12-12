#pragma once

#include "graph.h"
#include <vector>
#include <queue>
#include <stack>

namespace cust_lib {
    /**
     * This class hosts all the search algorithms which are implemented on the dataset's graph. 
     */
    class search_algos {
        public:
            /**
             * This function implements both A* and Dijkstra's Graph Search Algorithms. 
             * Both of the search algorithms are variations of each other, with the latter
             * not having the heuristic value being added to every node's priority.
             * 
             * @param search_graph: Graph in which the values are to be searched in. 
             * @param source: Beginning Vertex in the search.
             * @param destination: Ending Vertex in the search.
             * @param isDijkstra: boolean to decide which mode will the algorithm will run in. True for Dijkstra. 
             * 
             * @return : vector of type Vertex. This represents the path followed. Empty if not found. 
             */ 
            vector<Vertex> search(Graph* search_graph, Vertex source, Vertex destination, bool isDijkstra);

            /**
             * This function implements a BFS style search from source to destination.
             * 
             * @param search_graph: Graph in which the values are to be searched in.
             * @param source: Beginning Vertex in the search.
             * @param destination: Ending Vertex in the search.
             * 
             * @return : vector of type Vertex. This represents the path followed. Empty if not found.
             */ 
            vector<Vertex> BFS(Graph* search_graph, Vertex source, Vertex destination);

            /**
             * This function implements the landmark search algorithm, which is the shortest distance from point A to B through C.
             * Mathematically, it is the shortest path from A to B the one from B to C combined. 
             * This function runs the A* search algorithm on the graph to find the shortest path from A to B through C.
             * 
             * @param search_graph: Graph in which the values are to be searched in.
             * @param source: Beginning Vertex in the search.
             * @param landmark: Vertex through which the path has to mandatorily pass.
             * @param destination: Ending Vertex in the search.
             * 
             * @return vector of type Vertex. This represents the path followed. Empty if not found.
             */ 
            vector<Vertex> landmark_search(Graph* search_graph, Vertex source, Vertex landmark, Vertex destination);
        private:
            /**
             * This function returns the heuristic value of Vertex A and B. 
             * 
             * @param graph: Graph in which the values are to be searched.
             * @param A: First Vertex.
             * @param B: Second Vertex.
             */ 
            int calc_heuristic(Graph* graph, Vertex A, Vertex B);

            /**
             * The following struct is a specific implementation of a priority queue which is used by our search algorithm.
             * Adapted from: https://www.redblobgames.com/pathfinding/a-star/implementation.cpp
             */ 
            struct search_p_queue {
                /**
                 * Define a pair which will be stored inside the priority queue.
                 * int: Priority of the node.
                 * Vertex: The node's name.
                 */ 
                typedef std::pair<int, Vertex> node_elem;
                
                /**
                 * Priority queue data structure.
                 */ 
                std::priority_queue<node_elem, std::vector<node_elem>, std::greater<node_elem>> node_queue;

                /**
                 * This function returns whether the queue is empty.
                 * 
                 * @return : if node_queue is empty or not.
                 */
                inline bool empty() const {
                    return node_queue.empty();
                }

                /**
                 * This function inserts a Vertex with a set priority into the priority queue.
                 * 
                 * @param item: Vertex to insert.
                 * @param priority: priority of the vertex.
                 */
                inline void put(Vertex item, int priority) {
                    node_queue.emplace(priority, item);
                }

                /**
                 * Returns the vertex at the top of the priority queue. Pops the vertex off the queue as well.
                 * 
                 * @return : The vertex at the top of the priority queue.
                 */
                Vertex get() {
                    Vertex toReturn = node_queue.top().second;
                    node_queue.pop();
                    return toReturn;
                }
            };
    };
}
