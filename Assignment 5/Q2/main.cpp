#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Graph{

    int n;
    int e;
    vector<vector<int> > g;
    vector<vector<int> > components;
    vector<char> colour;

    Graph(){
        g.resize(n+1);
        colour.resize(n+1);
    }

    void addEdge(int u, int v){
        g[u].push_back(v);
    }

    void dfs_visit(int s, vector<int> comp){
        colour[s] = 'G';
        comp.push_back(s);

        for(int i= 0; i<g[s].size(); i++){
            if(colour[g[s][i]]=='W'){
                dfs_visit(i, comp);
            }
        }
        colour[i] = 'B';
    }

    void dfs(){
        colour.assign('W');
        for(int i= 1; i<=n; i++){
            if(colour[i]=='W'){
                vector<int> comp;
                dfs_visit(i,comp);
                components.push_back(comp);
            }
        }
    }

    void output(){
        int mat[n+1][n+1];
        memset(mat, 0, sizeof(mat));

        for(int i= 0; i<components.size(); i++){
            for(int j = 0; j<components[i].size(); j++){
                for(int k = j; k<components[i].size(); k++){
                    mat[components[i][j]][components[i][k]] = 1;
                    mat[components[i][k]][components[i][j]] = 1;
                }
            }
        }

        for(int i= 1; i<n+1; i++){
            for(int j= 0; j<n+1; j++){
                cout<<mat[i][j]<<" ";
            }
            cout<<"\n";
        }
    }
};

int main()
{
    int n, e;

    cin>>n>>e;

    Graph gg(n);

    for(int i= 0; i<e; i++){
        int u,v;
        cin>>u>>v;

        gg.addEdge(u,v);
    }
    return 0;
}
