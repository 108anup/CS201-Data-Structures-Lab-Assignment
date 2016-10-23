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

class Set{

    int n;

    public:

    vector<node*> dict;

    Set(int n){
        this->n = n;
        dict.resize(SIZE);
        dict.assign(SIZE, NULL);
    }

    void union_set(int x, int y){
        if(!dict[x]||!dict[y]){
            cout<<"\nERROR:: Element not Found!\n";
        }
        else
            union_set(dict[x],dict[y]);
    }

    node* find_set(int x){
        if(dict[x])
            return find_set(dict[x]);
        else{
            cout<<"\nERROR:: Element not Found!\n";
            return NULL;
        }
    }

    node* find_set(node* p){
        return p->rep;
    }

    void union_set(node* x, node* y){
        node* l = find_set(y); //lesser size
        node* g = find_set(x); //greater size

        if(!l || !g){
            cout<<"\nERROR:: Element not Found!\n";
        }

        if(g!=l){

            if(g->s<l->s){
                node* temp = g;
                g = l;
                l = temp;
            }

            g->tail->next = l;
            g->tail = l->tail;


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
