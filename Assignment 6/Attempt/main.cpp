#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <stdio.h>

using namespace std;

class Graph{

    vector<vector<int> > g;
    int n;
    int time;
    vector<int> d;
    vector<int> f;

    public:

    vector<char> colour;

    Graph(int n){
        this->n = n;
        g.resize(n);
        colour.resize(n,'W');
        d.resize(n,INT_MAX);
        f.resize(n,INT_MAX);
        time = 0;
    }

    void addEdge(int u, int v){
        g[u].push_back(v);
    }

    void make_stack(int v, stack<int> &ordering){
        colour[v] = 'G';
        for(int i= 0; i<g[v].size(); i++){
            if(colour[g[v][i]]=='W'){
                make_stack(g[v][i],ordering);
            }
        }
        colour[v] = 'B';
        ordering.push(v);
    }

    void dfs(){
        colour.resize(n,'W');
        d.resize(n,INT_MAX);
        f.resize(n,INT_MAX);
        for(int i= 0; i<g.size(); i++){
            if(colour[i]=='W'){
                dfs_visit(i);
            }
        }
    }

    void dfs_visit(int v){
        colour[v] = 'G';
        d[v] = ++time;
        cout<<v<<" ";

        for(int i=0; i<g[v].size(); i++){
            if(colour[g[v][i]]=='W'){
                dfs_visit(g[v][i]);
            }
        }

        colour[v] = 'B';
        f[v] = ++time;
    }

    void scc(){
        time = 0;

        stack<int> ordering;
        for(int i=0; i<g.size(); i++){
            colour[i] = 'W';
            d[i]=INT_MAX;
            f[i]=INT_MAX;
        }

        for(int i=0; i<g.size(); i++){
            if(colour[i]=='W'){
                make_stack(i,ordering);
            }
        }

        Graph gT = transpose();

        cout<<"\nThe Strongly Connected Components are:\n\n";
        int num =0;

        while(!ordering.empty()){
            int top = ordering.top();
            ordering.pop();
            if(gT.colour[top]=='W'){
                cout<<++num<<". ";
                gT.dfs_visit(top);
                cout<<"\n";
            }
        }
    }

    Graph transpose(){
        Graph gT(n);
        for(int i= 0; i<g.size(); i++){
            for(int j = 0; j<g[i].size(); j++){
                gT.addEdge(g[i][j],i);
            }
        }
        return gT;
    }

    void showedges(){
        for(int i= 0; i<g.size(); i++){
            for(int j= 0; j<g[i].size(); j++){
                cout<<i<<" "<<g[i][j]<<"\n";
            }
        }
    }

    void showdfs(){
        cout<<"\nShowing Vertices of DFS in order of Discover time:\n";
        dfs();

        cout<<"\nThe Discover and Finish Times are:\n";
        for(int i= 0; i<n; i++){
            cout<<"d["<<i<<"] = "<<d[i]<<", f["<<i<<"] = "<<f[i]<<"\n";
        }
    }

};

int main()
{
    int v,e;
    freopen("in.txt","r",stdin);

    cout<<"Enter the Number of Vertices and Edges Separated by a Space:\t";
    cin>>v>>e;

    Graph g(v);

    cout<<"\nEnter the Edges:\n";
    for(int i= 0; i<e; i++){
        int x,y;
        cin>>x>>y;
        g.addEdge(x,y);
    }

    cout<<"\nThe Edges of the Transpose Graph are:\n";
    g.transpose().showedges();
    g.showdfs();
    g.scc();
    return 0;
}
