#include <iostream>
#include <climits>
#include <math.h>

using namespace std;

#define max(a,b) (a)>(b)?(a):(b)
#define SIZE int(1e5+5)

class WT{

    int arr[SIZE];
    int k;
    int n;

public:

    WT(int m, int a[]){
        k=m;
        n = pow(2,ceil(log2(k)));
        for(int i= n-1; i-n+1<=k-1; i++){
            arr[i] = a[i-n+1];
        }
    }

    void buildWinnerTree(){
        for(int i= n-2; i>=0; i--){
            int c1 = 2*i+1;
            int c2 = 2*i+2;
            if(c2<=n-2+k){
                arr[i] = max(arr[c1],arr[c2]);
            }
            else if(c1<=n-2+k)
                arr[i] = max(arr[c1],0);
            else
                arr[i] = 0;

        }
    }

    void showArray(){
        for(int i= 0; i<=n-2+k; i++){
            cout<<arr[i]<<" ";
        }
    }

    int parent(int i){
        return (i-1)/2;
    }

    int nextMax(){
        int temp = arr[0];
        updateTop(0);
        return temp;
    }
    //Recursively find the winner of the sub trees and update the root accordinlgluy
    int updateTop(int root){
        int temp = arr[root];
        int c1 = 2*root+1;
        int c2 = 2*root+2;

        if(c2<2*n-1){
            if(arr[c2]==temp){
                int sub_max = updateTop(c2);
                arr[root] = max(arr[c1],sub_max);
            }
            else{
                int sub_max = updateTop(c1);
                arr[root] = max(arr[c2],sub_max);
            }
            return arr[root];
        }
        else{
            arr[root] = 0;
            if(root%2==0)
                return arr[root-1];
            else
                return arr[root];
        }
    }


};

int main()
{
    int k;
    cout<<"Enter the Number of Elements:\t";
    cin>>k;

    int a[k];
    cout<<"\nEnter the Elements:\n";
    for(int i= 0; i<k; i++){
        cin>>a[i];
    }

    WT my_tree(k,a);
    my_tree.buildWinnerTree();

    cout<<"\nThe Tree Built is:\n";

    my_tree.showArray();
    cout<<"\n";
    cout<<my_tree.nextMax();
    cout<<"\n";
    my_tree.showArray();

    return 0;
}
