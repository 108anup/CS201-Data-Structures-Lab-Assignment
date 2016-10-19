/**
*
*   Assignment 4 - Binary Tree - Q3
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
#include <climits>
#include <math.h>
#include <stdlib.h>

using namespace std;

#define max(a,b) (a)>(b)?(a):(b)

struct data{
    int row;
    int col;
    int val;
};

struct node{
    node* right;
    node* down;

    char flag; //'d' for using data and 'n' for using next;

    union{
        node* next;
        data d;
    };

    node(char f){
        down = right = NULL;
        flag = f;
        if(f=='n')
            next =NULL;
        else{
            d.val = 0;
            d.col = 0;
            d.row = 0;
        }
    }
};

node* createNode(char f){
    node* p = new node(f);
    return p;
}

class SM{
    node* header;

    public:
    
    //Initialize all the Header Nodes
    SM(int rows, int cols, int vals){
        header = createNode('d');
        header->d.row = rows;
        header->d.col = cols;
        header->d.val = vals;
        header->flag = 'd';
        //NOTE: down and right of the header node both point to the next header node.

        int num_header_nodes = max(rows,cols);
        node* p;
        p=header;
        
        //Make LInks of the Header nodes
        for(int i= 0; i<num_header_nodes; i++){
            node* temp = createNode('n');
            temp->right = temp->down = temp;
            //initially the down and right of each header node (apart from main header) points ot itself.
            temp->next = NULL;

            if(i==0){
                header->down = header->right = temp;
            }
            else{
                p->next = temp;
                //p is the previous header node.
                //so its next points to the next header node.
            }
            p = temp;
        }
    }

	//Returns Random number between [i,j] inclusive
    int getRandomNum(int i, int j){
        if(i>=j)
            return i;
        else
            return rand()%(j-i+1) +i;
    }

    int findMax(){
        node* row = header->down;
        int max_el = INT_MIN;
        int r = 0;
        while(row!=NULL){
            cout<<"Row no. "<<r<<"\t";
            //traverse each row untill the pointer the row is reached and 
            //check if element if greater than current maximum
            node* element = row->right;
            while(element!=row){
            	//Also Printing the Elements while Traversing
                cout<<element->d.row<<","<<element->d.col<<","<<element->d.val<<"\t";
                if(element->d.val>max_el)
                    max_el = element->d.val;
                element = element->right;
            }
            cout<<"\n";
            row=row->next;
            r++;
        }
        return max_el;
    }

    bool insertnode(node* p){
        node* row = header->down;
        //reach the row into which the node has to be inserted
        for(int i= 0; i<p->d.row; i++){
            row = row->next;
        }
        node* t = row;
        //reach the node whose right will be p (it will be either the last or a 
        //node whose right's column is greater than column of p)
        while(t->right!=row){
            if(t->right->d.col<p->d.col)
                t=t->right;
            else if(t->right->d.col==p->d.col){
                return false;
            }
            else
                break;
        }
        //make the appropriate links
        p->right = t->right;
        t->right = p;



        node* col = header->right;
        //reach the column into which the node has to be inserted
        for(int i= 0; i<p->d.col; i++){
            col = col->next;
        }
        t = col;
        //reach the node whose down will be p (it will be either the last or a 
        //node whose down's row is greater than row of p)
        while(t->down!=col){
            if(t->down->d.row<=p->d.row)
                t=t->down;
            else if(t->down->d.row==p->d.row){
                return false;
            }
            else
                break;
        }
        //make the appropriate links
        p->down = t->down;
        t->down = p;

        return true;
    }

    void randomfill(){
        int num_rows = header->d.row;
        int num_cols = header->d.col;
        int num_el = header->d.val;
		//generate random row, col, val tuples and try inserting if already found then repeat.
        for(int i= 0; i<num_el; i++){
            node* p = createNode('d');
            p->d.row = getRandomNum(0,num_rows-1);
            p->d.col = getRandomNum(0,num_cols-1);
            p->d.val = getRandomNum(0,100);

            if(!insertnode(p)){
                i--;
            }
        }

    }
};

int main()
{
    srand(time(NULL));
    int r,c,n;
    cout<<"Enter the Rows and Columens Separated By a Space:\n";
    cin>>r>>c;
    cout<<"Enter the Number of non zero elements (less than or equal to "<<r*c<<"):\n";
    cin>>n;
    SM m(r,c,n);
    m.randomfill();

    cout<<"The Matrix Stands as in form of (row,col,val) tuples (indexing base 0):\n";
    int maxima = m.findMax();
    cout<<"\nMaximum Element is:\n";
    cout<<maxima;

    return 0;
}
