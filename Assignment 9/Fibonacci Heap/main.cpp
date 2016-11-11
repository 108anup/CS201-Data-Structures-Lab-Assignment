#include <iostream>
#include <math.h>
#include <vector>
#include <stdio.h>

using namespace std;

int countme;
int count_nodes;

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
    public:
    int n;

    node* min;

    Fib(){
        min = NULL;
        n = 0;
    }

    Fib(node * p, int k){
        min = p;
        n = k;
    }

    //Finds the Minimum of the Heap in O(1) time.
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
        n++;
    }

    //Inserts an Element to the Heap in O(1) time.
    void insert(node* p){
        //If First node then min = p
        if(!min){
            min = p;
            p->left = p->right = p;
        }
        //Make Appropraite pointer changes
        else{
            min->right->left = p;
            p->right = min->right;
            p->left = min;
            min->right = p;

            if(p->data<min->data){
                min = p;
            }
        }
    }


    //Extracts the minimum of the nodes in the heap in O(log(n)) time amortized.
    int extractMin(){
        if(min){
            n--;
            int ret = min->data;
            node* c = min->child;

            //Add all the children of min to root list
            if(c){
                min->child = NULL;
                node* p = c;

                while(p->parent){
                    p->parent = NULL;
                    node* r = p->right;
                    insert(p);
//                    n--;
                    p=r;
                }
            }
            //Note that we have already reduced n in the begininning of the function so
            //n==0 means there was only 1 element.
            else if(n==0){
                delete min;
                min=NULL;
                return ret;
            }
            //Delete Min updating pointers
            node* m = min;
            m->left->right = min->right;
            m->right->left = min->left;
            node* p = min->right;
            delete min;
            min = p;

            consolidate();
            return ret;
        }
        else{
            cout<<"\nERROR:: No Element in heap\n";
            return -1;
        }
    }

    //Consolidate function ensures that there are atmost 1 nodes in the root list with a given degree
    //This is done in O(log(n)) time amortized
    void consolidate(){
        if(n>0){

            vector<node*> rootlist;
            node* p = min->right;

            rootlist.push_back(min);

            while(p!=min){
                rootlist.push_back(p);
                p=p->right;
            }

            int s = int((log(n)+0.0)/log(2)) + 5;
            //s = n;
            vector<node*> a(s);

            for(int i= 0; i<s; i++){
                a[i] = NULL;
            }

            //Traverse through the rootlist
            for(int i= 0; i<rootlist.size(); i++){
                node* p = rootlist[i];
                int d = p->degree;
                //Check if a node of degree d is already present.
                while(a[d]!=NULL){
                    node* t = a[d];

                    //t represents the larger of p and t so it will become child of p
                    if(p->data > t->data){
                        node* temp = p;
                        p = t;
                        t = temp;
                    }
                    makeChild(t,p);
                    a[d] = NULL;
                    d++;
                }
                a[d] = p;
            }

            min = NULL;
            for(int i = 0; i<s; i++){
                if(a[i]){
                    a[i]->left = a[i];
                    a[i]->right = a[i];
                    insert(a[i]);
                }
            }
        }
    }


    //Function that makes y as the child of x in O(1) time.
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
            countme++;
            node* p = root;
            cout<<endl<<s<<"Value: "<<root->data<<", Degree: "<<root->degree;
            cout<<endl<<s<<"Children:\n";
            show(p->child, s+".......");
            p=root->right;
            if((root->parent!=NULL && root->parent->child == root) || root == min){
                while(p!=root){
                    cout<<endl<<s<<"Sibling:\n";
                    show(p,s);
                    p=p->right;
                }
            }
        }
        else{
            cout<<s<<"None\n";
        }
    }
    void CC(node* root){
        if(root){
            count_nodes++;
            node* p = root;
            CC(p->child);
            p=root->right;
            if((root->parent!=NULL && root->parent->child == root) || root == min){
                while(p!=root){
                    CC(p);
                    p=p->right;
                }
            }
        }
    }
    void showrootlist(){
        if(min){
            cout<<endl<<"Value: "<<min->data<<", Degree: "<<min->degree;
            node* p = min->right;

            while(p!=min){
                cout<<endl<<"Value: "<<p->data<<", Degree: "<<p->degree;
                p=p->right;
            }
        }
    }
};

Fib union_fib(Fib a, Fib b){
    node* p = a.min;
    node* q = b.min;

    node* pl = p->left;
    node* qr = q->right;

    p->left = q;
    q->right = p;

    pl->right = qr;
    qr->left = pl;

    node* t = p->data<q->data?p:q;
    Fib f(t, a.n+b.n);
    return f;
}

int main()
{

    Fib f;


//    f.insert(2);
//    f.insert(3);
//    f.insert(1);
//    f.insert(5);
//    f.insert(7);
//    f.show();
//    cout<<"\nMinimum:"<<f.extractMin();
//    f.show();
//    int z = f.extractMin();
//    cout<<"\nMinimum:"<<z<<endl;
//    f.show();
//    cout<<"\nMinimum:"<<f.extractMin();
//    f.show();
//    f.insert(2);
//    f.insert(3);
//    f.insert(1);
//    f.show();
//    cout<<"\nMinimum:"<<f.extractMin();
//    f.show();

    freopen("2.txt","r",stdin);


    /**
    Please remove Comments from the input file for testing, i.e. remove the lines starting with # from the input file.
    While testing from file make flag = false
    else keep it true.
    */

    char ch;
    int e;
    bool flag = false;
    bool v = true;
    if(flag){
        cout<<"\nEnter the Choice:\n(c,i,e,u,S for Create, Insert, Extract Min, Union and Show Respectively)\n";
    }

    Fib f1,f2,f3;

    while(cin>>ch){
        int x;

        switch(ch){

            case 'c':
                break;
            case 'u':
                f1.insert(3);
                f1.insert(6);
                f1.insert(8);
                f1.insert(1);

                f2.insert(5);
                f2.insert(0);
                f2.insert(9);
                f2.insert(10);
                f2.insert(12);

                f1.extractMin();
                f2.extractMin();

                f1.insert(5);
                f1.insert(111);
                f1.insert(2);
                f1.extractMin();

                f2.insert(19);

                cout<<"\nTaking union of 2 Heaps:\n--------------------\nFirst Heap:\n";
                f1.show();
                cout<<"\n--------------------\nSecond Heap:\n";
                f2.show();

                f3 = union_fib(f1,f2);
                cout<<"\n--------------------\nAfter Union:\n";
                f3.show();

                break;
            case 'i':
                if(flag)
                    cout<<"\nEnter the Value to Insert:\t";
                    cin>>x;
//                    cout<<"\nCurrent Count: "<<f.n;
                    f.insert(x);
//                    cout<<"\nInserting: "<<x<<"\n";
                break;
            case 'e':
                e = f.extractMin();
                if(v){
                    cout<<"\nExtracted is:\t"<<e;
                }
                break;
            case 'p':
                f.consolidate();
                f.show();
                break;
            case 'S':
                cout<<"\n";
                f.show();
                break;
            case '+':
                v = true;
                break;
            case '-':
                v = false;
                break;
            default:
                cout<<"\nPlease Choose Correct Option...\n";
                break;
        }
        if(flag){
            cout<<"\nEnter the Choice:\n(c,i,e,u,S for Create, Insert, Extract Min, Union and Show Respectively)\n";
        }
    }


    return 0;
}

