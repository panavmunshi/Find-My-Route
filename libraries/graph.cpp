#include "graph.h"

const Vertex Graph::InvalidVertex = "_CS225INVALIDVERTEX";
const Edge_Weight Graph::InvalidWeight = Edge_Weight(-1, -1, -1, "");
const string Graph:: InvalidLabel = "_CS225INVALIDLABEL";
const Edge Graph::InvalidEdge = Edge(Graph::InvalidVertex, Graph::InvalidVertex, Graph::InvalidWeight, Graph::InvalidLabel);

Graph::Graph(bool weighted) : weighted(weighted),directed(false),random(Random(0))
{
}

Graph::Graph(bool weighted, bool directed) : weighted(weighted),directed(directed),random(Random(0))
{
}

Graph::Graph(bool weighted, int numVertices, unsigned long seed)
    :weighted(weighted),
      directed(false),
     random(Random(seed)) 
{
    if (numVertices < 2)
    {
     error("numVertices too low");
     exit(1);
    }

    vector<Vertex> vertices;
    for (int i = 0; i < numVertices; i++)
    {
        insertVertex(to_string(i));
        vertices.push_back(to_string(i));
    }

    // make sure all vertices are connected
    random.shuffle(vertices);
    Vertex cur = vertices[0];
    for (size_t i = 0; i < vertices.size() - 1; ++i)
    {
        Vertex next = vertices[i + 1];
        insertEdge(cur, next, "", Edge_Weight());
        if (weighted) 
        {
            setEdgeWeight(cur, next, "", Edge_Weight(random.nextInt(), random.nextInt(), random.nextInt(), ""));
        }
        cur = next;
    }

    // keep the graph from being overpopulated with edges,
    //  while still maintaining a little randomness
    int numFailures = 0;
    int idx = 0;
    random.shuffle(vertices);
    while (numFailures < 2) 
    {
        if (!insertEdge(vertices[idx], vertices[idx + 1], "", Edge_Weight())) 
        {
            ++numFailures;
        } 
        else 
        {
            // if insertEdge() succeeded...
            if (weighted)
                setEdgeWeight(vertices[idx], vertices[idx + 1], "",
                              Edge_Weight(random.nextInt(), random.nextInt(), random.nextInt(), ""));
            ++idx;
            if (idx >= numVertices - 2) 
            {
                idx = 0;
                random.shuffle(vertices);
            }
        }
    }
}

vector<Vertex> Graph::getAdjacent(Vertex source) const 
{
    auto lookup = adjacency_list.find(source);

    if(lookup == adjacency_list.end())
        return vector<Vertex>();

    else
    {
        vector<Vertex> vertex_list;
        unordered_map <Vertex, vector<Edge>> & map = adjacency_list[source];
        for (auto it = map.begin(); it != map.end(); it++)
        {
            vertex_list.push_back(it->first);
        }
        return vertex_list;
    }
}


Vertex Graph::getStartingVertex() const
{
    return adjacency_list.begin()->first;
}

vector<Vertex> Graph::getVertices() const
{
    vector<Vertex> ret;

    for(auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        ret.push_back(it->first);
    }

    return ret;
}

Edge Graph::getEdge(Vertex source, Vertex destination, string flight_data) const
{
    if(assertEdgeExists(source, destination, flight_data, __func__) == false)
        return Edge();
    
    for (auto it = adjacency_list[source][destination].begin(); it != adjacency_list[source][destination].end(); ++it) {
        if (it->getWeight().flight_data == flight_data) {
            return *it;
        }
    }
    return InvalidEdge;
}

vector<Edge> Graph::getMultiEdges(Vertex source, Vertex destination) const {
    if (adjacency_list.find(source) != adjacency_list.end() &&
        adjacency_list[source].find(destination) != adjacency_list[source].end()) {
            return adjacency_list[source][destination];
    }
    return vector<Edge>();
}

vector<Edge> Graph::getEdges() const
{
    if (adjacency_list.empty())
        return vector<Edge>();

    vector<Edge> ret;
    set<pair<Vertex, Vertex>> seen;

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); it++)
    {
        Vertex source = it->first;
        for (auto its = adjacency_list[source].begin(); its != adjacency_list[source].end(); its++)
        {
            Vertex destination = its->first;
            if(seen.find(make_pair(source, destination)) == seen.end())
            {
                //this pair is never added to seen
                //ret.push_back(its->second);
                for (const Edge& edges : its->second) {
                    ret.push_back(edges);
                }
                seen.insert(make_pair(source,destination));
                if(!directed)
                {
                    seen.insert(make_pair(destination, source));
                }
            }
        }
    }

    return ret;
}

bool Graph::vertexExists(Vertex v) const
{
    return assertVertexExists(v, "");
}

bool Graph::edgeExists(Vertex source, Vertex destination) const
{
    return assertEdgeExists(source, destination, "", "");
}

Edge Graph::setEdgeLabel(Vertex source, Vertex destination, string flight_data, string label)
{
    if (assertEdgeExists(source, destination, flight_data, __func__) == false)
        return InvalidEdge;
    
    vector<Edge> e_list = adjacency_list[source][destination];
    Edge e = InvalidEdge;
    int idx = 0;
    for (; idx < e_list.size(); idx++) {
        if (e_list[idx].getWeight().flight_data == flight_data) {
            e = e_list[idx];
            break;
        }
    }

    Edge new_edge(source, destination, e.getWeight(), label);
    adjacency_list[source][destination].at(idx) = new_edge;

    if(!directed)
    {
        Edge new_edge_reverse(destination,source, e.getWeight(), label);
        vector<Edge> reverse_list = adjacency_list[destination][source];
        
        for (int i = 0; i < reverse_list.size(); i++) {
            if (reverse_list[i].getWeight().flight_data == flight_data) {
                adjacency_list[destination][source].at(i) = new_edge_reverse;
                break;
            }
        }
        
    }
    return new_edge;
}


string Graph::getEdgeLabel(Vertex source, Vertex destination, string flight_data) const
{
    if(assertEdgeExists(source, destination, flight_data, __func__) == false)
        return InvalidLabel;
    vector<Edge> edge_list = adjacency_list[source][destination];
    for (const Edge& edges : edge_list) {
        if (edges.getWeight().flight_data == flight_data) {
            return edges.getLabel();
        }
    }
    return "";
}

Edge_Weight Graph::getEdgeWeight(Vertex source, Vertex destination, string flight_data) const
{
    if (!weighted)
        error("can't get edge weights on non-weighted graphs!");

    if(assertEdgeExists(source, destination, flight_data, __func__) == false)
        return InvalidWeight;
    
    vector<Edge>& edge_list = adjacency_list[source][destination];
    for (const Edge& edges : edge_list) {
        if (edges.getWeight().flight_data == flight_data) {
            return edges.getWeight();
        }
    }

    return InvalidWeight;
}

void Graph::insertVertex(Vertex v)
{
    // will overwrite if old stuff was there
    removeVertex(v);
    // make it empty again
    adjacency_list[v] = unordered_map<Vertex, vector<Edge>>();
    edge_count_list[v] = unordered_map<Vertex, int>();
}


Vertex Graph::removeVertex(Vertex v)
{
    // TODO: Needs to be reviewed. 
    if (adjacency_list.find(v) != adjacency_list.end())
    {
        if(!directed){
            for (auto it = adjacency_list[v].begin(); it != adjacency_list[v].end(); it++)
            {
                Vertex u = it->first;
                adjacency_list[u].erase(v);
                edge_count_list[u].erase(v);
            }
            adjacency_list.erase(v);
            edge_count_list.erase(v);
            return v;
        }
        
        adjacency_list.erase(v);
        edge_count_list.erase(v);
        
        for(auto it2 = adjacency_list.begin(); it2 != adjacency_list.end(); it2++)
        {
            Vertex u = it2->first;
            if (it2->second.find(v)!=it2->second.end())
            {
                it2->second.erase(v);
            }

            if (edge_count_list[u].find(v) != edge_count_list[u].end()) {
                edge_count_list[u].erase(v);
            }
        }
        return v;
    }

    return InvalidVertex;
}

bool Graph::insertEdge(Vertex source, Vertex destination, string flight_data, Edge_Weight weight)
{
    if(adjacency_list.find(source)!= adjacency_list.end() 
    && adjacency_list[source].find(destination)!= adjacency_list[source].end())
    {
        vector<Edge> edge_list = adjacency_list[source][destination];
        bool is_found = false;
        for (const Edge& edges : edge_list) {
            if (edges.getWeight().flight_data == flight_data) {
                is_found = true;
                break;
            }
        }
        if (is_found) {
            return false;
        }
    }

    if(adjacency_list.find(source)==adjacency_list.end())
    {
        adjacency_list[source] = unordered_map<Vertex, vector<Edge>>();
    }

    if (edge_count_list.find(destination) == edge_count_list.end()) {
        edge_count_list[destination] = unordered_map<Vertex, int>();
    }
        //source vertex exists
    adjacency_list[source][destination].push_back(Edge(source, destination, weight, ""));
    edge_count_list[destination][source] = 1;

    if (edge_count_list.find(source) != edge_count_list.end()) {
        for (auto it = edge_count_list[source].begin(); it != edge_count_list[source].end(); ++it) {
            if (it->first == destination) {
                continue;
            } else if (edge_count_list[destination].find(it->first) != edge_count_list[destination].end()) {
                int current_val = edge_count_list[destination][it->first];
                edge_count_list[destination][it->first] = current_val > it->second + 1 ? it->second + 1 : current_val;
            } else {
                edge_count_list[destination][it->first] = it->second + 1;
            }
            
        }
    }
    

    if(!directed)
    {
        if(adjacency_list.find(destination) == adjacency_list.end())
        {
            adjacency_list[destination] = unordered_map<Vertex, vector<Edge>>();
        }

        if (edge_count_list.find(source) == edge_count_list.end()) {
            edge_count_list[source] = unordered_map<Vertex, int>();
        }
        adjacency_list[destination][source].push_back(Edge(source, destination, weight, ""));
        edge_count_list[source][destination] = 1;
         
        if (edge_count_list.find(destination) != edge_count_list.end()) {
            for (auto it = edge_count_list[destination].begin(); it != edge_count_list[destination].end(); ++it) {
                if (it->first == source) {
                    continue;
                } else if (edge_count_list[source].find(it->first) != edge_count_list[source].end()) {
                    int current_val = edge_count_list[source][it->first];
                    edge_count_list[source][it->first] = current_val > it->second + 1 ? it->second + 1 : current_val;
                } else {
                    edge_count_list[source][it->first] = it->second + 1;
                }
            }
        }
    }
    
    return true;
}

Edge Graph::removeEdge(Vertex source, Vertex destination, string flight_data)
{
    if(assertEdgeExists(source, destination, flight_data, __func__) == false)
        return InvalidEdge;
    vector<Edge>& e_list = adjacency_list[source][destination];
    Edge e = InvalidEdge;
    for (auto it = e_list.begin(); it != e_list.end(); ++it) {
        if (it->getWeight().flight_data == flight_data) {
            e = *it;
            e_list.erase(it);
            break;
        }
    }
    if (e_list.size() == 0) {
        edge_count_list[source].erase(destination);
    }
    
    // if undirected, remove the corresponding edge
    if(!directed)
    {
        vector<Edge>& reverse_list = adjacency_list[destination].at(source);
        for (auto it = reverse_list.begin(); it != reverse_list.end(); ++it) {
            if (it->getWeight().flight_data == flight_data) {
                reverse_list.erase(it);
                break;
            }
        }
        if (reverse_list.size()) {
            edge_count_list[destination].erase(source);
        }
    }
    return e;
}


Edge Graph::setEdgeWeight(Vertex source, Vertex destination, string flight_data, Edge_Weight weight)
{
    if (assertEdgeExists(source, destination, flight_data, __func__) == false)
        return InvalidEdge;
    vector<Edge>& e_list = adjacency_list[source][destination];
    Edge e = InvalidEdge;
    int idx;
    for (idx = 0; idx < e_list.size(); idx++) {
        if (e_list[idx].getWeight().flight_data == flight_data) {
            e = e_list[idx];
            break;
        }
    }
    //std::cout << "setting weight: " << weight << std::endl;
    Edge new_edge(source, destination, weight, e.getLabel());
    adjacency_list[source][destination].at(idx) = new_edge;

    if(!directed)
    {
        Edge new_edge_reverse(destination,source, weight, e.getLabel());
        vector<Edge>& rev_list = adjacency_list[destination][source];

        for (int rev_idx = 0; rev_idx < rev_list.size(); rev_idx++) {
            if (rev_list[rev_idx].getWeight().flight_data == flight_data) {
                adjacency_list[destination][source].at(rev_idx) = new_edge_reverse;
                break;
            }
        }
        
    }

    return new_edge;
}

bool Graph::assertVertexExists(Vertex v, string functionName) const
{
    if (adjacency_list.find(v) == adjacency_list.end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent vertices");
        return false;
    }
    return true;
}

bool Graph::assertEdgeExists(Vertex source, Vertex destination, string flight_data, string functionName) const
{
    if(assertVertexExists(source,functionName) == false)
        return false;
    if(adjacency_list[source].find(destination) == adjacency_list[source].end())
    {
        if (functionName != "")
            error(functionName + " called on nonexistent edge " + source + " -> " + destination);
        return false;
    }

    vector<Edge>& edge_list = adjacency_list[source][destination];
    bool is_found = false;

    for (auto it = edge_list.begin(); it != edge_list.end(); ++it) {
        if (it->getWeight().flight_data == flight_data) {
            is_found = true;
            break;
        }
    }

    if (!is_found) {
        return false;
    }

    if(!directed)
    {
        if (assertVertexExists(destination,functionName) == false)
            return false;
        if(adjacency_list[destination].find(source)== adjacency_list[destination].end())
        {
            if (functionName != "")
                error(functionName + " called on nonexistent edge " + destination + " -> " + source);
            return false;
        }

        vector<Edge>& edge_list_rev = adjacency_list[destination][source];
        bool is_found_rev = false;

        for (auto it = edge_list_rev.begin(); it != edge_list_rev.end(); ++it) {
            if (it->getWeight().flight_data == flight_data) {
                is_found_rev = true;
                break;
            }
        }

        if (!is_found_rev) {
            return false;
        }
    }
    return true;
}

bool Graph::isDirected() const
{
    return directed;
}

void Graph::clear()
{
    adjacency_list.clear();
}

int Graph::get_edge_count(Vertex source, Vertex dest) const {
    if (edge_count_list.find(source) != edge_count_list.end()) {
        if (edge_count_list[source].find(dest) != edge_count_list[source].end()) {
            return edge_count_list[source][dest];
        }
    }
    return INT_MAX;
}

/**
 * Prints a graph error and quits the program.
 * The program is exited with a segfault to provide a stack trace.
 * @param message - the error message that is printed
 */
void Graph::error(string message) const
{
    cerr << "\033[1;31m[Graph Error]\033[0m " + message << endl;
}

/**
 * Creates a name for snapshots of the graph.
 * @param title - the name to save the snapshots as
 */
void Graph::initSnapshot(string title)
{
    picNum = 0;
    picName = title;
}

/**
 * Saves a snapshot of the graph to file.
 * initSnapshot() must be run first.
 */
void Graph::snapshot()
{
    std::stringstream ss;
    ss << picNum;
    string newName = picName + ss.str();
    savePNG(newName);
    ++picNum;
}

/**
 * Prints the graph to stdout.
 */
void Graph::print() const
{
    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        cout << it->first << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            std::stringstream ss;
            ss << it2->first; 
            string vertexColumn = "    => " + ss.str();
            vertexColumn += " " ;
            cout << std::left << std::setw(26) << vertexColumn;
            for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3) {
                string edgeColumn = "edge label = \"" + it3->getLabel()+ "\"";
                cout << std::left << std::setw(26) << edgeColumn;
                if (weighted)
                    cout << "weight = " << it3->getWeight();
            }
            cout << endl;
        }
        cout << endl;
    }
}

/**
 * Saves the graph as a PNG image.
 * @param title - the filename of the PNG image
 */
void Graph::savePNG(string title) const
{
    std::ofstream neatoFile;
    string filename = "images/" + title + ".dot";
    neatoFile.open(filename.c_str());

    if (!neatoFile.good())
        error("couldn't create " + filename + ".dot");

    neatoFile
        << "strict graph G {\n"
        << "\toverlap=\"false\";\n"
        << "\tdpi=\"1300\";\n"
        << "\tsep=\"1.5\";\n"
        << "\tnode [fixedsize=\"true\", shape=\"circle\", fontsize=\"7.0\"];\n"
        << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";

    vector<Vertex> allv = getVertices();
    //lambda expression
    sort(allv.begin(), allv.end(), [](const Vertex& lhs, const Vertex& rhs) {
        return stoi(lhs.substr(3)) > stoi(rhs.substr(3));
    });

    int xpos1 = 100;
    int xpos2 = 100;
    int xpos, ypos;
    for (auto it : allv) {
        string current = it;
        neatoFile 
            << "\t\"" 
            << current
            << "\"";
        if (current[1] == '1') {
            ypos = 100;
            xpos = xpos1;
            xpos1 += 100;
        }
        else {
            ypos = 200;
            xpos = xpos2;
            xpos2 += 100;
        }
        neatoFile << "[pos=\""<< xpos << "," << ypos <<"\"]";
        neatoFile << ";\n";
    }

    neatoFile << "\tedge [penwidth=\"1.5\", fontsize=\"7.0\"];\n";

    for (auto it = adjacency_list.begin(); it != adjacency_list.end(); ++it) 
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2) 
        {
            string vertex1Text = it->first;
            string vertex2Text = it2->first;

            neatoFile << "\t\"" ;
            neatoFile << vertex1Text;
            neatoFile << "\" -- \"" ;
            neatoFile << vertex2Text;
            neatoFile << "\"";

            for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it) {
                string edgeLabel = it3->getLabel();
                if (edgeLabel == "WIN") {
                    neatoFile << "[color=\"blue\"]";
                } else if (edgeLabel == "LOSE") {
                    neatoFile << "[color=\"red\"]";                
                } else {
                    neatoFile << "[color=\"grey\"]";
                }

                if (weighted && it3->getWeight() != Edge_Weight())
                    neatoFile << "[label=\"" << it3->getWeight() << "\"]";
                neatoFile<< "[constraint = \"false\"]" << ";\n";
            }
        }
    }

    neatoFile << "}";
    neatoFile.close();
    string command = "neato -n -Tpng " + filename + " -o " + "images/" + title
                     + ".png 2> /dev/null";
    int result = system(command.c_str());


    if (result == 0) {
        cout << "Output graph saved as images/" << title << ".png" << endl;
    } else {
        cout << "Failed to generate visual output graph using `neato`. Install `graphviz` or `neato` to generate a visual graph." << endl;
    }

    string rmCommand = "rm -f " + filename + " 2> /dev/null";
    system(rmCommand.c_str());
}
