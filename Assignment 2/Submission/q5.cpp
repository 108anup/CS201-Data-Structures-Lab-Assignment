/**
*
*   Assignment 2 - Linked List, Stack, Queues - Q5
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
            deleteLast();
        }
    }
};

bool check_for_cycle(LinkedList<int>& l){

    //If there is only 1 element and its next does not point to itself or only 2 elements where in the next of last is NULL
    //Then the List has no Cycle
    if(l.getFirst()->next!=NULL && l.getFirst()->next->next!=NULL){
        //Define 2 pointers which traverse with different velocities over the list
        node<int> *p1 = l.getFirst()->next;
        node<int> *p2 = l.getFirst()->next->next;

        //If there is a cycle then ( num_steps * 1 = num_steps * 2 ) % |length of cycle|
        //since num_steps increments by one each time so num_steps = |length of cycle| if cycle is present
        //we start num_steps when we arrive at the first node of the cycle.
        //so total work is proportional to num_steps + (n-|length of cycle|)
        //Therefore Algorithm runs in O(n) time.
        while(p2->next!=NULL && p2->next->next!=NULL && p1!=p2){
            //cout<<p1->data<<" "<<p2->data<<"\n";
            p1=p1->next;
            p2=p2->next->next;
        }

        if(p1==p2){
            return 1;
        }
        else{
            return 0;
        }
    }
    return 0;
}

int main(){

    LinkedList<int> l;
    int n;

    cout<<"Number of Elements to be entered into the Linked List:\t";
    cin>>n;

    cout<<"\nEnter the Elements:\n";
    for(int i= 0; i<n; i++){
        int x;
        cin>>x;
        l.insertAtEnd(x);
    }

    char response = 'n';
    cout<<"\nDo you want to join the last Element with some kth element? (y/n):\t";
    cin>>response;

    if(response =='Y' || response =='y'){
        int k;
        cout<<"\nEnter k such that the next of last element will point the the kth element \n(k should lie between 1 and n):\t";
        cin>>k;

        node<int>* p = l.getFirst();
        while(k>1){
            p=p->next;
            k--;
        }
        l.getLast()->next=p;
    }

    if(check_for_cycle(l)){
        cout<<"\nYes, Cycle is Present";
    }
    else{
        cout<<"\nCycle is not Present";
    }
    
    return 0;
}