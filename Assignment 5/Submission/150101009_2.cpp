/**
*
*   Assignment 5 - Graphs DFS_BFS Q2.
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
        //s is the source vertex and v is its descendent
        tm[s][v] = true;
        for(int i= 0; i<g[v].size(); i++){
            //If the Entry is already there in the Matrix then we don't need to visit it again.
            if(tm[s][g[v][i]]==false){
                dfs_visit(s,g[v][i]);
            }
        }
    }

    //For Each Vertex we are running DFS irrespective of whether it has been Visited or Not.
    //DFS for one vertex can take upto Theta(V+E) time so for DFS on All Vertex Time will be O(V(V+E))
    //We are setting the source vertex in this block and then recursively call dfs_visit for each of its descendent.
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
    //The Matrix Described int he Question is also known as the Transitive Closure. Link for Reference:
    //(https://books.google.co.in/books?id=TrXd-gxPhVYC&lpg=PP1&dq=algorithm%20design%20manual&pg=PA284&redir_esc=y&hl=en#v=onepage&q&f=false)
    cout<<"\nThe Transitive closure of the Graph is:\n";
    gg.dfs();
    gg.show();
    return 0;
}
