#include <iostream>
#include <queue>

using namespace std;

struct node{
    int data;
    node* parent;
    node* child;
    node* next;
    int ht; //Represents the length of the path from root to the current node
};


//Allocates and initialises a node
node* createNode(int x){
    node* p = new node;
    p->parent = p->child = p->next = NULL;
    p->data = x;
    p->ht = 0;

    return p;
}

class SibTree{

    //Root and size of the tree
    node* root;
    int s;

    public:

    SibTree(){
        root= createNode(1);
        s =1;
    }

    //Prints the Tree in Breadth First Search Fashion
    void BFS(){
        cout<<"\nSize:\t"<<s;
        cout<<"\nTree:\n";
        if(root){
            int prevht = 0;
            queue<node*> q;
            q.push(root);
            //^ Initialised a Queue with the root element

            while(!q.empty()){
                //pop the top element
                node* p = q.front();
                q.pop();

                //if a height change takes place implies need to go to new line
                if(p->ht>prevht){
                    cout<<"\n";
                    prevht = p->ht;
                }
                cout<<p->data<<" ";
                node* t = p->child;

                //insert all its children for inspection next
                while(t){
                    q.push(t);
                    t=t->next;
                }
            }
        }
    }

    //Inserts an element as the cth child of node with value as x in O(s) time
    void insert(int x, int y, int c){
        if(c<1)
            c=1;
        //Find the node whose child we want to make
        node* p = find(root,x);

        if(p){
            s++; //Update size of Tree
            //get the child of the node
            node* t = p->child;
            c--; //c represents number of shifts rather than location of element insertion after decrement

            //Initialise node and add parent
            node* tbi = createNode(y);
            tbi->parent = p;
            tbi->ht = p->ht+1;

            //If the node does not have any children or no shift is required we just make tbi as the first node of the child list
            if(c==0 || t==NULL){
                p->child = tbi;
                tbi->next = t; //t is NULL if p has no children initially
            }
            else{
                node* prev = NULL; //Represents the node previous to the place where we have to insert the node
                //Note this loop will run atleast once as c>=1 and t!=NULL in the else part
                //And so prev will have a Non NULL Value always
                for(int i= 0; i<c && t!=NULL; i++){
                    prev = t;
                    t=t->next;
                }

                //we need to insert tbi after rpev and before t
                prev->next = tbi;
                tbi->next = t;
            }
        }
        //The case when the node with value x is not found.
        else{
            cout<<"\n\nERROR:: Node with Value "<<x<<" not Found";
        }
    }

    //Recursively traverses the full tree to find the node with a given value
    //Takes O(s) time.
    node* find(node* r,int k){

        if(r){
            //If match found then return
            if(r->data==k)
                return r;
            //Else check the children
            node* p = find(r->child,k);
            if(p)
                return p;
            //Else check the sibling recursively
            p = find(r->next,k);
            if(p)
                return p;
        }
        //If not found in next and sibling return NULL
        return NULL;
    }

    //Takes O(s) time to remove the node with input value
    void remove(int k){
        //Find the pointer to the Node to be deleted
        node* p= find(root,k);

        if(p && p->child==NULL){
            s--;
            node* par = p->parent;
            node* prev;
            node* t = par->child;

            //Try to find the element previous to the node to be deleted in the child linked list of the parent
            while(t->data != k){
                prev = t;
                t=t->next;
            }

            //If there is such a previous elment then make the next of prev as the next of p
            //Then delete the node
            if(prev){
                node* temp = p;
                prev->next = p->next;
                delete p;
            }
            //If such prev element does not exists that means the first child is to be removed then update the parent's child
            //Then delete node (Deallocate memory)
            else{
                node* temp = p;
                par->child = p->next;
                delete p;
            }
        }
    }


};

int main()
{
    SibTree s;
    s.insert(1,2,1);
    s.insert(1,3,2);
    s.insert(1,4,3);
    s.insert(1,5,4);
    s.insert(2,6,1);
    s.insert(2,7,2);
    s.insert(2,8,3);
    s.insert(4,9,1);
    s.insert(9,12,1);
    s.insert(5,10,1);
    s.insert(5,11,2);
    s.BFS();

    s.remove(7);
    cout<<"\n\n";s.BFS();

    s.remove(3);
    cout<<"\n\n";s.BFS();

    s.insert(2,99,2);
    s.insert(9,44,2);
    s.insert(5,88,1);
    s.insert(7,22,1);

    cout<<"\n\n";s.BFS();

    s.remove(4);
    cout<<"\n\n";s.BFS();


    return 0;
}