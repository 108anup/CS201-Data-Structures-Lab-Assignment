/**
*
*   Assignment 7 - DisjointSets Q3. Forest
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

using namespace std;

const int SIZE = 1e5;

struct node{
    int data;
    node* rep; //parent
    int s; //rank
};

//Disjoint set Data Structure
//For n make set operations and m make set, union and find operations
//The Overall Complexity is O(m*alpha(n)) where alpha is the Inverse Ackerman Function (extermely slow growing).
//Which is roughly O(m) as alpha(n) <=4 for all practical purposes.
//The Explaination for the overall Complexity with both Union by Rank and Path Compression heuristic is out of scope of discussion.
//If we only follow Union by Rank Heuristic Time Complexity would be O(m*log(n)) as find set each operation would atmost O(log(n)) time. 
class Set{

    int n;

    public:

    //Dictionary that maps Data Elements to the node pointer. 
    vector<node*> dict;

    Set(int n){
        this->n = n;
        dict.resize(SIZE);
    }

    //Overloaded function for Union that takes data elts as imput
    //O(log(n)) per single iteration worst case.
    void union_set(int x, int y){
        if(!dict[x] || !dict[y])
            cout<<"\nInvalid Parameters";
        else
            union_set(dict[x],dict[y]);
    }

    //Overloaded function for Find set that takes data elts as imput
    //O(log(n)) Per single iteration worst case.
    node* find_set(int x){
        if(!dict[x]){
            cout<<"\nInvalid Parameters";
            return NULL;
        }
        return find_set(dict[x]);
    }

    //NOTE::
    //The Rank for any Node could be atmost log(n).
    //Since at any instant except for the last level for each tree in the forest, the levels have atleast 2^i elements where i is the level number
    //And so for rank = k there would be alteast 2^(k-1)-1 elements in that set (where rank = 1 for Singleton set) 
    //So if n are the total elements the universal set would have log(n+1)+1 elements = O(log(n))

    //Since each set can have rank atmost O(log(n)) there fore each single iteration takes atmost O(log(n)) time.
    node* find_set(node* p){
        //Go the parent and update rep
        if(p->rep == p){
            return p;
        }
        else return p->rep = find_set(p->rep);
    }

    //Since Apart from the Find Set operations the other operations take constant time so O(log(n)) per iteration.
    void union_set(node* x, node* y){
        node* l = find_set(y); //lesser rank
        node* g = find_set(x); //greater rank

        if(g!=l){
            if(g->s<l->s){
                node* temp = g;
                g = l;
                l = temp;
                l->rep = g;
            }
            else if(l->s==g->s){
                l->rep = g;
                g->s += 1;
            }
            else{
                l->rep = g;
            }
        }
    }

    //Constant time for making a set.
    void make_set(int x){
        node* p = new node;
        p->data = x;
        p->rep = p;
        p->s = 1;
        dict[x] = p;
    }

    void show(){
        cout<<"\nNode, Representative\n";
        for(int i= 0; i<SIZE -1; i++){
            node* r = dict[i];
            if(r)
                cout<<r->data<<",\t"<<find_set(r)->data<<endl;
        }
    }
};


int main()
{
    int n;
    cout<<"Enter the Number of Elements:\t";
    cin>>n;
    Set S(n);

    cout<<"\nEnter the Value of the Elements (Max Range 0 to 10^4):\t";
    for(int i = 0; i<n; i++){
        int x;
        cin>>x;
        S.make_set(x);
    }

    int ch = 0;
    while(ch!=9){
        cout<<"\n\n----\nMENU";
        cout<<"\n1. Find Set";
        cout<<"\n2. Union";
        cout<<"\n9. End";
        cout<<"\nChoice:\t";
        cin>>ch;

        int x, y;
        node* r;
        switch(ch){
            case 1:
                cout<<"\n----\n\nYou have chosen Find Set:";
                cout<<"\nEnter the value of the Element whose Set Representative you want:\t";
                cin>>x;
                r= S.find_set(x);
                if(r){
                    cout<<"\nSet Representative is:\t"<<r->data<<endl;
                }
                break;
            case 2:
                cout<<"\n----\n\nYou have chosen Union:";
                cout<<"\nEnter the value of the Elements whose sets you want to unite\n(Separated by Spaces):\t";
                cin>>x>>y;
                S.union_set(x,y);
                cout<<"\nThe Resulting Disjoint Sets are:\n"<<endl;
                S.show();
                break;
            case 9:break;
            default: cout<<"\n\nPlease Enter Valid option."; break;
        }
    }
    return 0;
}
