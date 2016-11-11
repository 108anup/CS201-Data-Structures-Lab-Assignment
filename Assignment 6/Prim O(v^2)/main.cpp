/**
*
*   Assignment 6 - Graphs Q2. Prim O(V^2)
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
#include <climits>
#include <stdio.h>

using namespace std;

class Graph{

    vector<vector<int> > g;
    vector<char> s;         //denotes set 'A' or 'B' = 'V-A'
    vector<int> p;          //denotes parent
    vector<int> d;          //denotes key
    int n;

public:

    Graph(int n){
        this->n = n;
        g.resize(n);
        d.resize(n);
        p.resize(n);

        for(int i = 0; i<n; i++){
            g[i].resize(n,0);
        }
    }

    void addEdge(int u, int v, int l){
        g[u][v] = g[v][u] = l;
    }

    //This Routine Updates the Distances of all the Vertices adjacent to the
    //supplied vertex. Here the distance represents the minimum distance of the vertex
    //in the set 'V-A' from a vertex of the set 'A' for the vertices of set 'V-A' while
    //for the vertices of the set 'A' the distance value is the smallest weight edge that connects
    //them to the MST.
    void updateDistances(int r){
        for(int i= 0; i<n; i++){
            if(g[r][i] && s[i] == 'B' && d[i] > g[r][i]){
                p[i] = r;
                d[i] = g[r][i];
            }
        }
    }

    //Find the Minimum of all the keys for vertices in the set 'V-A'
    //Using Linear Search => O(V) time.
    int getMinKey(){
        int minKey = INT_MAX;
        int minIdx = -1;

        for(int i= 0; i<n; i++){
            if(s[i] == 'B' && d[i]<=minKey){
                minKey = d[i];
                minIdx = i;
            }
        }
        return minIdx;
    }

    //Takes overall O(E+V^2) which is same as O(V^2) as |E| = OMEGA(V^2)
    void Prim(int root){
        d.assign(n,INT_MAX);
        p.assign(n,-1);
        s.assign(n,'B');

        d[root] = 0;
        p[root] = -1;
        s[root] = 'A';

        updateDistances(root); //O(V)

        for(int c=1; c<n; c++){ //run n-1 times so that all the n vertices have set 'A'
            int x = getMinKey(); //O(V) time per loop iteration total V choose 2 times
            //So Total Complexity of above step is O(V^2)
            s[x] = 'A';
            updateDistances(x); //O(E Time Total as each edge is visited atmost once in this routine)
        }
    }

    //Traverse through the Vertices and print the Edge that connects them to the MST
    void printParents(){
        for(int i = 1; i<n; i++){
            cout<<p[i]<<" - "<<i<<" => "<<g[p[i]][i]<<"\n";
        }
    }

};

int main()
{
    freopen("in.txt","r",stdin);
    int V,E;

    cout<<"Enter the Number of Vertices and Edges separated by a space:\t";
    cin>>V>>E;

    Graph gg(V);

    cout<<"\nEnter the Edges int the form of source destination weight (separated by spaces):\n";
    for(int i= 0; i<E; i++){
        int u, v, l;
        cin>>u>>v>>l;

        gg.addEdge(u,v,l);
    }

    gg.Prim(0);
    cout<<"\nThe MST formed is as follows:\n";
    cout<<"The Selected Edges are (in the form source - destination => weight) :\n";
    gg.printParents();

    return 0;
}

