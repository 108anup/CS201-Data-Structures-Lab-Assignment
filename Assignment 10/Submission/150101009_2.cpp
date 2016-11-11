/**
*
*   Assignment 10 - BST and Hashing Q2.
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
#include <list>
#include <vector>
#include <utility>

using namespace std;

//The Term of a Polynomial
struct poly{
    int deg;
    int coeff;
};

//This is the Hashtable Made during the Online Assignment
class hashtable{

    public:

    vector<poly> a;
    int (hashtable::*hashfunction)(int k, int i);
    int m;

    //The Constructor takes input the size of the table as well as the technique for resolving conflicts/hash function
    hashtable(int m, int hashfn=0){
        if(hashfn == 1){
            hashfunction = &hashtable::linear;
        }
        else if(hashfn == 2){
            hashfunction = &hashtable::quad;
        }
        else{
            hashfunction = &hashtable::doublehash;
        }
        this->m = m;
        a.resize(m);
        poly p = {-2,0};
        a.assign(m,p); //-2 initially and -1 for deleted value
    }

    pair<int,int> insert_into_table(poly p){
        bool flag = 0;
        int idx;
        int i;
        //Typically for uniform hashing and good hashfunction
        //This should run in about O(n/m) n = number of elements to be inserted and m is the size of hashtable/
        //in this case n = m so in this under appropriate circumstances the loop runs in O(1) time.
        //In the Worst case this loop can go on for O(m) time i.e. searching each location.
        for(i=0; i<m; i++){
            //Compute the appropriate Hash Function
            idx = (this->*hashfunction)(p.deg,i);
            //If the location is not used then insert here itself
            if(a[idx].deg==-1 || a[idx].deg==-2){
                a[idx] = p;
                flag = 1;
                break;
            }
            //If the location is used check if the degree is same
            //If yes add
            else if(a[idx].deg == p.deg){
                a[idx].coeff += p.coeff;
                flag = 1;
                break;
            }
        }

        //We are returning the index of the location where element is inserted and
        //also number of trials we took to insert the element.
        if(!flag){
            return make_pair(-1,-1);
        }
        else{
            return make_pair(idx,i);
        }
    }

    int delete_from_table(int k){
        int idx;
        int i;
        for(i=0; i<m; i++){
            //Compute Hash Function
            idx = (this->*hashfunction)(k,i);
            //Check if an element was present here before or has it been empty since birth
            if(a[idx].deg== -2){
                return -1;
            }
            //If something is there then check if degree matches and if it does then delete the node.
            else if(a[idx].deg == k){
                a[idx].deg = -1;
                a[idx].coeff = 0;
                return idx;
            }
        }
        //If not found till now implies not present.
        return -1;
    }

    //Primary Hash function
    int h(int k){
        return k%m;
    }

    //Quadratic Probing
    int quad(int k, int i){
        int c1 = 1;
        int c2 = 3;

        return (h(k) + c1*i + c2*i*i)%m;
    }

    //Linear Probing
    int linear(int k, int i){
        return (h(k) + i)%m;
    }

    //Secondary Hash Function
    int h2(int k){
        return 1 + k%(m-1);
    }

    //Double Hashing
    int doublehash(int k, int i){
        return (h(k) + i*h2(k))%m;
    }
};

int main()
{
    list<poly> a;
    list<poly> b;

    int m,n;
    cout<<"Enter the Number of Terms of the First Polynomial:\t";
    cin>>n;
    cout<<"Enter the Terms in the form of coefficient <space> degree:\n";
    int c,d;
    for(int i= 0; i<n; i++){
        cin>>c>>d;
        poly p = {d,c};
        a.push_back(p);
    }
    cout<<"Enter the Number of Terms of the Second Polynomial:\t";
    cin>>m;
    cout<<"Enter the Terms in the form of coefficient <space> degree:\n";
    for(int i= 0; i<m; i++){
        cin>>c>>d;
        poly p = {d,c};
        b.push_back(p);
    }

    hashtable h(m*n);

    //Term wise product in O(m*n) time if hashing is uniform, worst case O(n*n*m*m) but very less likely.
    for(list<poly>::iterator i = a.begin(); i!=a.end(); i++){
        for(list<poly>::iterator j = b.begin(); j!=b.end(); j++){
            poly pdt = {(*i).deg + (*j).deg, (*i).coeff * (*j).coeff};
            h.insert_into_table(pdt);
        }
    }
    cout<<"\nThe Product is:\n";
    for(int i= 0; i<m*n; i++){
    	if(h.a[i].coeff !=0 && h.a[i].deg>=0){
	        cout<<showpos<<h.a[i].coeff;
	        cout<<"x^";
	        cout<<noshowpos<<h.a[i].deg<<" ";
    	}
    }


    return 0;
}
