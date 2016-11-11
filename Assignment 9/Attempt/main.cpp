#include <iostream>
#include <stdlib.h>

#define MAX 100

using namespace std;

struct node{
    node* left;
    node* right;
    node* child;
    node* parent;

    int key;
    int degree;
    bool mark;

    node(){
        left = right = child = parent = NULL;
        key = degree = 0;
        mark = false;
    }
};

node* createNode(){
    node* p = new node;
    return p;
}


class Fib{

    public:

    node* min;
    int n;

    Fib(node* p, int k){
        min = p;
        n = k;
    }

    Fib(){
        min = NULL;
        n =0;
    }

    void fillrand(int x){
        for(int i=0; i<x; i++){
            insert(rand()%MAX);
        }
    }

    void printList(node* r){
        if(r){
            node* p = r->right;
            cout<<"\nRoot: "<<r->key<<" , "<<r->degree<<" , "<<r->mark<<"\n";
            while(p!=r){
                cout<<p->key<<" , "<<p->degree<<" , "<<p->mark<<"\n";
                p=p->right;
            }
        }
        else{
            cout<<"\nEmpty List\n";
        }
    }

    void insert(int x){
        n++;
        min = insert(min,x);
    }

    void insert(node* p){
        n++;
        min = insert(min,p);
    }

    node* insert(node* l, int x){
        node* p = createNode();
        p->key = x;

        return insert(l, p);
    }

    node* insert(node* l, node* p){
        if(!l){
            p->left = p->right = p;
            l = p;
        }
        else{
            l->right->left = p;
            p->right = l->right;
            l->right = p;
            p->left = l;

            if(p->key<l->key){
                l = p;
            }
        }

        return l;
    }

    int numNodes(){
        return n;
    }

    int numNodes(node* r){
        int n = 0;
        if(r){
            n = 1;
            node* p = r->right;

            while(p!=r){
                n++;
                p=p->right;
            }
        }

        return n;
    }

    void link(node* y, node* z){

        //Remove y
        y->left->right = y->right;
        y->right->left = y->left;
        z->degree++;
        y->parent = z;

        node* c = z->child;
        if(!c){
            y->left = y->right = y;
            z->child = y;
        }
        else{
            c->right->left = y;
            y->right = c->right;
            c->right = y;
            y->left = c;
        }
    }

    void show(){
        show(min);
    }

    void show(node* r, string s = ""){
        if(r){
            node* p = r->right;

            cout<<"\n"<<s<<"Value:\t"<<r->key;
            cout<<"\n"<<s<<"Children:\n";
            show(r->child,s+"....");
            if( r == min || (r->parent!=NULL && r->parent->child==r)){
                while(p!=r){
                    cout<<"\n"<<s<<"Sibling:\n";
                    show(p,s);
                    p=p->right;
                }
            }
        }
    }

    void createChild(node* l1, node* l2){
        l2->degree+=numNodes(l1);

        node* l = l1;
        l->parent = l2;
        l = l->right;

        while(l!=l1){
            l->parent = l2;
            l=l->right;
        }

        if(!l2->child){
            l2->child = l1;
        }
        else{
            node* c=l2->child;
            node* cl = c->left;
            node* l1r = l1->right;

            c->left = l1;
            l1->right = c;
            cl->right = l1r;
            l1r->left = cl;
        }
    }
};

Fib concat(Fib a, Fib b){
    node* p = a.min;
    node* q = b.min;

    node* pl = p->left;
    node* qr = q->right;

    p->left = q;
    q->right = p;

    pl->right = qr;
    qr->left = pl;

    node* t = p->key<q->key?p:q;
    Fib f(t, a.n+b.n);
    return f;
}


int main()
{
    Fib f;
    cout<<"\nFirst:\n";

    f.fillrand(5);
    f.printList(f.min);
    cout<<"\nAfter Linking:\n";
    f.link(f.min->right,f.min);
    f.show();

    cout<<"\nSecond:\n";
    Fib a;
    a.fillrand(5);
    a.printList(a.min);

    cout<<"\nCombine:\n";

    Fib g = concat(a,f);
    g.show();

    cout<<"\nGetting Num in Root List:\t"<<f.numNodes(f.min);


    Fib h;
    h.fillrand(3);
    cout<<"\nThird\n";
    h.printList(h.min);

    g.createChild(h.min,g.min);
    g.show();

    return 0;
}
