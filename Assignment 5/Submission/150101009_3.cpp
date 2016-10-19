/**
*
*   Assignment 5 - Graphs DFS_BFS Q3.
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
#include <vector>
#include <utility>
#include <stdio.h>

using namespace std;

class Graph{

    int n;
    int e;
    //Adjacency list
    vector<vector<int> > g;
    vector<char> colour;
    //To store the The Edges in Categories
    vector<pair<int,int> > tree_edges;
    vector<pair<int,int> > back_edges;
    vector<pair<int,int> > front_edges;
    vector<pair<int,int> > cross_edges;
    //Finish and Start Times
    vector<int> d;
    vector<int> f;
    int time;

    public:

    Graph(int n){
        this->n = n;
        g.resize(n+1);
        colour.resize(n+1);
        f.resize(n+1);
        d.resize(n+1);
    }

    void addEdge(int u, int v){
        g[u].push_back(v);
    }
    //Time Complexity is O(V+E) as in a single DFS Traversal we are able to categorize all the Edges.

    void dfs_visit(int s){
        colour[s] = 'G';
        d[s]=++time;

        for(int i= 0; i<g[s].size(); i++){
            if(colour[g[s][i]]=='W'){
                tree_edges.push_back(make_pair(s,g[s][i]));
                dfs_visit(g[s][i]);
            }
            //If the Edge being Discovered in the Current Vertex's Adjacency list is Gray that means it is a Back Edge
            else if(colour[g[s][i]]=='G'){
                back_edges.push_back(make_pair(s,g[s][i]));
            }
            //If the Edge being Dsicovered in the Current Vertex's Adjacency list is Black
            //that means it is a either a Forward Edge or a Cross Edge
            else if(colour[g[s][i]]=='B'){
                //If the Vertex was Finsihed after the Current Vertex Finished then it must be a Front Edge 
                //else it is a cross edge.
                if(f[g[s][i]]>d[s])
                    front_edges.push_back(make_pair(s,g[s][i]));
                else
                    cross_edges.push_back(make_pair(s,g[s][i]));
            }
        }
        colour[s] = 'B';
        f[s]=++time;
    }

    void dfs(){
        time = 0;
        colour.assign(n+1,'W');
        for(int i= 1; i<=n; i++){
            if(colour[i]=='W'){
                dfs_visit(i);
            }
        }
    }

    void show_vector_pair(vector<pair<int,int> > v){
        for(int i= 0; i<v.size(); i++){
            cout<<v[i].first<<" "<<v[i].second<<"\n";
        }
    }

    void showEdges_dfs_forest(){
        cout<<"\nTree Edges:\n";
        show_vector_pair(tree_edges);
        cout<<"\nBack Edges:\n";
        show_vector_pair(back_edges);
        cout<<"\nFront Edges:\n";
        show_vector_pair(front_edges);
        cout<<"\nCross Edges:\n";
        show_vector_pair(cross_edges);
    }
};

int main()
{
    //freopen("in.txt","r",stdin);
    cout<<"Enter the Number of Vertices and Edges Separated by a space:\t";
    int n, e;
    cin>>n>>e;

    Graph gg(n);
    cout<<"\nEnter the Edges (NOTE: Vertex indexing starts with 1):\n";
    for(int i= 0; i<e; i++){
        int u,v;
        cin>>u>>v;
        gg.addEdge(u,v);
    }
    cout<<"The Categorized Edges Stand as:\n";
    gg.dfs();
    gg.showEdges_dfs_forest();
    return 0;
}
