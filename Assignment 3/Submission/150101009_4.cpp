/**
*
*   Assignment 3 - Binary Tree - Q4
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
#include <stdlib.h>
#include <climits>
#include <utility>
#include <string.h>
#include <vector>

const int MOD = 1e9+7;

#define NUM_REPS 50
#define NUM_EL 100

#define max(a,b) (a)>(b)?(a):(b)

using namespace std;

template <class T>
struct node{
    T data;
    node<T>* left;
    node<T>* right;
    node<T>* parent;

    node(){
        left = right = parent = NULL;
    }
};

template<class T>
node<T>* createNode(T d){
    node<T>* p = new node<T>;
    p->data = d;
    return p;
}

template<class T>
bool isLeaf(node<T>* p){
    return p->left==NULL && p->right==NULL;
}

template <class T>
class BST{

    node<T>* root;

public:

    BST(){
        root = NULL;
    }

    void insert_node(T d){
        node<T>* p = createNode(d);
        insert_node(p,root);
    }

    static void insert_node(node<T>* p, node<T>* &r){

        if(r==NULL){
            r = p;
        }
        else{
            p->parent = r;
            if(r->data>p->data){
                insert_node(p,r->left);
            }
            else{
                insert_node(p,r->right);
            }
        }
    }

    static void inorder(node<T>* root){
        if(root!=NULL){
            inorder(root->left);
            cout<<root->data<<" ";
            inorder(root->right);
        }
    }

    node<T>*& getRoot(){
        return root;
    }

    //Since each node is visited exactly once so T(n) = O(n)
    //This is a recursive algorithm for computing the Diameter.
    //Each time this method is called we return 2 things:
    //First is the The maximum depth of any node in the tree if r->parent is the root node
    //Second is the diameter of the tree considering r as the root node.
    pair<int, int> computeDiameter(node<T>* r){
        if(r!=NULL){
            pair<int,int> l = computeDiameter(r->left);
            pair<int,int> ri = computeDiameter(r->right);

            //Diameter is the Maximum of (the Diameter of the left sub tree, 
            //diameter of the right sub tree and 
            //the max_depth of a node in left sub tree + max_depth of a node in right sub tree)
            //NOTE: r is the LCA of the node in left sub tree with max depth and the node of the right sub tree with max depth
            int dia = max(ri.second,max(l.second,l.first+ri.first));
            int depth_wrt_parent = max(l.first,ri.first);
            depth_wrt_parent++;

            return make_pair(depth_wrt_parent,dia);
        }
        return make_pair(0,0);
    }
};


int main()
{
    BST<int> a;
	int n;
	cout<<"NOTE: The notes are inserted in the manner that the Binary Search Property is Valid.\n\nEnter number of nodes to insert into the Tree:\t";
	cin>>n;

	cout<<"\nEnter the Elements to be Inserted:\t";
	for(int i= 0; i<n; i++){
		int x;
		cin>>x;
		a.insert_node(x);
	}
	cout<<"\nInorder Tracersal gives:\n";
	a.inorder(a.getRoot());

	pair<int,int> x = a.computeDiameter(a.getRoot());

    cout<<"\nThe Diameter of the Tree is:\t"<<x.second;

    return 0;
}

