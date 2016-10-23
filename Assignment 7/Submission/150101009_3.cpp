/**
*
*   Assignment 7 - DisjointSets Q2. Offline Minimum
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

//NOTE:: The Explaination of the Algorithm is given in the main function, getSeq function and union function in this mentioned order

#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

const int SIZE = 1e5;

struct node{
    int data;
    node* rep; //parent
    int s; //rank

    int number;
    node* next;
    node* prev;

    node(){
    	number = s = data = -1;
    	rep = prev = next = NULL;
    }
};

//Disjoint set Data Structure
//For n make set operations and m make set, union and find operations
//The Overall Complexity is O(m*alpha(n)) where alpha is the Inverse Ackerman Function (extermely slow growing).
//Which is roughly O(m) as alpha(n) <=4 for all practical purposes.
//The Explaination for the overall Complexity with both Union by Rank and Path Compression heuristic is out of scope of discussion.
//If we only follow Union by Rank Heuristic Time Complexity would be O(m*log(n)) as find set each operation would atmost O(log(n)) time. 
class Set{

    int n;

    public:

    //Dictionary that maps Data Elements to the node pointer.
    vector<node*> dict;

    Set(int n){
        this->n = n;
        dict.resize(SIZE);
    }

    //Overloaded function for Union that takes data elts as imput
    //O(log(n)) per single iteration worst case.
    void union_set(int x, int y){
        if(!dict[x] || !dict[y])
            cout<<"\nInvalid Parameters";
        else
            union_set(dict[x],dict[y]);
    }

    //Overloaded function for Find set that takes data elts as imput
    //O(log(n)) Per single iteration worst case.
    node* find_set(int x){
        if(!dict[x]){
            cout<<"\nInvalid Parameters";
            return NULL;
        }
        return find_set(dict[x]);
    }

    //NOTE::
    //The Rank for any Node could be atmost log(n).
    //Since at any instant except for the last level for each tree in the forest, the levels have atleast 2^i elements where i is the level number
    //And so for rank = k there would be alteast 2^(k-1)-1 elements in that set (where rank = 1 for Singleton set) 
    //So if n are the total elements the universal set would have log(n+1)+1 elements = O(log(n))

    //Since each set can have rank atmost O(log(n)) there fore each single iteration takes atmost O(log(n)) time.
    node* find_set(node* p){
        if(p->rep == p){
            return p;
        }
        else return p->rep = find_set(p->rep);
    }

    //Since Apart from the Find Set operations the other operations take constant time so O(log(n)) per iteration.
    void union_set(node* x, node* y){
    	if(x && y){
	        node* l = find_set(y); //lesser rank
	        node* g = find_set(x); //greater rank

	        if(g!=l){
	            if(g->s < l->s){
	                node* temp = g;
	                g = l;
	                l = temp;
	            }
	            else if(l->s==g->s){
	                g->s += 1;
	            }
	            l->rep = g;

                //In this question we would only be merging one set with a set whose number is just greater than the former's number
                //apart from the preprocessing step.
                //when we merge 2 sets g and l with number of g> that of l then we want the resultant set to have number as same as number of g
                //also the next of this set would be next of g and prev would be prev of l
                //also in doing this we would have to update the next of prev of l and prev of next of g
	            if(g->number != l->number){

		            node* new_set = g;
		            node* first_set = g->number<l->number?g:l;
		            node* second_set = g->number>l->number?g:l;

                    g->number = max(g->number, l->number);

		            new_set->prev = first_set->prev;
		            if(first_set->prev){
		            	first_set->prev->next = new_set;
		            }

                    new_set->next = second_set->next;
                    if(second_set->next){
                        second_set->next->prev = new_set;
		            }
	        	}
	        }
    	}
    }

    //Constant time for making a set.
    node* make_set(int x){
        node* p = new node;
        p->data = x;
        p->rep = p;
        p->s = 1;

        if(x>=0 && x<SIZE)
            dict[x] = p;
        return p;
    }

    void show(){
        cout<<"\nNode, Representative\n";
        for(int i= 0; i<SIZE -1; i++){
            node* r = dict[i];
            if(r){
                node* p =find_set(r);
                cout<<r->data<<",\t"<<p->data<<"\t"<<p->number<<"\t"<<p->next<<endl;
            }
        }
    }
};

//**
//This is the most significant Routine for this Question.
//In the preprocessing in the main function we obtain disjoint sets such that elements between 2 consecutive E's are in the same set.
//If the set number is i then that element can only be extracted on or after the ith position
//We start from the smallest Element so for any element 'e' then we find out when can it be extracted let us say it is i
//We set the ith extracted element as that element 'e' and then all the other elements in its set cannot be extracted in the ith position
//So we put all of them in the next set whose extracted element has not been set.
//**

//We Use Total of n make set operations in preprocessing
//n find set ops and atmost n union ops resulting in total time of O(3n*alpha(n)) = O(n*alpha(n)) which is roughly O(n) for all practical purposes
//As alpha(n) <=4 for all practical purposes.
void getSeq(int n, int m, Set S, int extracted[]){
	for(int i= 1; i<=n; i++){
//        cout<<"\n"<<i<<":\n";
//        S.show();
//        cout<<"\n"<<endl;

		node* p = S.find_set(i);
		int j= p->number;
		if(j<m){
			extracted[j] = i;
			S.union_set(p,p->next);
		}
	}
}

//This funciton returns the next positive integer from the input buffer and return -1 if such a value does not exist
int getnextInt(){
	int x;
	cin>>x;

	if(cin.good()){
		return x;
	}
	else{
		cin.clear();
		return -1;
	}
}

int main()
{

    //freopen("in.txt","r",stdin);

    int n;
    cout<<"Enter the Number of Elements:\t";
    cin>>n;
    Set S(n);
    cout<<"Enter the Input String:\n**(Use Space as delimiter instead of Commas.)\n (Only use numbers and letter E in the input string)\n";
    cout<<"Sample Input: 4 8 E 3 E 9 2 6 E E E 1 7 E 5\n";

    int nums_inputted = 0;
    int setnum = 0;
    node* prev_set = NULL;
    int prev_elt;
    int m;

    //Preprocessing Step:   
    //We try to make Elements between 2 E's into a disjoint set 
    //Each disjoint set has a number and stores pointers to prev and next set.
    //We start with a null set each time we encounter integer we add it to the set
    //Whenever we encounter a E we mmake a new null set and increment its number

    //CREATE NULL SET
    setnum = 0;
    prev_set = S.make_set(-1);
    prev_set->number = setnum;
    prev_elt = -1;
    prev_set->prev = NULL;
    prev_set->next=NULL;

    //We keep on reading from the input buffer till we get n positive ints as that is specified in the question that there are exactly n insertions.
    while(nums_inputted<n){
    	int x = 0;
    	if( (x = getnextInt()) == -1){
    		char e;
    		cin>>e;

    		setnum++;
            node* p = S.make_set(-1);
            p->number = setnum;
            p->prev = prev_set;
            prev_set->next=p;
            prev_set=p;
            prev_elt=-1;
    	}

    	else{
    		nums_inputted++;

    		node* p = S.make_set(x);
    		p->number = setnum;
    		p->prev = prev_set;
            S.union_set(prev_set,p);
    	}
    }


    m = setnum;
    int extracted[m];

    getSeq(n,m,S,extracted);

    cout<<"\nThe Extraction Sequence is:\t";
    for(int i= 0; i<m; i++){
    	cout<<extracted[i]<<" ";
    }


    return 0;
}
