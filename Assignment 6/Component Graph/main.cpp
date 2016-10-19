/**
*
*   Assignment 6 - Graphs Q2. Component Graph
*   CS 210 - Data Structures (Fall Sem, 2016)
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
#include <vector>
#include <stack>
#include <climits>
#include <stdio.h>

using namespace std;

/**
--GIST of the Approach--
Finding the Component Graph of the Given Graph

First We find all the strongly connected components in O(V+E) time.
By Doing a DFS on the Transpose Graph in descending order of
finish times of vertices of the original graph.

We store the Components in a 2d vector such that each row contains all the vertices of that component
We traverse through it and we assign the component index to each vertex
O(V) time

Then We traverse through the edgelist of the original graph and for each edge that connects
2 vertices belonging to different components we add them to the component graph.

Finally we remove the duplicate edges added to the component graph in the above process. in O(E)time
*/

class Graph{

    vector<vector<int> > g;
    int n;
    int time;
    vector<int> d;
    vector<int> f;
    vector<vector<int> > components;    //stores the vertices of the same component in a vector
    vector<int> cc;                     //stores component index of a vertex

    public:

    vector<char> colour;

    Graph(int n){
        this->n = n;
        g.resize(n);
        colour.resize(n,'W');
        d.resize(n,INT_MAX);
        f.resize(n,INT_MAX);
        cc.resize(n);
        time = 0;
    }

    void addEdge(int u, int v){
        g[u].push_back(v);
    }

    //Method that adds the vertices into a stack in order of their finish times
    //such that the topmost element of the stack is last to finish
    //Takes O(V+E) time as all Edges and vertices are explored exactly once.
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

    //This is just the DFS VISIT Routine which explores all the vertices reachable from a given vertex
    //in O(V+E) time.
    void dfs_visit(int v, vector<int> &comp){
        colour[v] = 'G';
        d[v] = ++time;
        comp.push_back(v);

        for(int i=0; i<g[v].size(); i++){
            if(colour[g[v][i]]=='W'){
                dfs_visit(g[v][i],comp);
            }
        }

        colour[v] = 'B';
        f[v] = ++time;
    }

    //Main Routine that Finds the Component Graph of the Given Graph
    //Over all Complexity O(V+E)
    Graph Component_Graph(){
        time = 0;

        //First We find all the strongly connected components in O(V+E) time.
        //By Doing a DFS on the Transpose Graph in descending order of
        //finish times of vertices of the original graph.
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

        cout<<"\nThe Component Vertices/Strongly Connected Components are:\n";
        int num =0;

        while(!ordering.empty()){
            int top = ordering.top();
            ordering.pop();
            if(gT.colour[top]=='W'){
                vector<int> comp;
                gT.dfs_visit(top, comp);
                //We store the Components in a 2d vector such that each
                //row contains all the vertices of that component
                components.push_back(comp);
            }
        }

        //We traverse through the component 2d vector and we assign the component index to each vertex
        //O(V) time
        for(int i= 0; i<components.size(); i++){
            cout<<"Component Vertex "<<i<<":\t";
            for(int j= 0; j<components[i].size(); j++){
                cout<<components[i][j]<<" ";
                cc[components[i][j]] = i;
            }
            cout<<"\n";
        }

        Graph cg(components.size());
        //Then We traverse through the edgelist of the original graph and for each edge that connects
        //2 vertices belonging to different components we add them to the component graph.
        for(int i= 0; i<g.size(); i++){
            for(int j= 0; j<g[i].size(); j++){
                if(cc[i] != cc[ g[i][j] ]){
                    cg.addEdge(cc[i],cc[g[i][j]]);
                }
            }
        }
        //Finally we remove the duplicate edges added to the component graph in the above process. in O(E)time
        cg.removeDuplicateEdges();
        return cg;
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

    //Remove Duplicate Edges from any Graph
    //Takes O(E) time where E is the number of edges in the Graph
    //We Use it to remove duplicates in the Component Graph
    //Which is less than the number of edges in the Original Graph
    void removeDuplicateEdges(){
        vector<vector<int> > g_opt;
        g_opt.resize(n);

        vector<int> has_edge_from;
        has_edge_from.resize(n,-1);

        for(int i= 0; i<n; i++){
            for(int j= 0; j<g[i].size(); j++){
                //While Traversing the Edgelist of a vertex say u
                //we find u->v twice the first time we change has_edge_from[v]=u next time
                //when we see that it is already u so we dont add it
                //When we will traverse the adjacency list of the next vertex then we dont care
                //if has_edge_from[v] = u we only care whether the value is equal to the vertex whose
                //adjacency list is being traversed or not.
                if(has_edge_from[g[i][j]] != i){
                    g_opt[i].push_back(g[i][j]);
                    has_edge_from[g[i][j]] = i;
                }
            }
        }
        g=g_opt;
    }

};

int main()
{
    int v,e;
    //freopen("in.txt","r",stdin);

    cout<<"Enter the Number of Vertices and Edges Separated by a Space:\t";
    cin>>v>>e;

    Graph g(v);

    cout<<"\nEnter the Edges:\n";
    for(int i= 0; i<e; i++){
        int x,y;
        cin>>x>>y;
        g.addEdge(x,y);
    }

    Graph cg = g.Component_Graph();
    cout<<"\nThe Edges of the Component Graph are as follows:\n";
    cg.showedges();
    return 0;
}
