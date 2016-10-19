/**
*
*   Assignment 2 - Linked List, Stack, Queues - Q4
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

//Generic Implementation of Linked List -> Dependency for Queue Class
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

//Generic Implementation of Queue Class -> depends on Linked List Class
template<class T>
class Queue{
    LinkedList<T> l;

public:

    void enQueue(T d){
        l.insertAtEnd(d);
    }

    T deQueue(){
        if(l.getFirst()!=NULL){
            T temp = l.getFirst()->data;
            l.deleteFirstNode();
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

    bool isEmpty(){
        return l.getFirst()==NULL;
    }

};


struct process{
    string processname;
    int startTime;
    int remainingTime; //Initially set to Total Execution time, as time is scheduled this variable is decremented till it becomes 0.
    vector<pair<int, int> > runningTime; //To Store the Starting Times and Ending Times of Each Process
                                        //As Assigned by the Scheduler
};

//See Which process arrived First - Used for sorting the Processes in accordance to Arrival Time.
bool compare_processes(process p1, process p2){
    return p1.startTime<p2.startTime;
}

//Finds the Running Times of Each Processes using the Round Robin Scheduling Scheme
//let E[i] be execution time of ith process then Algorithm takes O(sum(E[i]%q)) (sum over i from 0 to n-1) time.
void round_robin(process plist[], int n,int q){
    //Process Queue
    Queue<int> que;

    //The next Process to be checked if queue is empty 
    int i = 1;
    int processedTillTime = 0;//CPU Time upto which time allocation has been done

    que.enQueue(0); //First process to be processed
    while(i<n || !que.isEmpty()){ //break when all processes have been dealt with and process queue is empty

        bool needsAnotherRide = false; //Stores whether the process to be processed (Current Process) will require more time than the quanta
        int tbp; //Index of the Current Process

        if(que.isEmpty()){
            processedTillTime = plist[i].startTime; //If queue is empty this means that all processes that have had arrived on or before current Time
                                                    //have been processed and next processing will only be done when next process arrives.
        }
        else{

            tbp = que.deQueue(); //If queue is not empty then the frontmost process needs processing

            if(plist[tbp].remainingTime>q){ //process needs more than one quanta
                plist[tbp].remainingTime-=q;
                plist[tbp].runningTime.push_back(make_pair(processedTillTime,processedTillTime+q));
                needsAnotherRide = true; //Since process needs more than one quanta then we shall push it to the queue later in the loop
                processedTillTime +=q; //The time till which scheduling has been done is increased
            }
            else if(plist[tbp].remainingTime>0){
                int temp = processedTillTime+plist[tbp].remainingTime;
                plist[tbp].runningTime.push_back(make_pair(processedTillTime,temp));
                plist[tbp].remainingTime=0;
                processedTillTime = temp;
                //In this case the process does not need more than the quanta to complete the work so we don't need to add it to the queue again.
            }
        }

        //Check which all processes have arrived in the time we looked at frontmost process
        //and the time when it will have elapsed its scheduled time.
        while(i<n && plist[i].startTime<=processedTillTime){
            que.enQueue(i);
            i++;
        }

        //First the processes arrived are inserted into the queue 
        //then the process which needs more time to complete is inserted again to the queue (if required)
        if(needsAnotherRide)
            que.enQueue(tbp);
    }

}


int main(){

    //freopen("in.txt","r",stdin); //For Testing Purposes Only
    int n,q;
    cout<<"Enter the Number of Processes:\t";
    cin>>n;

    cout<<"Enter the Time Quantum:\t";
    cin>>q;
    process plist[n];

    cout<<"Enter the Processes separated by Newlines \nand THREE columns per process denoting ProcessName (w/o whitespaces), arrival time and ";
    cout<<"execution time respectively.\n\nSample Input:\nP0 0 250\nP1 50 170\nP2 130 75\n\nEnter:\n";

    //Inputting The Processes
    for(int i=0; i<n; i++){
        cin>>plist[i].processname>>plist[i].startTime>>plist[i].remainingTime;
    }

    sort(plist,plist+n,compare_processes); //This uses the sort function of the STL (Standard Template Library)
    //Since we have already implemented sorting in last Assignment, so I think it is appropraite to use the Library function in this Assignment.

    //Find the Running Times of Each of the Processes
    round_robin(plist,n,q);

    cout<<"\nThe Running Times of the various Processes are:\n";
    for(int i = 0; i<n; i++){
        cout<<plist[i].processname<<" ";
        for(int j = 0; j<plist[i].runningTime.size(); j++){
            cout<<"<"<<plist[i].runningTime[j].first<<","<<plist[i].runningTime[j].second<<"> ";
        }
        cout<<"\n";
    }
}