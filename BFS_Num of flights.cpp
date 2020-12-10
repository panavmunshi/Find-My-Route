using namespace std;
 
bool BFS_trav(vector<int> next_array[], int init, int fin, int v, int prev[], int leng[])
{

    list<int> q;
 
    bool visited[v];
 
    for (int a = 0; a < v; a++){
        visited[a] = false;
        prev[a] = -1;
        leng[a] = 9999;
    }
 
    visited[init] = true;
    leng[init] = 0;
    q.push_back(init);
 

    while (q.empty() == false){
        int a = q.front();
        q.pop_front();
        int b = 0;
        while(b <= next_array[a].size() - 1){
            if (visited[next_array[a][b]] == false){
                visited[next_array[a][b]] = true;
                prev[next_array[a][b]] = a;

                leng[next_array[a][b]] = 1 + leng[a];
                q.push_back(next_array[a][b]);
                if (next_array[a][b] == fin){return true;}    
            }
            
            b++;
        }
    }
    return false;
}
 
void leastedges(vector<int> next_array[], int s, int fin, int v){
    
    
    int leng[v];
    int prev[v]; 
 
    if (BFS_trav(next_array, s, fin, v, prev, leng) == false) {
        cout << "Given initial node and final node are unconnected";
        return;
    }
 

    vector<int> route;
    int last_pt = fin;
    route.push_back(last_pt);

    while (prev[last_pt] != -1) {
        route.push_back(prev[last_pt]);
        last_pt = prev[last_pt];
    }
 

    cout << "Least Number of flights required : " << leng[fin];
 
    
    cout << "\nFlight Route is::\n"; 
    int a = route.size() - 1;

    while(a >= 0){
        cout << route[a] << " ";
        a--;
    }
}