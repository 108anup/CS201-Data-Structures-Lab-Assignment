#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

struct node{
    node* left;
    node* right;
    node* child;
    node* parent;
    int data;
    int degree;
    bool mark;

    node(){
        left = right = child = parent = NULL;
        degree = data = 0;
        mark = false;
    }
};

node* createNode(){
    node* p = new node;
    return p;
}

class Fib{

    node* min;
    int n;
public:

    Fib(){
        min = NULL;
        n = 0;
    }

    Fib(node * p, int k){
        min = p;
        n = k;
    }

    int minimum(){
        if(min){
            return min->data;
        }
        else{
            cout<<"\nERROR:: No Element in Heap\n";
            return -1;
        }
    }

    void insert(int x){
        node * p = createNode();
        p->data = x;

        insert(p);
    }

    void insert(node* p){
        if(!min){
            min = p;
            p->left = p->right = p;
        }
        else{
            min->right->left = p;
            p->right = min->right;
            p->left = min;
            min->right = p;

            if(p->data<min->data){
                min = p;
            }
        }
        n++;
    }

    int extractMin(){
        if(min){
            int ret = min->data;
            node* c = min->child;

            if(c){
                min->child = NULL;
                node* p = c;

                while(p->parent){
                    p->parent = NULL;
                    node* r = p->right;
                    insert(p);
                    p=r;
                }
            }
            else if(n==1){
                delete min;
                return ret;
            }
            n--;
            //Delete Min updating pointers
            node* m = min;
            m->left->right = min->right;
            m->right->left = min->left;
            node* p = min->right;
            delete min;
            min = p;

//            cout<<"\nBefore Consolidation"<<endl;
//            show();

            consolidate();
            return ret;
        }
        else{
            cout<<"\nERROR:: No Element in heap\n";
            return -1;
        }
    }

    void consolidate(){
        int s = int(log(n)/log(2)) + 2;
        vector<node*> a(s);

        for(int i= 0; i<s; i++){
            a[i] = NULL;
        }
        a[min->degree]=min;
        node* p = min->right;
        node* starting = min;
        while(p && p!=starting){
            int d = p->degree;
            while(a[d]){
                node* t = a[d];

                if(p->data > t->data){
                    node* temp = p;
                    p = t;
                    t = p;
                }
                if(t==starting){
                    starting = p;
                }
                makeChild(t,p);
                a[d] = NULL;
                d++;
            }
            a[d] = p;
            p = p->right;
        }
        int minval = starting->data;
        node* minptr = starting;

        p = starting->right;

        while(p!=starting){
            if(p->data<minval){
                minval = p->data;
                minptr = p;
            }
            p=p->right;
        }
        min = minptr;
    }

    void makeChild(node* y, node* x){
        x->degree++;
        y->mark = false;

        //Remove y from root list
        y->left->right = y->right;
        y->right->left = y->left;

        node* c = x->child;

        if(c){
            c->right->left = y;
            y->right = c->right;
            c->right = y;
            y->left = c;
        }
        else{
            x->child = y;
            y->right = y->left = y;
        }
        y->parent = x;
    }

    void show(){
        show(min);
    }

    void show(node* root, string s= ""){
        if(root){
            node* p = root;
            cout<<endl<<s<<"Value: "<<root->data;
            cout<<endl<<s<<"Children:\n";
            show(p->child, s+"....");
            p=root->right;
            if((root->parent!=NULL && root->parent->child == root) || root == min){
                while(p!=root){
                    cout<<endl<<s<<"Sibling:\n";
                    show(p,s);
                    p=p->right;
                }
            }
        }
    }
};

int main()
{

    Fib f;
    f.insert(2);
    f.insert(3);
    f.insert(1);
    f.insert(5);
    f.insert(7);
    f.show();
    cout<<"\nMinimum:"<<f.extractMin();
    f.show();
    int z = f.extractMin();
    cout<<"\nMinimum:"<<z<<endl;
    f.show();
    cout<<"\nMinimum:"<<f.extractMin();
    f.show();
    f.insert(2);
    f.insert(3);
    f.insert(1);
    f.show();
    cout<<"\nMinimum:"<<f.extractMin();
    f.show();
    return 0;
}
