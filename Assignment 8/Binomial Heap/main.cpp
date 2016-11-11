/**
*
*   Assignment 8 - Binomial Heap Q1.
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
#include <stdio.h>

using namespace std;

//Function that prints spaces equal to the number given
void printspace(int x){
    for(int i= 0; i<x; i++){
        cout<<" ";
    }
}

struct node{
    node* parent;
    node* leftMostChild;
    node* sibling;
    int val;
    int degree;

    node(){
        parent = leftMostChild = sibling = NULL;
        val = degree = 0;
    }
};

node* createNode(int val){
    node * p = new node;
    p->val = val;
    return p;
}

//For n element Binomial heap the number of elements in root list will be O(log(n)) atmost floor(log(n)) +1 to be precise.
class BHeap{

public:

    node* head;

    BHeap(){
        head = NULL;
    }

    BHeap(node* h){
        head = h;
    }

    //Function that Unites 2 Heaps of sizes n1 and n2 in O(log(n1) + log(n2)) time.
    //The root list of the Binomial Heap becomes O(log(n1) + O(log(n2)) after the merge step
    //In each iteration of the loop we reduce the size of root list by either 1 or we move to the next element
    //So Elements remaining to cover in the subsequent iterations decreases by one thus time taken will be at most O(log(n1) + log(n2))
    static BHeap Union(BHeap h1, BHeap h2){

        BHeap f;
        //First Merge the 2 Heaps in O(log(n1) + log(n2)) time by a scheme similar to merge in Merge Sort.
        f.head = Merge(h1, h2);
//        cout<<"\nAfter Merging:\n";
//        f.showHeap();

        if(f.head){
            //We maintain 3 Pointers viz. prev, x, next.
            node* prev = NULL;
            node* x = f.head;
            node* next = x->sibling;

            while(next){
                //Case 1,2: degree of x != degree of next or degree of x = that of next = that of next of next
                //We just move the pointers ahead by 1 unit.
                if((x->degree!=next->degree) || (next->sibling && next->sibling->degree == next->degree)){
                    prev = x;
                    x=next;
                    next = next->sibling;
                }

                //Case 3: degree of x == degree of next !=degree of next of next
                else{
                    //Case 3.1 value of x <= value of next
                    //We make next as the child of x and update pointers accordingly.
                    if(x->val<=next->val){
                        x->sibling = next->sibling;
                        makeChild(next, x);
                    }
                    //Case 3.2 value of x> value of next
                    //We make x as the child of next
                    //In this case we need to update the sibling of prev as next
                    //if prev is NULL then we need to change the head of the Binomial Heap.
                    else{
                        if(prev){
                            prev->sibling = next;
                        }
                        else{
                            f.head = next;
                        }
                        makeChild(x,next);
                        x = next;
                    }
                    next = x->sibling;
                }
            }
        }
//        cout<<"\nAfter Uniting:\n";
//        f.showHeap();
        return f;
    }

    //Merges 2 Heaps Similar to merge of Merge Sort.
    //Since we just traverse the root list of the Heaps we just take O(log(n1)+log(n2)) time.
    static node* Merge(BHeap h1, BHeap h2){

//        cout<<"\nGot Heap 1 as\n";
//        h1.showHeap();
//        cout<<"\nGot Heap 2 as\n";
//        h2.showHeap();

        node* a = h1.head;
        node* b = h2.head;
        node* c = NULL;
        node* h = NULL; //Head of the Final Binomial Heap

        while(a && b){
            //Maintain 3 pointers 1 that points to instantaneous element of First Heap, 1 for 2nd Heap and one for merged Heap
            //We in each iteration find the node with lesser degree and append it to the merged heap.
            if(a->degree>b->degree){
                if(!c){
                    h = c = b;
                }
                else{
                    c->sibling = b;
                    c=c->sibling;
                }
                b=b->sibling;
            }
            else{
                if(!c){
                    h = c = a;
                }
                else{
                    c->sibling = a;
                    c=c->sibling;
                }
                a=a->sibling;
            }
        }

        //Copy the Remaining elements if any
        if(a){
            if(!c){
                h = c = a;
            }
            else
                c->sibling = a;
        }
        if(b){
            if(!c){
                h = c = b;
            }
            else
                c->sibling = b;
        }

        //returns pointer to the head of the merged heap.
        return h;
    }

    //Makes y as the child of z
    //Updates the Pointers accordingly
    static void makeChild(node* y, node* z){
        y->parent = z;
        y->sibling = z->leftMostChild;
        z->leftMostChild = y;
        z->degree = z->degree +1;
    }

    void insert(int x){
        insert(createNode(x));
    }

    //For Inserting we just make a Heap of size 1 and take its union with the original heap.
    //Union would take O(log(n)) time.
    void insert(node* x){
        BHeap h(x);
        head = Union(*this, h).head;
    }


    //Traverse through the root list and find the minimum
    //O(log(n)) time taken.
    int minimum(){
        if(head){
            node* min = head;
            node* p = head->sibling;

            while(p){
                if(p->val<min->val){
                    min = p;
                }
                p=p->sibling;
            }
            return min->val;
        }
        else{
            cout<<"\nERROR:: Cannot Find Min as No Element in the Heap";
            return -1;
        }
    }

    //For extract min we remove the binomial tree containing the least element and
    //We construct a Binomial Heap of the children of the root of Binomial Tree with containing Least Element
    //Then we take Union of the Original heap and the Heap Formed.
    //The Original Heap has O(log(n)) Elements
    //The Formed Heap contains O(log(n)) elements and is created in O(log(n)) time by just traversal and updating the pointers
    //Union takes O(log(n)) time
    //So Over all Time taken is O(log(n))
    int extractMin(){
        if(head){
            node* min = head;
            node* p = head;
            node* prev = NULL;
            node* prevofmin = NULL;

            //Traverse and Find Minimum
            while(p){
                if(p->val<min->val){
                    min = p;
                    prevofmin = prev;
                }
                prev=p;
                p=p->sibling;
            }

            //Remove the Tree having Minimum element.
            int ret = min->val;
            if(prevofmin){
                prevofmin->sibling = min->sibling;
            }
            else{
                head = min->sibling;
            }
//            cout<<"\nRemaining:\n";
//            showHeap();

            BHeap h;
            node* temp = min->leftMostChild;
            delete min;

            //Make a New Binomial Heap out of the Children of the Tree with minimum elements.
            if(temp){
                h.head = changePointers(temp->sibling, temp);
//                cout<<"\nTo be Added:\n";
//                h.showHeap();
                head = Union(*this, h).head;
            }

            return ret;
        }
        else{
            cout<<"\nERROR:: Cannot Extract Min as No Element in the Heap";
            return -1;
        }
    }

    //Recursively toggles the direction of the pointers of siblings in the root list of a binomial tree
    //This is done by a single traversal and thus takes O(log(n)) time.
    //Also we make parents of each node traversed as NULL as these elements would become the members of the root list.
    static node* changePointers(node* p, node* prev){
        if(p){
            prev->sibling=NULL;
            prev->parent = NULL;
            p->parent = NULL;

            //If p has a sibling then first change pointer of its siblings
            if(p->sibling){
                node* last = changePointers(p->sibling, p);
                //After changing the pointers of the Siblings change the pointers of p
                p->sibling = prev;
                return last;
            }
            else{
                //If p is the last node of the list then just change its sibling
                p->sibling = prev;
                return p;
            }
        }
        else{
            prev->parent = NULL;
            return prev;
        }
    }

    //The following 2 methods just implements what was given in the Assignment.
    void show(node* p, int depth){
        if(p->sibling){
            show(p->sibling, depth);
            cout<<"\n";
        }
        if(p->leftMostChild || !p->parent){
            printspace(6*depth+4);
            cout<<p->val;
            if(!p->leftMostChild)
                cout<<endl;
        }
        else{
            printspace(6);
            cout<<p->val<<endl;
        }
        if(p->leftMostChild){
            show(p->leftMostChild,depth+1);
        }

    }

    void showHeap(){
        cout<<"\nStructure of Binomial Heap rotated 90 deg ccw:\n";
        if(head)
            show(head,0);
        else
            cout<<"Empty Heap\n\n";
    }
};



int main()
{
    /** MAIN TEST
    *
    *   The Test given in the Assignment is Typed Below
    *   Uncomment following lines and comment the lines following the commented area to test them.
    */
//    BHeap h;
//    cout<<"Inserting 20 Elements:\n";
//    for(int i=1; i<=20; i++)
//       h.insert(i);
//    h.showHeap();
//
//    cout<<"Extracting 10 Elements with flag off:\n";
//    for(int i= 0; i<10; i++){
//       h.extractMin();
//    }
//    h.showHeap();
//
//    cout<<"Extracting 10 Elements with flag on:\n";
//    for(int i= 0; i<10; i++)
//       cout<<"Minimum Extracted:\t"<<h.extractMin()<<endl;
//    h.showHeap();
//    cout<<"\nDoing a Extract Min:\n";
//    h.extractMin();
//
//    cout<<"Inserting 20 Elements:\n";
//    for(int i=1; i<=20; i++)
//       h.insert(20-i+1);
//    h.showHeap();

    freopen("in.txt","r",stdin);


    /**
    *   Menu For Driving the Binomial Heap.
    *   To test with a File input just make the verbose flag as false
    *   Please Remove the Comments from the input file if any i.e. lines with #
    */

    char ch='\0';
    BHeap h;

    bool verbose = false;
    bool eminverbose = true;
    int x;
    while(true){
        if(verbose){
            cout<<"\nBINOMIAL HEAP - MAIN MENU";
            cout<<"\n(c) Make Binomial Heap";
            cout<<"\n(S) Show Heap";
            cout<<"\n(i) Insert Into Heap";
            cout<<"\n(d) Extract Minimum";
            cout<<"\n(+) Turn ON Print After Extract Min";
            cout<<"\n(-) Turn OFF Print After Extract Min";
            cout<<"\n(e) End";
            cout<<"\nChoice:\t";
        }
        if(cin>>ch){
            switch(ch){
                case 'c':
                    cout<<"\nHeap Created\n\n";
                    break;
                case 'S':
                    h.showHeap();
                    break;
                case 'i':
                    if(verbose){
                        cout<<"\nEnter Value to be Inserted:\t";
                    }
                    cin>>x;
                    h.insert(x);
                    break;
                case 'd':
                    x = h.extractMin();
                    if(eminverbose && x!=-1)
                        cout<<"\nMinumum Extracted:\t"<<x<<endl;
                    break;
                case '+':
                    cout<<"\nChanged Flag to True\n";
                    eminverbose = true;
                    break;
                case '-':
                    cout<<"\nChanged Flag to False\n";
                    eminverbose = false;
                    break;
                case 'e':
                    return 0;
                default:
                    cout<<"\nERROR:: Wrong Option\n";
                    break;
            }
        }
        else{
            break;
        }
    }

    return 0;
}
