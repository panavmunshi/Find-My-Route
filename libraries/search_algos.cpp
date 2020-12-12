#include "search_algos.h"

using namespace cust_lib;
using namespace std;

vector<Vertex> search_algos::search(Graph* search_graph, Vertex source, Vertex destination, bool isDijkstra) {
    /* Declare the search algorithm's priority queue and add the source with priority 0. */
    /* The priority here is the cost of traversing. */
    search_p_queue frontier;
    frontier.put(source, 0);

    /* Declare member structures which will help track the shortest path. */
    std::unordered_map<Vertex, Vertex> parentToChildMap;
    std::unordered_map<Vertex, int> vertexToCost;
    std::vector<Vertex> toReturn;

    /* Set the source's parent as "NULL". This means that there is no preceding node to source. */
    parentToChildMap[source] = "NULL";

    /* Set the cost at source to 0. This is because the cost of moving from source to source is 0. */
    vertexToCost[source] = 0;

    /* Loop until either all nodes have been visited or until we reach our destination. */
    while (!frontier.empty()) {
        /* Get the vertex with the highest priority. */
        Vertex curr = frontier.get();

        /* If we have reached our destination, break from the loop. Else, continue. */
        if (curr == destination) {
            break;
        } else {
            /* Run through all the neighbours of the curr vertex. */
            for (Vertex next : search_graph->getAdjacent(curr)) {
                /* Calculate the cost of movement for each of the neighbors. */
                int new_cost = vertexToCost[curr] + search_graph->getEdgeWeight(curr, next);
                /* If we have not visited this cell or if the new_cost is lesser than the previous cost of moving till this neighbor, step in. */
                if (vertexToCost.find(next) == vertexToCost.end() || new_cost < vertexToCost[next]) {

                    /* Set/update the cost of the Vertex next. */
                    vertexToCost[next] = new_cost;
                    
                    /* Calculate the priority. If this algorithm is running in Dijkstra mode, the priority is the new_cost itself. */
                    /* If it is running in A* mode, the priority is new_cost + the heuristics value. */
                    int priority = (isDijkstra) ? new_cost : new_cost + calc_heuristic(search_graph, source, destination);

                    /* Add the next node to the priority queue and set its parent to current. */
                    frontier.put(next, priority);
                    parentToChildMap[next] = curr;
                }
            }
        }
    }

    /* As we are tracking backwards, simply pushing to the vector will result in a reverse traversal. */
    /* Use a stack to fix this. */
    std::stack<Vertex> reversal_stack;
    Vertex current = destination;

    while (current != "NULL") {
        reversal_stack.push(current);
        if (parentToChildMap.find(current) == parentToChildMap.end()) {
            return vector<Vertex>();
        }
        current = parentToChildMap[current];
    }

    /* Pop off all the Vertices from the stack and put them inside the vector. */
    while (!reversal_stack.empty()) {
        toReturn.push_back(reversal_stack.top());
        reversal_stack.pop();
    }

    /* Return result. */
    return toReturn;
}

int search_algos::calc_heuristic(Graph* graph, Vertex A, Vertex B) {
    /* Call the graph's internal heuristic function and return its value. */
    return graph->get_edge_count(A, B);
}

vector<Vertex> search_algos::BFS(Graph* search_obj, Vertex source, Vertex dest)
{   
    /* Initialize map to store every vertex's visited state. Initialize map to false. */
    unordered_map<Vertex, bool> isVisited;
    unordered_map<Vertex, Vertex> came_from;
    vector<Vertex> toReturn;

    for (Vertex v : search_obj->getVertices()) {
        isVisited[v] = false;
    }

    /* Initialize the bfs queue. */
    queue<Vertex> bfs_queue;
    
    /* Set the visited status of source to true. */
    isVisited[source] = true;

    /* This map helps in back-tracking to the source from the destination. Set source's predecessor to "NONE". */
    came_from[source] = "NONE";
    
    /* Enqueue source vertex. */
    bfs_queue.push(source);

    /* Loop through all nodes or until we've reached the destination. */
    while(!bfs_queue.empty()){
        /* Get the vertex at front and pop it off the queue. */
        Vertex curr = bfs_queue.front();
        bfs_queue.pop();

        /* If this is the destination, break off the loop. */
        if (curr == dest) {
            break;
        }
        
        /* Loop through all the neighbours of the current node. */
        for (Vertex q : search_obj->getAdjacent(curr)) {
            /* If Vertex q hasn't been visited, push it to the queue and mark it visited. Additionally, set its parent to curr. */
            if (!isVisited[q]) {
                isVisited[q] = true;
                came_from[q] = curr;
                bfs_queue.push(q);
            }
        }
    }

    /* As we are tracking backwards, simply pushing to the vector will result in a reverse traversal. */
    /* Use a stack to fix this. */
    std::stack<Vertex> reversal_stack;
    Vertex current = dest;

    while (current != "NONE") {
        reversal_stack.push(current);
        if (came_from.find(current) == came_from.end()) {
            return vector<Vertex>();
        }
        current = came_from[current];
    }

    /* Pop off all the Vertices from the stack and put them inside the vector. */
    while (!reversal_stack.empty()) {
        toReturn.push_back(reversal_stack.top());
        reversal_stack.pop();
    }

    /* Return result. */
    return toReturn;
}

vector<Vertex> search_algos::landmark_search(Graph* search_graph, Vertex source, Vertex landmark, Vertex destination) {
    /* Declare the return vector. */
    vector<Vertex> toReturn;

    /* Get the shortest path from source to landmark using A* search. */
    vector<Vertex> a_to_b = search(search_graph, source, landmark, false);

    /* If this vector is empty, return an empty vector as this path isn't posssible. */
    if (a_to_b.empty()) {
        return toReturn;
    }

    /* Get the shortest path from landmark to destination using A* search. */
    vector<Vertex> b_to_c = search(search_graph, landmark, destination, false);

    /* If this vector is empty, return an empty vector as this path isn't posssible. */
    if (b_to_c.empty()) {
        return toReturn;
    }

    /* Recreate the vector to be returned using the other two vectors. */
    toReturn.push_back(source);
    for (Vertex v : a_to_b) {
        if (v != source && v != landmark) {
            toReturn.push_back(v);
        }
    }

    toReturn.push_back(landmark);
    for (Vertex q : b_to_c) {
        if (q != landmark && q != destination) {
            toReturn.push_back(q);
        }
    }

    toReturn.push_back(destination);

    /* Return the result. */
    return toReturn;
}