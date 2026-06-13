#include<iostream>
#include<vector>
using namespace std;

class Graph{
    int n; //no of vertices
    vector<vector<int>> w; //adjacency matrix
    vector<vector<bool>> blocked;//true->blocked, false-> not blocked
    bool directed;//true->directed, false->undirected
    vector<int> q, key, p;
public:
    Graph(int n, bool dir): n(n), directed(dir){
        w = vector<vector<int>> (n, vector<int>(n, 0));
        blocked = vector<vector<bool>> (n, vector<bool> (n, false));
        q = vector<int> (n);
        key = vector<int> (n);
        p = vector<int> (n);
    }
    void addEdge(int u, int v, int x, bool blocked_status= false){
        w[u][v] = x;
        blocked[u][v] = blocked_status;
        if(!directed) {
            w[v][u] = x;
            blocked[v][u] = blocked_status;
        }
    }
    bool isEdge(int u, int v){
        if(w[u][v] != 0) return true;
        else return false;
    }
    int ExtractMin(){
        int m = INT_MAX;
        int idx = -1;
        for(int i = 0; i < n; i++){
            if(q[i] == 1 && key[i] < m){
                m = key[i];
                idx = i;
            }
        }
        return idx;
    }
    void MST_Prim(int r){
        for(int i = 0; i < n; i++){
            q[i] = 1;
            key[i] = INT_MAX;
            p[i] = -1;
        }
        key[r] = 0;
        for(int i = 1; i <= n; i++){
            int u = ExtractMin();
            if(u == -1){
                cout << "Graph is disconnected" << endl;
                break;
            }
            q[u] = 0;
            for(int v = 0; v < n; v++){
                if(isEdge(u, v) && blocked[u][v] == false){
                    //v is adjacent to u
                    if(q[v] == 1 && key[v] > w[u][v]){
                        key[v] = w[u][v];
                        p[v] = u;
                    }
                }
            }
        }

        int cost = 0;
        cout << "Chosen edges for MST:" << endl;
        for(int i = 0; i < n; i++){
            if(p[i] != -1){
                cout<<"("<<i<<", "<<p[i]<<", "<<key[i]<<")"<<endl;
                cost += key[i];
            }
        }
        cout << "cost of MST: " << cost << endl;
    }
};
int main(){
    Graph g(4, false);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 4, true);
    g.addEdge(0, 3, 9);
    g.addEdge(1, 2, 6, true);
    g.addEdge(1, 3, 8);
    g.addEdge(2, 3, 7);
    g.MST_Prim(0);
}

