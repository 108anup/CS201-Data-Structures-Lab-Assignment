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
    int depth;

    node(){
        left = right = parent = NULL;
        depth = level = 0;
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
    int num_leaves;

    BST(){
        max_level = -1;
        min_level = INT_MAX;
        root = NULL;
        num_leaves = 0;
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
            p->level+=1;
            p->parent = r;
            if(r->data>p->data){
                insert_node(p,r->left);
            }
            else{
                insert_node(p,r->right);
            }
        }
    }

    void preorder(node<T>* root, bool verbose = false){
        if(root!=NULL){
            if(verbose)
                cout<<root->data<<" ";
            preorder(root->left);
            preorder(root->right);
        }
    }

    static void inorder(node<T>* root){
        if(root!=NULL){
            inorder(root->left);
            cout<<root->data<<" ";
//            cout<<root->level<<endl;
            inorder(root->right);
        }
    }

    static void postorder(node<T>* root){
        if(root!=NULL){
            postorder(root->left);
            postorder(root->right);
            cout<<root->data<<" ";
//            cout<<root->level<<endl;
        }
    }

    void calc_levels(node<T>* r){
        if(r!=NULL){
            if(isLeaf(r)){
                num_leaves++;   //Each node is visited exactly once therefore, in Calculation of Number of Leaves it takes O(n) time.
                if(r->level>max_level)
                    max_level = r->level;
                if(r->level<min_level)
                    min_level = r->level;
            }
            else{
                calc_levels(r->left);
                calc_levels(r->right);
            }
        }
    }

    node<T>*& getRoot(){
        return root;
    }

    /**METHOD 1 for LCA*/

    //Each Node is visited Atmost once so overall O(n) time.
    //FULL Traversal for Normal Tree
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

    //if we have the pointers to the nodes for whom we need to find LCA are given
    //since from each node we traverse up along a simle path we take atmost O(h) computations
    //so this method completes in O(h) time.
    node<T>* findLCA(node<T>* a, node<T>* b){
        if(a==NULL || b==NULL)
            return NULL;

        vector< node<T>* > parents1;
        vector< node<T>* > parents2;
        node<T>* temp = a;
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

        while(parents1[i1]==parents2[i2] && i1>=0 && i2>=0){
            i1--;i2--;
        }
        if(i2==-1)
            return parents2[i2+1];
        else return parents1[i1+1];
    }

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

    /**METHOD 2 for LCA */

    //Since each node is visited exactly once so T(n) = O(n)
    //This works only if either both the values are present or none of them are present
    //If exactly one of the values is present then pointer to that node is returned.
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

    //Since each node is visited exactly once so T(n) = O(n)
    //Diameter is calculated by max_depth + second_max_depth whcih are found using the following method and so takes O(n) time.
    //Diameter = max(dv+dw-2du) over all v and w for maximum take nodes such that lca is root and v and w are leaf nodes with largest depth
    pair<int, int> computeDiameter(node<T>* r){
        //second is diamter and first is max depth of a node in the tree with root as r.
        if(r!=NULL){
            pair<int,int> l = computeDiameter(r->left);
            pair<int,int> ri = computeDiameter(r->right);

            int dia = max(ri.second,max(l.second,l.first+ri.first));
            int depth_wrt_parent = max(l.first,ri.first);
            depth_wrt_parent++;

            return make_pair(depth_wrt_parent,dia);
        }
        return make_pair(0,0);
    }
};

void q1and2(){
    int counts[NUM_EL];
    memset(counts, 0, sizeof(counts));
    cout<<"Max Level\tMin Level\n";
    for(int j = 0; j<NUM_REPS ;j++){
        BST<int> a;
        for(int i= 0; i<NUM_EL; i++){
            a.insert_node(rand()%MOD);
        }
        a.calc_levels(a.getRoot());
        cout<<a.max_level<<"\t\t"<<a.min_level<<"\t\t"<<a.num_leaves<<endl;
        counts[a.max_level-a.min_level]++;
    }
    cout<<"\n\n";
    cout<<"MaxLevel-MinLevel\tFrequency\n";
    for(int i = 0; i<NUM_EL; i++){
//        if(counts[i]!=0)
            cout<<i<<"\t\t\t"<<counts[i]<<"\n";
    }
}

void lcacheck(){
    BST<int> a;
    a.insert_node(20);
    a.insert_node(8);
    a.insert_node(22);
    a.insert_node(4);
    a.insert_node(12);
    a.insert_node(10);
    a.insert_node(14);

    node<int>* n1 = a.getRoot()->left->right->left;
    node<int>* n2 = a.getRoot()->right;

    cout<<n1->data<<" "<<n2->data<<" "<<a.findLCA(14,14,a.getRoot())->data;
}


int main()
{
    BST<int> a;
    a.insert_node(20);
    a.insert_node(8);
    a.insert_node(5);
    a.insert_node(10);
    a.insert_node(6);
    a.insert_node(3);
    a.insert_node(2);
    a.insert_node(12);
//    a.insert_node(22);
//    a.insert_node(24);
    pair<int,int> x = a.computeDiameter(a.getRoot());

    cout<<x.second;

    return 0;
}
