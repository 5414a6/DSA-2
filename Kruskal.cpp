#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class DisjointSets{
    int n;
    vector<int> p, Rank;
public:
    DisjointSets(int n): n(n){
        p = vector<int> (n);
        Rank = vector<int> (n);
    }
    void makeSet(int x){
        p[x] = x;
        Rank[x] = 0;
    }
    int Find(int x){
        if( x != p[x])
            p[x] = Find(p[x]);
        else return x;
    }
    void Union(int a, int b){
        int x = Find(a);
        int y = Find(b);

        if(x == y){
            cout << "already in the same set" << endl;
            return;
        }
        if(Rank[x] > Rank[y]){
            p[y] = x;
        }else{
            p[x] = y;
            if(Rank[x] == Rank[y])
                Rank[y]++;
        }
    }

};

class Graph{
    int n;
    vector<vector<int>> edges;
public:
    Graph(int n): n(n){
    }
    void addEdge(int u, int v, int w){
        edges.push_back({w, u, v});
    }
    void Kruskal(){
        DisjointSets ds(n);
        vector<vector<int>> T;

        for(int v = 0; v < n; v++)
            ds.makeSet(v);

        //sort the edges in ascending order
        sort(edges.begin(), edges.end());

        for(auto e : edges){
            int w = e[0];
            int u = e[1];
            int v = e[2];

            if( ds.Find(u) != ds.Find(v)){
                T.push_back({u, v, w});
                ds.Union(u, v);
            }else{
                cout << "Cycle detected" << endl;
            }
        }

        int cost = 0;
        cout << "Selected edges for MST:" << endl;
        for(auto e: T){
            int u = e[0];
            int v = e[1];
            int w = e[2];
            cout <<"("<<u<<", "<<v<<", "<<w<<")"<<endl;
            cost += w;
        }
        cout << "Cost of MST:" << cost << endl;
    }
};

int main(){
    Graph g(5);
    g.addEdge(0, 2, 10);
    g.addEdge(2, 3, 6);
    g.addEdge(1, 2, 7);
    g.addEdge(1, 3, 5);
    g.addEdge(0, 1, 9);
    g.addEdge(3, 4, 3);
    g.addEdge(1, 4, 2);
    g.Kruskal();

}

