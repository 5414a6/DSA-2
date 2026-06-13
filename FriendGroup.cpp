#include<iostream>
#include<vector>
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

class FriendGroups{
    int N;
    DisjointSets ds;
public:
    FriendGroups(int N): N(N), ds(N){
        for(int i = 0; i < N; i++)
            ds.makeSet(i);
    }
    void Friend(int x, int y){
        if(x%2 == y%2){
            ds.Union(x, y);
        }
    }
    void Check(int x, int y){
        if(ds.Find(x) == ds.Find(y))
            cout << "in the same group" << endl;
        else cout << "in the different group" << endl;
    }
};

int main(){
    FriendGroups g(8);
    g.Friend(2, 6);
    g.Friend(3, 7);
    g.Friend(2, 5);
    g.Friend(4, 6);
    g.Check(2, 7);

}

