/**
*
*   Assignment 10 - BST and Hashing Q3.
*   CS 210 - Data Structures (Fall Sem, 2016)
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

using namespace std;

struct node{
    node* left;
    node* right;
    node* parent;
    long long int key;
    string title;
    string author;
    int year;
    int cost;
    long long int num_copies_sold;
};

//Initialize Node
node* createNode(){
    node* t = new node;
    t->left = t->right = t->parent = NULL;
    t->key = 0;
    t->title = "";
    t->author = "";
    t->year = t->cost = t->num_copies_sold = 0;
}

class BST{

    public:
    node* root;

    BST(){
        root = NULL;
    }

    //BST insert in O(h) h = height of Tree for balanced BST it will be O(log(n)) in worst case it is O(n)
    void insert(node* p,node* &r){
        //If node is there check its value
        if(r){
            //If roots value is greater then insert in LST else RST (Left and Right Sub Tress Respectively)
            if(r->key > p->key){
                insert(p,r->left);
            }
            else{
                insert(p,r->right);
            }
        }
        else{
            r = p;
        }
    }

    //BST Search in O(h)
    node* search(long long int isbn, node* r){
        if(r){
            //If Key Matches then done
            if(r->key == isbn)
                return r;
            //If key is bigger than to be searched then go for LST else RST
            else if(r->key>isbn)
                return search(isbn,r->left);
            else
                return search(isbn,r->right);
        }
        else{
            return NULL;
        }
    }

    //Inorder traversal visiting each node once in O(n) time in sorted order
    void inorder(node* r, void (*fn)(node* p)){
        if(r){
            //First invoke LST then root then RST
            inorder(r->left,fn);
            //fn is the function to be invoked on each node of the tree
            //Can be used to Display all values, update all values etc.
            fn(r);
            inorder(r->right,fn);
        }
    }

};

node* getBook(){
    node* p = createNode();
    cin.ignore();
    cout<<"\nEnter Title: ";
    getline(cin,p->title);
    cout<<"\nEnter Author: ";
    getline(cin,p->author);
    cout<<"\nEnter ISBN (13 digit): ";
    cin>>p->key;
    cout<<"\nEnter Year: ";
    cin>>p->year;
    cout<<"\nEnter Cost: ";
    cin>>p->cost;
    cout<<"\nEnter Number of Copies Sold: ";
    cin>>p->num_copies_sold;

    return p;
}

node* makeNode(string title, string author, long long int isbn, int yr, int cst, int numcps){
    node* p = createNode();
    p->title = title;
    p->author = author;
    p->key = isbn;
    p->year = yr;
    p->cost = cst;
    p->num_copies_sold = numcps;
    return p;
}

void show(node* p){
    cout<<"\nTitle: "<<p->title;
    cout<<"\nAuthor: "<<p->author;
    cout<<"\nISBN: "<<p->key;
    cout<<"\tYear: "<<p->year;
    cout<<"\nCost: "<<p->cost;
    cout<<"\nCopies Sold: "<<p->num_copies_sold<<endl;
}

void inc10percent(node* p){
    p->cost = 1.1 * p->cost;
}

void showcopies(node* p){
    if(p){
        cout<<"\nTitle: "<<p->title;
        cout<<"\nISBN: "<<p->key;
        cout<<"\nCopies Sold: "<<p->num_copies_sold<<endl;
    }
    else{
        cout<<"\nBook Not Found!\n";
    }
}

int main()
{
    BST a;
    //Insert 5 dummy books
    a.insert(makeNode("Introduction to Algorithms","Cormen",9788120340077,2005,1000,10234000),a.root);
    a.insert(makeNode("Psychology","Baron",9788177583854,2005,1000,1000000),a.root);
    a.insert(makeNode("Chanakya's Chant","Ashhwin Sanghi",9789381626818,2005,200,10000450),a.root);
    a.insert(makeNode("Take Charge of Your Life","Anup Agarwal",9788120340068,2013,150,9986372),a.root);
    a.insert(makeNode("The Election that Changed India","Cormen",9780143424987,2015,400,999991232),a.root);

    while(true){
        int ch;
        cout<<"\nMAIN MENU";
        cout<<"\n1. Show all Books";
        cout<<"\n2. Add Book";
        cout<<"\n3. Increase Cost by 10%";
        cout<<"\n4. Show Sold Copies";
        cout<<"\n9. End";
        cout<<"\nChoice:\t";
        cin>>ch;

        long long int x;
        switch(ch){
            case 1:
                a.inorder(a.root,show);
                break;
            case 2:
                a.insert(getBook(),a.root);
                break;
            case 3:
            	//Traverse the Full Tree and Increase Cost of each by 10%
                a.inorder(a.root,inc10percent);
                cout<<"\nDone\n";
                break;
            case 4:
                cout<<"\nEnter ISBN: ";
                cin>>x;
                showcopies(a.search(x,a.root));
                break;
            case 9:
                return 0;
            default:
                break;
        }
    }

    return 0;
}
