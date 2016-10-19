/**
*
*   Assignment 2 - Linked List, Stack, Queues - Q3
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
#include <vector>
#include <utility>
#include <algorithm>
#include <string.h>
#include <stdio.h>

using namespace std;

//Generic Node for the Data Structures. 
template<class T>
struct node{
    T data;
    node* next;
};

//Generic Implementation of Linked List -> Dependency for Stack Class
//Taking same implementation as done during Lab.
template<class T>
class LinkedList{

    node<T>* first;
    node<T>* last;

public:

    LinkedList(){
        first=last = NULL;
    }

    node<T>* createNode(T d){
        node<T>* p = new node<T>;
        p->data = d;
        p->next = NULL;
        return p;
    }

    node<T>* searchNode(T d){
        node<T>* p = first;
        while(p!=NULL){
            if(p->data == d)
                return p;
            p=p->next;
        }
        return NULL;
    }

    void insertNodeAfterValue(T d, T toinsert){
        node<T>* p = searchNode(d);
        if(p==NULL){
            cout<<"Element Not Found\n";
        }
        else{
            insertNodeAfter(p,toinsert);
        }
    }

    void insertNodeAfter(node<T>* p, T d){
        if(p==NULL){
            p = createNode(d);
            first = last = p;
        }
        else{
            node<T>* temp = p->next;
            p->next = createNode(d);
            p->next->next = temp;
            if(temp==NULL)
                last = p->next;
        }
    }

    void insertAtStart(T d){
        node<T>* p = createNode(d);
        p->next = first;
        first = p;

        if(first->next == NULL)
            last = first;
    }

    void insertAtEnd(T d){
        insertNodeAfter(last,d);
    }

    void deleteAfterValue(T d){
        node<T>* p = searchNode(d);
        if(p==NULL){
            cout<<"Not Found\n";
        }
        else{
            deleteAfter(p);
        }
    }

    void deleteAfter(node<T>* p){
        if(p==NULL || p->next ==NULL){
            cout<<"Underflow\n";
        }
        else{
            node<T>* temp = p->next;
            if(p->next==last)
                last=p;
            p->next = p->next->next;
            delete(temp);
        }
    }

    void deleteFirstNode(){
        if(first!=NULL){
            node<T>* temp = first;
            first = first->next;
            delete(temp);
            if(first ==NULL)
                last =NULL;
        }
        else{
            cout<<"Underflow\n";
        }
    }

    void deleteLast(){
        if(first ==NULL){
            cout<<"Underflow\n";
        }
        else if(last==first){
            delete(first);
            last = first = NULL;
        }
        else{
            node<T>* p = first;
            while(p->next!=last){
                p=p->next;
            }
            deleteAfter(p);
        }
    }

    node<T>* getFirst(){return first;}
    node<T>* getLast(){return last;}

    void show(){
        cout<<"Current Status:\t";
        node<T>* p = first;
        while(p!=NULL){
            cout<<p->data<<" ";
            p=p->next;
        }
        cout<<"\n";
    }

    ~LinkedList(){
        while(first!=NULL){
            deleteFirstNode();
        }
    }
};

//Generic Implementation of Stack Class -> depends on Linked List Class
template<class T>
class Stack{
    LinkedList<T> l;
    int size_stack;

public:

    Stack(){
        size_stack=0;
    }

    T push(T d){
        size_stack++;
        l.insertAtEnd(d);
        return d;
    }

    T pop(){
        if(l.getLast()!=NULL){
            size_stack--;
            T temp = l.getLast()->data;
            l.deleteLast();
            return temp;

        }
        else{
            cout<<"Underflow\n";
            return -1;
        }
    }

    void show(){
        l.show();
    }

    node<T>* getTop(){
        return l.getFirst();
    }

    bool isEmpty(){
        return l.getFirst()==NULL;
    }

    int getSize(){
        return size_stack;
    }
};

//O(n^2) Algorithm for computing s = span(x)
void span_naive(int x[], int s[], int n){

    memset(s,0,n*sizeof(int));

    for(int i=0; i<n; i++){ //n+1 times
        int j = i; // n times

        //Linearlly Check for the Rightmost element to the left of i which is greater than value at i.
        while(j>=0 && x[j]<=x[i]){ //atmost i+1 times per execution so total (n+1)*n/2
            s[i]++; //atmost i times so overall n*(n-1)/2
            j--; //atmost i times per execution so overall n*(n-1)/2
        }
    }
}

//O(n) Algorithm to compute s = span(x)
void span_stack(int x[], int s[], int n){

    memset(s,0,n*sizeof(int));
    Stack<int> *st = new Stack<int>;

    //define h(i) as the index of the rightmost element greater than the ith element to the left of i
    //after each execution of the loop the invariant is that top is 'i' (on which execution was done i.e. before incrementing)
    //and then h(i) is below i then h(h(i)) and so on.

    st->push(0);
    s[0]=1;

    for(int i=1; i<n; i++){ //n times

        //while the value of the topmost element of the stack is <= x[i] keep on popping
        //so we arrive at the point when an element greater than x[i] comes or stack becomes empty.
        while(!st->isEmpty() && x[st->getTop()->data]<=x[i]) //condition check atmost n (inside loop) + (n-1) (false loop condition) = 2n-1 times
            st->pop(); //Since each element is push exactly once so this line runs atmost n times overall

        //if stack is empty that means that value at i is larger than all the other elements before it and so s[i] is i+1
        //if stack has some element then the top element is the rightmost element to the left of i which has a value greater the the value at i.
        //and so s[i] will be i - its index.
        s[i] = st->isEmpty()?i+1:i-st->getTop()->data; //n-1 times

        //The current element becomes a candidate for being h(i+1) for i+1 so push into the stack.
        st->push(i); //n-1 times
    }
}

void printarray(int a[], int n){
    for(int i= 0; i<n; i++){
        cout<<a[i]<<" ";
    }
}
int main(){

    int n;
    cout<<"Enter the Length of the Array:\t";
    cin>>n;


    int a[n];
    int s[n];
    int ss[n];

    cout<<"\nEnter the Array:\t";
    for(int i=0; i<n; i++){

        cin>>a[i];
    }

    cout<<"\nThe Span Calculated using the Naive Algorithm is:\n";
    span_naive(a,s,n);
    printarray(s,n);

    cout<<"\nThe Span Calculated using the Optimized Algorithm (Using Stack) is:\n";
    span_stack(a,ss,n);
    printarray(ss,n);

}