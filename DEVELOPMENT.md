## CS 225 Final Project

## Development Journal

**Week 1 (November 17 - 24) :**

During the first week, we finalized our idea and what the output for our program was going to
be and how we would go about achieving our goal. We decided upon three approaches:

- A breadth-first search (BFS) traversal to find the most efficient path from a given source point to the desired destination input by the user.
- A* search algorithm, a very practical algorithm used in travel routing systems, such as the one like ours, to obtain the most efficient path from point A to point B with the smallest ‘cost’, in this case, the least amount of time taken (as per our used dataset).
- Dijkstra’s Algorithm, a similar approach that produces a shortest-path tree that is traversed by fixing a node as the source node, and finding the shortest paths to all other nodes in the graph.

We began researching on these algorithms and made a brief plan on how we would go about finishing each of these approaches. We also assigned each of these approaches, and the rest of the project deliverables to different group members.

**Week 2 (November 25 - December 1):**

This week was during our Thanksgiving break, so we did not get a whole lot done practically. The primary outcomes were writing pseudocode for each of these algorithms. We made skeleton functions for each of the approaches. We also wrote the main function, the Makefile, the README.md files, and imported our dataset csv files and the wrote test cases.

**Week 3 (December 2 - December 9):**

During the final week, each member delved into the implementations of their assigned algorithms - BFS, A*, and Dijkstra. We ran into a few issues with integrating the theoretical algorithms and pseudocode into our actual implementations within the context of our dataset, but were able to solve them by doing further research and collaborating during our triweekly meetings. We had the most issues with the A* algorithm, as we weren’t getting the desired output and it took quite some time to debug. Furthermore, during testing of our programs, we also had to manually check the shortest paths from the dataset to confirm if our output was correct.