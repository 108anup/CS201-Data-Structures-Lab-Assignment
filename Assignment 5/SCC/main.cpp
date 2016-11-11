#include <iostream>
#include <string.h>
#include <vector>
#include <stack>
#include <stdio.h>

using namespace std;

class Graph{

    int n;
    int e;
    vector<vector<int> > g;
    vector<char> colour;

    public:

    Graph(int n){
        this->n = n;
        g.resize(n);
        colour.resize(n);
    }

    void addEdge(int u, int v){
        g[u].push_back(v);
    }

    void fillStack(int s, stack<int> &st){
        colour[s] = 'G';
        for(int i= 0; i<g[s].size(); i++){
            if(colour[g[s][i]]=='W'){
                fillStack(g[s][i],st);
            }
        }
        st.push(s);
    }

    void dfs_visit(int s){
        colour[s] = 'G';
        cout<<s<<" ";

        for(int i= 0; i<g[s].size(); i++){
            if(colour[g[s][i]]=='W'){
                dfs_visit(g[s][i]);
            }
        }
        colour[s] = 'B';
    }

    void SCC(){
        stack<int> st;
        colour.assign(n,'W');

        for(int i= 0; i<n; i++){
            if(colour[i]=='W'){
                fillStack(i,st);
            }
        }

        Graph gt = getTranspose();
        gt.colour.assign(n,'W');

        while(!st.empty()){
            int v = st.top();
            st.pop();

            if(gt.colour[v]=='W'){
                gt.dfs_visit(v);
                cout<<"\n";
            }
        }
    }

    Graph getTranspose(){
        Graph gg(n);
        for(int i= 0; i<n; i++){
            for(int j = 0; j<g[i].size(); j++)
                gg.addEdge(g[i][j],i);
        }
        return gg;
    }
};

int main()
{
    freopen("in.txt","r",stdin);
    int n;
    cin>>n;

    Graph gg(n);
    int u,v;

    while(cin>>u>>v){
        gg.addEdge(u,v);
    }

    gg.SCC();
    return 0;
}

