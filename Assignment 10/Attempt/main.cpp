#include <iostream>
#include <vector>

int m = 11;


    int h(int k){
        return k%m;
    }

    int quad(int k, int i){
        int c1 = 1;
        int c2 = 3;

        return (h(k) + c1*i + c2*i*i)%m;
    }

    int linear(int k, int i){
        return (h(k) + i)%m;
    }

    int h2(int k){
        return 1 + k%(m-1);
    }

    int doublehash(int k, int i){
        return (h(k) + i*h2(k))%m;
    }


using namespace std;

class hashtable{

    vector<int> a;
    int (*hashfunction)(int k, int i);

    public:

    hashtable(int hashfn){
        if(hashfn == 1){
            hashfunction = &linear;
        }
        else if(hashfn == 2){
            hashfunction = &quad;
        }
        else{
            hashfunction = &doublehash;
        }

        a.resize(m);
        a.assign(m,-2); //-2 initially and -1 for deleted value
    }

    pair<int,int> insert_into_table(int k){
        bool flag = 0;
        int idx;
        int i;
        for(i=0; i<m; i++){
            idx = hashfunction(k,i);
            if(a[idx]==-1 || a[idx]==-2){
                a[idx] = k;
                flag = 1;
                break;
            }
        }

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
            idx = hashfunction(k,i);
            if(a[idx]== -2){
                return -1;
            }
            else if(a[idx] == k){
                a[idx] = -1;
                return idx;
            }
        }
        return -1;
    }
};

int main()
{
    m = 11;

//    int n;
//    cout<<"Enter the value of m:\t";
//    cin>>m;
//    cout<<"\nEnter number of Elements to enter into the hash table:\t";
//    cin>>n;
//    cout<<"Enter the Elements:\n";
//
//    hashtable lin(1);
//    hashtable quadratic(2);
//    hashtable doub(3);
//
//    int lincoll = 0;
//    int quadcoll = 0;
//    int doublecoll = 0;
//
//    for(int i=0; i<n; i++){
//        int x;
//        cout<<"\n";
//        cin>>x;
//        pair<int,int> recv = lin.insert_into_table(x);
//        if(recv.first!=-1){
//            cout<<"\nLinear Probing: (idx, collisions) = ("<<recv.first<<", "<<recv.second<<")\n";
//            lincoll +=recv.second;
//        }
//        else{
//            cout<<"\nCould not insert into Linear Hash Table\n";
//        }
//
//        recv = quadratic.insert_into_table(x);
//        if(recv.first!=-1){
//            cout<<"\nQuadratic Hashing: (idx, collisions) = ("<<recv.first<<", "<<recv.second<<")\n";
//            quadcoll +=recv.second;
//        }
//        else{
//            cout<<"\nCould not insert into Quadratic Hash Table\n";
//        }
//
//        recv = doub.insert_into_table(x);
//        if(recv.first!=-1){
//            cout<<"\nDouble Hashing: (idx, collisions) = ("<<recv.first<<", "<<recv.second<<")\n";
//            doublecoll +=recv.second;
//        }
//        else{
//            cout<<"\nCould not insert into Double Hashing Hash Table\n";
//        }
//    }
//
//    cout<<"\nTotal Collisions (linear, quadratic, double):\t("<<lincoll<<", "<<quadcoll<<", "<<doublecoll<<")\n";
//
//    int t;
//    cout<<"\nEnter Element to delete:\t";
//    cin>>t;
//
//    int r = lin.delete_from_table(t);
//    if(r!=-1){
//        cout<<"\nLinear Probing: Deleted from index:\t"<<r<<"\n";
//    }
//    else{
//        cout<<"\nLinear Probing: Element not Found\n";
//    }
//    r = quadratic.delete_from_table(t);
//    if(r!=-1){
//        cout<<"\nLinear Probing: Deleted from index:\t"<<r<<"\n";
//    }
//    else{
//        cout<<"\nLinear Probing: Element not Found\n";
//    }
//    r = doub.delete_from_table(t);
//    if(r!=-1){
//        cout<<"\nLinear Probing: Deleted from index:\t"<<r<<"\n";
//    }
//    else{
//        cout<<"\nLinear Probing: Element not Found\n";
//    }

    for(int i= 0; i<m; i++){
        cout<<quad(8,i)<<"\t";
    }
    cout<<"\n";
    for(int i= 0; i<m; i++){
        cout<<linear(8,i)<<"\t";
    }
    cout<<"\n";
    for(int i= 0; i<m; i++){
        cout<<doublehash(8,i)<<"\t";
    }
    return 0;
}
