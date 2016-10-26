#include <iostream>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;

class Heap{

    vector<int> h;
    int heapsize;

    public:

    Heap(){
        heapsize=0;
    }
    Heap(vector<int> in){
        h = in;
        heapsize = h.size();
        BuildHeap();
    }

    int left(int i){
        return 2*i+1;
    }

    int right(int i){
        return 2*i+2;
    }

    int parent(int i){
        return (i-1)/2;
    }

    void minHeapify(int root){
        int least = root;
        int l = left(root);
        int r = right(root);
        int s = heapsize;

        if(l<s && h[l]<h[least]){
            least = l;
        }
        if(r<s && h[r]<h[least]){
            least = r;
        }

        if(least!=root){
            int temp = h[root];
            h[root] = h[least];
            h[least] = temp;
            minHeapify(least);
        }
    }

    void BuildHeap(){
        int parent_last = parent(heapsize-1);
        for(int i= parent_last; i>=0; i--){
            minHeapify(i);
        }
    }

    int extractMin(){
        if(h.size()){
            int ret = h[0];
            h[0] = h[heapsize-1];
            h[heapsize-1] = ret;
            heapsize--;
            h.resize(heapsize);
            minHeapify(0);
            return ret;
        }

    }

    void insert_heap(int x){
        heapsize++;
        h.push_back(INT_MAX);

        decreaseKey(heapsize-1,x);
    }

    void decreaseKey(int loc, int val){
        if(h[loc]<val){
            cout<<"\nNON CONFORMANT INPUT\n";
        }

        h[loc] = val;
        if(h[loc]<h[parent(loc)]){
            h[loc] = h[parent(loc)];
            decreaseKey(parent(loc),val);
        }
    }
};

int main()
{
    fstream fin;
    fin.open("test.dat.txt");
//    fin.open("in.txt");

    int n;
    fin>>n;

    vector<int> a;

    Heap hi;

    for(int i= 0; i<n; i++){
        int x;
        fin>>x;
        a.push_back(x);
        hi.insert_heap(x);
    }

    Heap hb(a);

    fin.close();

    int k;
    cout<<"Taken Input from the File\n";
    cout<<"Enter the value of k, program will give the k least salaries:\t";
    cin>>k;

    cout<<"\nOne at a Time Insertion Stratergy:\n";
    for(int i = 0; i<k; i++){
        cout<<hi.extractMin()<<" ";
    }

    cout<<"\n\nBuildHeap Bottom Up Stratergy:\n";
    for(int i = 0; i<k; i++){
        cout<<hb.extractMin()<<" ";
    }


//    for(int i= 1; i<=4; i++){
//        cout<<5-i<<"\n";
//        a.push_back(5-i);
//    }
//    Heap h(a);
//    cout<<h.extractMin();
//    cout<<h.extractMin();
//    cout<<h.extractMin();
//    cout<<h.extractMin();
//    h.insert_heap(5);
//    h.insert_heap(1);
//    cout<<h.extractMin();
//    cout<<h.extractMin();

    return 0;
}
