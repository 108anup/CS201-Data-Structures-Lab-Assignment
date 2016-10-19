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
    SM(int rows, int cols, int vals){
        header = createNode('d');
        header->d.row = rows;
        header->d.col = cols;
        header->d.val = vals;
        header->flag = 'd';

        int num_header_nodes = max(rows,cols);
        node* p;
        p=header;
        for(int i= 0; i<num_header_nodes; i++){
            node* temp = createNode('n');
            temp->right = temp->down = temp;
            temp->next = NULL;

            if(i==0){
                header->down = header->right = temp;
            }
            else{
                p->next = temp;
            }
            p = temp;
        }
    }

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
            node* element = row->right;
            while(element!=row){
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
        for(int i= 0; i<p->d.row; i++){
            row = row->next;
        }
        node* t = row;
        while(t->right!=row){
            if(t->right->d.col<p->d.col)
                t=t->right;
            else if(t->right->d.col==p->d.col){
                return false;
            }
            else
                break;
        }
        p->right = t->right;
        t->right = p;



        node* col = header->right;
        for(int i= 0; i<p->d.col; i++){
            col = col->next;
        }
        t = col;
        while(t->down!=col){
            if(t->down->d.row<=p->d.row)
                t=t->down;
            else if(t->down->d.row==p->d.row){
                return false;
            }
            else
                break;
        }
        p->down = t->down;
        t->down = p;

        return true;
    }

    void randomfill(){
        int num_rows = header->d.row;
        int num_cols = header->d.col;
        int num_el = header->d.val;

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
