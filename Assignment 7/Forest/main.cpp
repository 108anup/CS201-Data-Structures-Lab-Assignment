#include <iostream>
#include <vector>

using namespace std;

const int SIZE = 1e5;

struct node{
    int data;
    node* rep; //parent
    int s; //rank
};

class Set{

    int n;

    public:

    vector<node*> dict;

    Set(int n){
        this->n = n;
        dict.resize(SIZE);
        dict.assign(SIZE,NULL);
    }

    void union_set(int x, int y){
        if(!dict[x] || !dict[y])
            cout<<"\nInvalid Parameters";
        else
            union_set(dict[x],dict[y]);
    }

    node* find_set(int x){
        if(!dict[x]){
            cout<<"\nInvalid Parameters";
            return NULL;
        }
        return find_set(dict[x]);
    }

    node* find_set(node* p){
        if(p->rep == p){
            return p;
        }
        else return p->rep = find_set(p->rep);
    }

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
