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
#include <iostream>
#include <vector>

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

class Set{

    int n;

    public:

    vector<node*> dict;

    Set(int n){
        this->n = n;
        dict.resize(SIZE);
        dict.assign(SIZE,NULL);
    }

    void union_set(int x, int y){
        if(!dict[x] || !dict[y])
            cout<<"\nInvalid Parameters";
        else
            union_set(dict[x],dict[y]);
    }

    node* find_set(int x){
        if(!dict[x]){
            cout<<"\nInvalid Parameters";
            return NULL;
        }
        return find_set(dict[x]);
    }

    node* find_set(node* p){
        if(p->rep == p){
            return p;
        }
        else return p->rep = find_set(p->rep);
    }

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

	            g->number = max(g->number, l->number);

	            if(g->number != l->number){

		            node* new_set = g;
		            node* first_set = g->number<l->number?g:l;
		            node* second_set = g->number>l->number?g:l;

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

void getSeq(int n, int m, Set S, int extracted[]){
	for(int i= 1; i<=n; i++){
        cout<<"\n"<<i<<":\n";
        S.show();
        cout<<"\n\n";

		node* p = S.find_set(i);
		int j= p->number;
		if(j<m){
			extracted[j] = i;
			S.union_set(p,p->next);
		}
	}
}

int getnextInt(){
	int x;
	cin>>x;
	// char comma;

	if(cin.good()){
		// cin>>comma;
		return x;
	}
	else{
		cin.clear();
		return -1;
	}
}

int main()
{

    freopen("in.txt","r",stdin);

    int n;
    cout<<"Enter the Number of Elements:\t";
    cin>>n;
    Set S(n);

    int nums_inputted = 0;
    int setnum = 0;
    node* prev_set = NULL;
    int prev_elt = -1;
    int m;

//    while(nums_inputted<n){
//    	int x = 0;
//    	if( (x = getnextInt()) == -1){
//    		char e;
//    		cin>>e;
//    		// char comma;
//    		// cin>>comma;
//
//    		setnum++;
//    		if(prev_elt==-1){
//                node* p = S.make_set(-1); //NULL SET
//                p->number = setnum;
//                p->prev = prev_set;
//                if(prev_set)
//                    prev_set->next=p;
//                prev_set=p;
//                prev_elt=-1;
//    		}
//    		else
//                prev_elt = -1;
//    	}
//
//    	else{
//    		nums_inputted++;
//
//    		node* p = S.make_set(x);
//    		p->number = setnum;
//    		p->prev = prev_set;
//
//    		if(prev_elt == -1){
//                if(prev_set)
//                    prev_set->next = p;
//    			prev_set = p;
//    			prev_elt = x;
//    		}
//    		else{
//    			S.union_set(prev_elt,x);
//    		}
//    	}
//    }

    setnum = 0;
    prev_set = S.make_set(-1);
    prev_set->number = setnum;
    prev_elt = -1;
    prev_set->prev = NULL;
    prev_set->next=NULL;

    while(nums_inputted<n){
    	int x = 0;
    	if( (x = getnextInt()) == -1){
    		char e;
    		cin>>e;
    		// char comma;
    		// cin>>comma;

    		setnum++;
            node* p = S.make_set(-1); //NULL SET
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

    for(int i= 0; i<m; i++){
    	cout<<extracted[i]<<" ";
    }


    return 0;
}
