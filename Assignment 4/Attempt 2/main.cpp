#include <iostream>

using namespace std;

#define max(a,b) (a)>(b)?(a):(b)

const int SIZE = 1e5+5;

class WT{

    int a[SIZE];
    int n;

    public:

    WT(int arr[], int s){
        n = s;
        for(int i=n-1; i<2*n-1; i++){
            a[i] = arr[i-n+1];
        }
    }

    void buildTree(){
        for(int i = n-2; i>=0; i--){
            int c1 = 2*i+1;
            int c2 = 2*i+2;

            a[i] = max(a[c1],a[c2]);
        }
    }

    int getWinner(){
        return a[0];
    }

    int removeWinner(int r){
        int c1 = 2*r+1, c2 = 2*r+2;

        if(c2<2*n-1){
            if(a[c1]==a[r]){
                int x = removeWinner(c1);
                a[r] = max(a[c2],x);
            }
            else{
                int x = removeWinner(c2);
                a[r] = max(a[c1],x);
            }
            return a[r];
        }
        else{
            a[r] = 0;
            return 0;
        }
    }

    void show(){
        for(int i = 0; i<2*n-1; i++){
            cout<<a[i]<<" ";
        }
        cout<<"\n";
    }
};

int main()
{
    const int s = 5;
    int arr[s] = {1,2,3,4,5};
    WT wt(arr,s);
    wt.buildTree();

    wt.show();
    wt.removeWinner(0);
    wt.show();

    return 0;
}
