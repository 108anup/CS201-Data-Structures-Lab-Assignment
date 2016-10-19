#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int mainmenu();

template<class T>
struct node{
    T data;
    node* next;
};

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
            deleteLast();
        }
    }
};

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
            return NULL;
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
            return NULL;
        }
    }

    void show(){
        l.show();
    }

    bool isEmpty(){
        return l.getFirst()==NULL;
    }

};

//O(n^2) Algorithm for computing s = span(x)
void span_naive(int x[], int s[], int n){

    memset(s,0,n*sizeof(int));

    for(int i=0; i<n; i++){ //n+1 times
        int j = i; // n times
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

    //define h(i) as the index of the rightmost element greater than the ith element
    //after each execution of the loop the invariant is that top is 'i' (on which execution was done i.e. before incrementing)
    //and then h(i) is below i then h(h(i)) and so on.

    st->push(0);
    s[0]=1;

    for(int i=1; i<n; i++){ //n times

        while(!st->isEmpty() && x[st->getTop()->data]<=x[i]) //condition check atmost n (inside loop) + (n-1) (false loop condition) = 2n-1 times
            st->pop(); //Since each element is push exactly once so this line runs atmost n times overall

        s[i] = st->isEmpty()?i+1:i-st->getTop()->data; //n-1 times

        st->push(i); //n-1 times
    }
}

struct process{
    string processname;
    int startTime;
    int remainingTime;
    vector<pair<int, int> > runningTime;
};

bool compare_processes(process p1, process p2){
    return p1.startTime<p2.startTime;
}

void round_robin(process plist[], int n,int q){
    Queue<int> que;

    int i = 1;
    int processedTillTime = 0;

    que.enQueue(0);
    while(i<n || !que.isEmpty()){

        bool needsAnotherRide = false;
        int tbp;

        if(que.isEmpty()){
            processedTillTime = plist[i].startTime;
        }
        else{

            tbp = que.deQueue();

            if(plist[tbp].remainingTime>q){
                plist[tbp].remainingTime-=q;
                plist[tbp].runningTime.push_back(make_pair(processedTillTime,processedTillTime+q));
                needsAnotherRide = true;
                processedTillTime +=q;
            }
            else if(plist[tbp].remainingTime>0){
                int temp = processedTillTime+plist[tbp].remainingTime;
                plist[tbp].runningTime.push_back(make_pair(processedTillTime,temp));
                plist[tbp].remainingTime=0;
                processedTillTime = temp;
            }
        }

        while(i<n && plist[i].startTime<=processedTillTime){
            que.enQueue(i);
            i++;
        }

        if(needsAnotherRide)
            que.enQueue(tbp);
    }

}

void check_round_robin(){
    freopen("in.txt","r",stdin);
    int n,q;
    cout<<"Enter the Number of Processes:\t";
    cin>>n;

    cout<<"Enter the Time Quantum:\t";
    cin>>q;
    process plist[n];

    cout<<"Enter the Processes separated by Newlines \nand THREE columns per process denoting ProcessName (w/o whitespaces), arrival time and ";
    cout<<"execution time respectively, Sorted By Arrival Time.\n\nSample Input:\nP0 0 250\nP1 50 170\nP2 130 75\n\nEnter:\n";

    for(int i=0; i<n; i++){
        cin>>plist[i].processname>>plist[i].startTime>>plist[i].remainingTime;
    }

    sort(plist,plist+n,compare_processes);

    round_robin(plist,n,q);

    cout<<"\nNote: Numbering of processes is in accordance with arrivalTime\n";
    for(int i = 0; i<n; i++){
        cout<<plist[i].processname<<" ";
        for(int j = 0; j<plist[i].runningTime.size(); j++){
            cout<<"<"<<plist[i].runningTime[j].first<<","<<plist[i].runningTime[j].second<<"> ";
        }
        cout<<"\n";
    }
}

int llmenu(LinkedList<int> l){
    int choice;

    cout<<"LINKED LIST MENU\n\n";
    cout<<"1. Insert Node After a Value\n";
    cout<<"2. Insert Node At Start\n";
    cout<<"3. Insert Node At End\n";
    cout<<"4. Delete Node After a Value\n";
    cout<<"5. Delete First Node\n";
    cout<<"6. Delete Last Node\n";
    cout<<"7. Return to Main Menu\n";
    cout<<"All Others. End\n";
    cout<<"Enter Choice:\t";
    cin>>choice;
    cout<<"\n";

    int value,value2;

    switch(choice){
        case 1:
            cout<<"\nEnter Value after which node is to be Inserted:\t";
            cin>>value;
            cout<<"\nEnter Value to be Inserted:\t";
            cin>>value2;
            l.insertNodeAfterValue(value,value2);
            l.show();
            break;
        case 2:
            cout<<"\nEnter Value to be Inserted:\t";
            cin>>value;
            l.insertAtStart(value);
            l.show();
            break;
        case 3:
            cout<<"\nEnter Value to be Inserted:\t";
            cin>>value;
            l.insertAtEnd(value);
            l.show();
            break;
        case 4:
            cout<<"\nEnter Value of data for Node whose child will be deleted:\t";
            cin>>value;
            l.deleteAfterValue(value);
            l.show();
            break;
        case 5:
            l.deleteFirstNode();
            l.show();
            break;
        case 6:
            l.deleteLast();
            l.show();
            break;
        case 7: return mainmenu();break;
        default: return 0;break;
    }

    return llmenu(l);
}

int smenu(Stack<int> s){
    int choice;

    cout<<"STACK MENU\n\n";
    cout<<"1. Push\n";
    cout<<"2. Pop\n";
    cout<<"7. Return to Main Menu\n";
    cout<<"All Others. End\n";
    cout<<"Enter Choice:\t";
    cin>>choice;
    cout<<"\n";

    switch(choice){
        case 1:
            int value2;
            cout<<"\nEnter Value to be Inserted:\t";
            cin>>value2;
            s.push(value2);
            s.show();
            break;
        case 2:
            cout<<s.pop()<<" - Popped Element\n";
            s.show();
            break;
        case 7: return mainmenu();break;
        default: return 0;break;
    }

    return smenu(s);
}

int qmenu(Queue<int> q){
    int choice;

    cout<<"QUEUE MENU\n\n";
    cout<<"1. Insert\n";
    cout<<"2. Delete\n";
    cout<<"7. Return to Main Menu\n";
    cout<<"All Others. End\n";
    cout<<"Enter Choice:\t";
    cin>>choice;
    cout<<"\n";

    switch(choice){
        case 1:
            int value2;
            cout<<"\nEnter Value to be Inserted:\t";
            cin>>value2;
            q.enQueue(value2);
            q.show();
            break;
        case 2:
            cout<<q.deQueue()<<" - Deleted Element\n";
            q.show();
            break;
        case 7: return mainmenu();break;
        default: return 0;break;
    }

    return qmenu(q);
}

int mainmenu(){
    int choice;

    cout<<"MAIN MENU\n\n";
    cout<<"1. LinkedList\n";
    cout<<"2. Stack\n";
    cout<<"3. Queue\n";
    cout<<"All Others. End\n";
    cout<<"Enter Choice:\t";
    cin>>choice;
    cout<<"\n";
    LinkedList<int>l;
    Stack<int>s;
    Queue<int>q;

    switch(choice){
        case 1:
            llmenu(l);
            break;
        case 2:
            smenu(s);
            break;
        case 3:
            qmenu(q);
            break;
        default: return 0;break;
    }
}

void check(){
    LinkedList<int> a;

    a.insertAtStart(2);
    a.show();
    a.insertNodeAfter(a.getFirst(),12);
    a.show();
    a.insertNodeAfter(a.getFirst(),13);
    a.show();
    a.insertAtStart(3);
    a.show();
    a.insertAtEnd(4);
    a.show();
    a.deleteAfter(a.getFirst());
    a.show();
    a.deleteFirstNode();
    a.show();
    a.deleteLast();
    a.show();
    a.insertAtEnd(9);
    a.show();
    a.insertNodeAfterValue(12,1);
    a.show();
    a.deleteAfterValue(12);
    a.show();
    a.deleteLast();
    a.show();
    a.deleteLast();
    a.show();
    a.deleteLast();
    a.show();
    a.deleteLast();
    a.show();

    cout<<endl<<endl;

    Stack<int> s;

    s.push(2);
    s.show();
    s.push(3);
    s.show();
    cout<<s.pop()<<" - Popped Element\n";
    s.show();
    s.push(4);
    s.show();
    cout<<s.pop()<<" - Popped Element\n";
    s.show();
    cout<<s.pop()<<" - Popped Element\n";
    s.show();
    cout<<s.pop()<<" - Popped Element\n";
    s.show();

    cout<<endl<<endl;

    Queue<int> q;

    q.enQueue(3);
    q.show();
    q.enQueue(7);
    q.show();
    q.enQueue(9);
    q.show();
    q.enQueue(10);
    q.show();
    q.enQueue(4);
    q.show();
    cout<<q.deQueue()<<" - Deleted Element\n";
    q.show();
    cout<<q.deQueue()<<" - Deleted Element\n";
    q.show();
    cout<<q.deQueue()<<" - Deleted Element\n";
    q.show();
    cout<<q.deQueue()<<" - Deleted Element\n";
    q.show();
    cout<<q.deQueue()<<" - Deleted Element\n";
    q.show();
    cout<<q.deQueue()<<" - Deleted Element\n";
    q.show();
}

void printarray(int a[], int n){
    for(int i= 0; i<n; i++){
        cout<<a[i]<<" ";
    }
}

void check_span(){

    int a[6] = {10, 4, 5, 90, 120, 80};
    int s[6];

    span_stack(a,s,6);
}

int main()
{
    LinkedList<int> l;
    l.insertAtEnd(1);
    l.insertAtEnd(2);
    l.insertAtEnd(3);
    l.insertAtEnd(4);
    l.insertAtEnd(5);
    l.insertAtEnd(1);
    l.getLast()->next=l.getFirst()->next;

    if(l.getFirst()->next!=NULL && l.getFirst()->next->next!=NULL){
        node<int> *p1 = l.getFirst()->next;
        node<int> *p2 = l.getFirst()->next->next;

        while(p2->next!=NULL && p2->next->next!=NULL && p1!=p2){
            cout<<p1->data<<" "<<p2->data<<"\n";
            p1=p1->next;
            p2=p2->next->next;
        }

        if(p1==p2){
            cout<<"\nYes, Cycle is Present";
        }
        else{
            cout<<"\nCycle is not Present";
        }
    }

    return 0;

}



