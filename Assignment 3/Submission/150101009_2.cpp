/**
*
*   Assignment 3 - Binary Tree - Q2
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

	int num_leaves;

    BST(){
        root = NULL;
        num_leaves = 0;
    }

    void insert_node(T d){
        node<T>* p = createNode(d);
        insert_node(p,root);
    }

    //Insertion in O(h) time in worst case O(h) can become O(n^2) for a skewed tree.
    //While inserting n elements into the tree worst case time is O(n^2) as for inserting the ith node worst case time for insertion is O(i-1).
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

    //Since Each node is visited exactly once in the following procedure so O(n) time is taken to find number of leaves.
    void calc_leafnodes(node<T>* r){
        if(r!=NULL){
            if(isLeaf(r)){
				num_leaves++;
            }
            else{
                //Recursively Check if Children are leaves.
                calc_leafnodes(r->left);
                calc_leafnodes(r->right);
            }
        }
    }

    node<T>*& getRoot(){
        return root;
    }

};

int main(){
	BST<int> a;
	int n; 
	cout<<"NOTE: The notes are inserted in the manner that the Binary Search Property is Valid.\nEnter number of nodes to insert into the Tree:\t";
	cin>>n;
	
	cout<<"\nEnter the Elements to be Inserted:\t";
	for(int i= 0; i<n; i++){
		int x;
		cin>>x;
		a.insert_node(x);
	}
	cout<<"\nInorder Tracersal gives:\n";
	a.inorder(a.getRoot());
	a.calc_leafnodes(a.getRoot());
	cout<<"\n\nThe Number of Leaf Nodes are:\t"<<a.num_leaves;
    return 0;
}

