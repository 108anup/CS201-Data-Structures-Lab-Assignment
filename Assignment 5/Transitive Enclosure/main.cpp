#include <iostream>
#include <string.h>
#include <vector>

#define SIZE 1005

using namespace std;

class Graph{

    int n;
    int e;
    vector<vector<int> > g;
    bool tm[SIZE][SIZE];

public:

    Graph(int n){
        this->n = n;
        g.resize(n+1);
    }

    void addEdge(int u, int v){
        g[u].push_back(v);
    }

    void dfs_visit(int s, int v){
        tm[s][v] = true;
        for(int i= 0; i<g[v].size(); i++){
            if(tm[s][g[v][i]]==false){
                dfs_visit(s,g[v][i]);
            }
        }
    }

    void dfs(){
        for(int i= 1; i<=n; i++){
            dfs_visit(i,i);
        }
    }


    void show(){
        for(int i= 1; i<=n; i++){
            for(int j = 1; j<=n; j++){
                cout<<tm[i][j]<<" ";
            }
            cout<<"\n";
        }
    }
};

int main()
{
    int n, e;
    cout<<"Enter the Number of Vertices and Edges Separated by a space:\t";
    cin>>n>>e;

    Graph gg(n);
    cout<<"\nEnter the Edges (NOTE: Vertex indexing starts with 1):\n";
    for(int i= 0; i<e; i++){
        int u,v;
        cin>>u>>v;
        gg.addEdge(u,v);
    }
    cout<<"\nThe Transitive Enclosure of the Graph is:\n";
    gg.dfs();
    gg.show();
    return 0;
}
