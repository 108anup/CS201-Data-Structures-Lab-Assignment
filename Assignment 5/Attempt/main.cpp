#include <iostream>
#include <vector>
#include <utility>
#include <stdio.h>

using namespace std;

class Graph{

    vector<vector<int> > adj;
    int n;
    int e;
    vector<char> colour;
    vector<int> parent;

public:

    vector<vector<int> > component;
    vector<pair<int,int> > backedges;

    Graph(int n){
        this->n = n;
        adj.resize(n+1);
        colour.resize(n+1);
        parent.resize(n+1);
    }

    void addEdge(int u, int v){
        if(u!=v){
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        else{
            adj[v].push_back(u);
        }
    }

    void dfs_visit(int source, vector<int> &comp){
        colour[source] = 'G';
        comp.push_back(source);

        for(int i= 0; i<adj[source].size(); i++){
            if(colour[adj[source][i]]=='W'){
                parent[adj[source][i]] = source;
                dfs_visit(adj[source][i], comp);
            }
            else if(colour[adj[source][i]]=='G' && adj[source][i]!=parent[source]){
                backedges.push_back(make_pair(source,adj[source][i]));
            }
        }
        colour[source] = 'B';
    }

    void dfs(){
        for(int i= 0; i<n+1; i++){
            colour[i] = 'W';
            parent[i] = -1;
        }

        for(int i=1; i<n+1; i++){
            if(colour[i]=='W'){
                vector<int> comp;
                dfs_visit(i,comp);
                component.push_back(comp);
            }
        }
    }

    void listcomp(){
        cout<<"Number of Connected Components:\n"<<component.size()<<endl;
        for(int i= 0; i<component.size(); i++){
            cout<<"Connected Component "<<i+1<<": ";
            for(int j= 0; j<component[i].size(); j++){
                cout<<component[i][j]<<" ";
            }
            cout<<"\n";
        }
    }

    void listcycles(){
        cout<<"Number of Cycles:\n"<<backedges.size()<<endl;
        for(int i= 0; i<backedges.size(); i++){
            int last = backedges[i].first;
            int first = backedges[i].second;

            int p = last;
            cout<<"Cycle "<<i+1<<": "<<first<<" ";
            while(p!=first){
                cout<<p<<" ";
                p = parent[p];
            }
            cout<<first<<"\n";
        }
    }
};

int main()
{

    freopen("in.txt","r",stdin);
    int n;
    int e;

    cout<<"Enter the Number of Vertices and number of edges separated by a space:\n";
    cin>>n>>e;

    Graph g(n);

    cout<<"Enter the Edges:\n";
    for(int i = 0; i<e; i++){
        int x, y;
        cin>>x>>y;
        g.addEdge(x,y);
    }
    g.dfs();
    g.listcomp();
    g.listcycles();

    return 0;
}
