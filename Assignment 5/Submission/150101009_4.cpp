/**
*
*   Assignment 5 - Graphs DFS_BFS Q4.
*   CS 210 - Data Structures
*
*   Written By:
*
*   Anup Agarwal (150101009)
*   anup.agarwal@iitg.ernet.in
*   +91 9711794321
*
*   Department of Computer Science and Engineering
*
*   A - 222 Barak Hostel,
*   Guwahati, Assam - 781039
*
*   All O (Big-Oh) signify time complexity unless mentioned otherwise
*
**/
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

        //Store the Vertices in a Stack in the Order of their Finishing Times
        //So the One with the highest Finishing Time becomes the top
        for(int i= 0; i<n; i++){
            if(colour[i]=='W'){
                fillStack(i,st);
            }
        }

        Graph gt = getTranspose();
        gt.colour.assign(n,'W');

        cout<<"\nThe SCCs are:\n";
        //Traverse the Transpose Graph in the Descending order of finishing times for the original Graph's DFS.
        while(!st.empty()){
            int v = st.top();
            st.pop();

            if(gt.colour[v]=='W'){
                //Vertices belonging to the same SCC are printed in the following line.
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
    //freopen("in.txt","r",stdin);
    cout<<"Enter the Number of Vertices:\t";
    int n;
    cin>>n;

    Graph gg(n);
    int u,v;
    
    cout<<"\nEnter the Edges (NOTE: Vertex indexing starts with 0 i.e. ZERO,\nPress Ctrl+D then Enter to End Input of Edges:\n";
    while(cin>>u>>v){
        gg.addEdge(u,v);
    }

    gg.SCC();
    return 0;
}