/**
*
*   Assignment 3 - Binary Tree - Q1
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
    int level;

    node(){
        left = right = parent = NULL;
        level = 0;
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

    int max_level;
    int min_level;

    BST(){
        max_level = -1;
        min_level = INT_MAX;
        root = NULL;
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

    //Since Each node is visited exactly once in the following procedure so O(n) time is taken
    //to calculate level for each node and also leaf node with max and min level.
    void calc_levels(node<T>* r){
        if(r!=NULL){

			//For root Node parent = NULL
			//For all other nodes level is level of parent +1
			if(r->parent==NULL)
				r->level = 0;
            else
                r->level = r->parent->level+1;
            //If the Node is a leaf node update max and min level appropriately
            if(isLeaf(r)){
                if(r->level>max_level)
                    max_level = r->level;
                if(r->level<min_level)
                    min_level = r->level;
            }
            else{
                //Recursively Update levels of the Children
                calc_levels(r->left);
                calc_levels(r->right);
            }
        }
    }

    node<T>*& getRoot(){
        return root;
    }

};

int main(){
    int counts[NUM_EL];
    memset(counts, 0, sizeof(counts));
    cout<<"Table of Maximum and Minimum level leaf nodes\nSno., Max Level, Min Level\n";
    for(int j = 0; j<NUM_REPS ;j++){
        BST<int> a;
        for(int i= 0; i<NUM_EL; i++){
            a.insert_node(rand()%MOD);
        }
        a.calc_levels(a.getRoot());
        cout<<j+1<<", "<<a.max_level<<", "<<a.min_level<<endl;
        counts[a.max_level-a.min_level]++;
    }
    cout<<"\n\n";
    cout<<"MaxLevel-MinLevel Frequency Table\n\nDifference, Frequency\n";
    //Maximum possible difference is equal to NUM_EL but most of the times the difference is very less in comparison to NUM_El due to random data distribution.
    for(int i = 0; i<NUM_EL; i++){
//        if(counts[i]!=0)
            cout<<i<<", "<<counts[i]<<"\n";
    }
    return 0;
}

