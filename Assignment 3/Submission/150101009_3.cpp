/**
*
*   Assignment 3 - Binary Tree - Q3
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

    /**METHOD 1 for LCA*/
    
    //we first find pointers to the nodes using the values then call {node<T>* findLCA(node<T>*, node<T>*)}
    //Finding Node Pointers takes O(n) for general Binary Tree and O(h) for Binary Search Tree
    //Then Finding LCA from the node pointers takes O(h) time
    //For general Binary Tree overall time O(n) and for BST overall time O(h)
    node<T>* findLCA(T v1, T v2, bool searchppt = false){
        //each findNodeByValue takes O(n) time and findLCA(node<T>*, node<T>*) takes O(h) time.
        //so overall time is O(n+h) = O(n).
        if(searchppt == false)
            return findLCA(findNodeByValue(v1,root),findNodeByValue(v2,root));

        //Below is used if the Tree has search Property then finding pointers takes O(h) time and another O(h) time for copmuting LCA using pointers
        //So overall Complexity in this case would be O(h).
        else
            return findLCA(findNodeByValue_BinarySearchTree(v1,root),findNodeByValue_BinarySearchTree(v2,root));

    }
    
    //if we have the pointers to the nodes for whom we need to find LCA are given
    //since from each node we traverse up along a simle path we take atmost O(h) computations
    //so this method completes in O(h) time.
    node<T>* findLCA(node<T>* a, node<T>* b){
        if(a==NULL || b==NULL)
            return NULL;

        vector< node<T>* > parents1;
        vector< node<T>* > parents2;
        node<T>* temp = a;

        //Traverse from node to root and keep saving the path.
        while(temp!=NULL){
            parents1.push_back(temp);
            temp = temp->parent;
        }
        temp = b;
            while(temp!=NULL){
            parents2.push_back(temp);
            temp = temp->parent;
        }
        int i1 = parents1.size()-1;
        int i2 = parents2.size()-1;

        //Both the Paths have to meet at root in all cases so parents1[parents1.size()-1] is equal to parents2[parents2.size()-1] = root
        //The First point at which the difference in path occurs signfies the LCA.
        //i.e. the last element which is present in both the arrays when traversing from the end is the LCA.
        // because after this node the paths to the nodes become different.
        while(parents1[i1]==parents2[i2] && i1>=0 && i2>=0){
            i1--;i2--;
        }
        if(i2==-1)
            return parents2[i2+1];
        else return parents1[i1+1];
    }

    //Each Node is visited exactly once so overall O(n) time.
    //This is used for a general tree in which the search property might not be available.
    node<T>* findNodeByValue(T a, node<T>* r){
        if(r==NULL || r->data==a)
            return r;
        else{
            node<T>* p = findNodeByValue(a,r->left);
            if(p==NULL)
                return findNodeByValue(a,r->right);
            else return p;
        }
    }

    //Since we just traverse along a simple path from root to a leaf node the maximum time taken is O(h). h is the height of the tree.
    node<T>* findNodeByValue_BinarySearchTree(T a, node<T>* r){
        if(r==NULL || r->data == a)
            return r;
        else if(r->data>a)
            return findNodeByValue_BinarySearchTree(a,r->left);
        else return findNodeByValue_BinarySearchTree(a,r->right);
    }    

    /**METHOD 2 for LCA */

    //Since each node is visited exactly once so T(n) = O(n)
    //This works only if either both the values are present or none of them are present
    //If exactly one of the values is present then pointer to that node is returned instead of NULL or error.
    node<T>* findLCA(T a, T b, node<T>* r){
        //if r is not NULL and matches with one of the values then return r to show its presence
        if(r == NULL || r->data==a || r->data==b)
            return r;

        node<T>* left_lca = findLCA(a,b,r->left);
        node<T>* right_lca = findLCA(a,b,r->right);

        //if both left and right lca return non NULL values this implies that
        //one node is in the Left sub tree of the root (r) and other is in the right sub tree thus r is the LCA
        if(left_lca && right_lca)
            return r;
        //This happens if the LCA exists in the Left sub tree or the right sub tree or both the values are not found.
        else return left_lca == NULL ? right_lca:left_lca;

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

	char res = 'Y';

    do{
        cout<<"\n\nEnter the Value of the 2 Nodes for which you want to find LCA:\n";
        int x1,x2;
        cin>>x1>>x2;

        node<int>* p1 = a.findLCA(x1,x2);
        node<int>* p2 = a.findLCA(x1,x2,a.getRoot());
        //cout<<p1<<" "<<p2;

        if(p1!=NULL && p2!=NULL){

            cout<<"\nMethod 1:\n";
            cout<<"The LCA of "<<x1<<" and "<<x2<<" is the Node with data: "<<p1->data;
            cout<<"\n\nMethod 2:\n";
            cout<<"The LCA of "<<x1<<" and "<<x2<<" is the Node with data: "<<p2->data;

        }
        else{
            cout<<"\nOne or more of the nodes given are not present in the Tree.";
        }

        cout<<"\n\nEnter Another Pair of Nodes to Find LCA? (y/N):\t";
        cin>>res;
        
    }while(res=='Y' || res=='y');
    return 0;
}

