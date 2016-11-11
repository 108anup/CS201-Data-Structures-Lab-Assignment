/**
*
*   Assignment 7 - DisjointSets Q2. Linked List
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
    node* next;
    node* rep;
    node* head;
    node* tail;
    int s; //size
};

//Disjoint set DS
//For n make set operations and m make set, union and find operations
//Time Complexity is O(m + nlog(n)) with the union by rank heuristic
//Although the time complexity for each union operation is O(min(n1,n2)) but the make_set operation
//can only be called O(log(n)) times for a given element
//Therefore total time for all possible union operations would be O(n*log(n))
//Without the heuristic this would be O(n^2) time. giving overall time O(min(mn, m+n^2))
//Also make set and find set take constant time 
//so O(m) time for them
//therefore overall time O(m + nlog(n)). 
class Set{

    int n;

    public:

    //Mapping from Set Data Element to Pointer to node containing the element.
    vector<node*> dict;

    Set(int n){
        this->n = n;
        dict.resize(SIZE);
        //dict.assign(SIZE, NULL);
    }

    //Overloaded function which takes data values as input for Union
    //O(min(n1,n2)) for single iteration where n1 and n2 are the sizes of the input sets
    void union_set(int x, int y){
        if(!dict[x]||!dict[y]){
            cout<<"\nERROR:: Element not Found!\n";
        }
        else
            union_set(dict[x],dict[y]);
    }

    //over loaded function that takes data values as input for finding the representative element.
    //O(1)
    node* find_set(int x){
        if(dict[x])
            return find_set(dict[x]);
        else{
            cout<<"\nERROR:: Element not Found!\n";
            return NULL;
        }
    }

    //O(1) as there is only one statement whose time is independent of input size.
    node* find_set(node* p){
        //We cache the representative element for each element of the set.
        return p->rep;
    }

    //Since we change the rep value for each element in set with lesser number of elements
    //Therefore each single iteration takes O(min(n1,n2)) time.
    void union_set(node* x, node* y){
        node* l = find_set(y); //lesser size
        node* g = find_set(x); //greater size

        if(!l || !g){
            cout<<"\nERROR:: Element not Found!\n";
        }

        if(g!=l){

            //find the set with more elements
            if(g->s<l->s){
                node* temp = g;
                g = l;
                l = temp;
            }

            //Make tail of the set with more elements as the tail of the set with more
            //Also attach the lesser set at the end of the more element set
            g->tail->next = l;
            g->tail = l->tail;

            //Update the rep element of the set with lesser number of elements.
            node* temp = l;
            while( temp!=l->tail ){
                temp->rep = g;
                temp=temp->next;
            }
            temp->rep = g;
            g->s = l->s+g->s;

            l->s=0;
            l->head = NULL;
            l->tail = NULL;
        }
    }

    //Constant Time making of set.
    void make_set(int x){
        node* p = new node;
        p->data = x;
        p->next = p->rep = p->head = p->tail = p;
        p->s = 1;
        dict[x] = p;
    }

    void show(){
        for(int i= 0; i<SIZE-1; i++){

            if(dict[i]){
                node* r = dict[i];

                if(r->rep == r){
                    node* t = r;
                    while(t!=r->tail){
                        cout<<t->data<<", ";
                        t=t->next;
                    }
                    cout<<t->data<<"\n";
                }
            }
        }
    }
};


int main()
{
    int n;
    cout<<"Enter the Number of Elements:\t";
    cin>>n;
    Set S(n);

    cout<<"\nEnter the Elements (Max Range: 0 to 10^4)\t";
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
        node* ret;
        switch(ch){
            case 1:
                cout<<"\n----\n\nYou have chosen Find Set:";
                cout<<"\nEnter the value of the Element whose Set Representative you want:\t";
                cin>>x;
                ret = S.find_set(x);
                if(ret)
                    cout<<"\nSet Representative is:\t"<<ret->data<<endl;
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
