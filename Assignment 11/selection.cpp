#include <iostream>

using namespace std;

string s="";

void printit(int a[], int x, int y, int n){
    //Traverse through all the elements and check whether they match the indicies changed
    //If yes then print them
    //Else Print spaces
    for(int i= 0; i<n; i++){
        if(i==x||i==y){
            cout<<a[i]<<"\t";
        }
        else{
            cout<<"\t";
        }
    }

    //After printing the line print a divider
    cout<<"\n"<<s<<"\n";
}

//This Function swaps the elements at the 2 indicies input
//If they are Different
//It Also calls the Print function to show the swap
void swapit(int a[], int x, int y, int n){
    if(x!=y){
        int temp = a[x];
        a[x] = a[y];
        a[y] = temp;
        printit(a,x,y,n);
    }
}

//This funciton is the Selction sort function that sorts a given array in O(n^2) time.
void selsort(int a[], int n){
    for(int i= 0; i<n-1; i++){
        int maxi = i;
        for(int j=i; j<n; j++){
            if(a[j]<a[maxi]){
                maxi = j;
            }
        }
        swapit(a,i,maxi,n);
    }

}

int main()
{
    //Take Appropriate Input
    int n;

    cout<<"Enter the Number of Elements in the Array:\t";
    cin>>n;

    int a[n];
    cout<<"Enter the Array:\n";
    for(int i= 0; i<n; i++){
        cin>>a[i];
    }

    cout<<"\nSorting:\n\n";

    //String s is the divider printing between two lines and and depends on the length of the array
    for(int i= 0; i<n; i++){
        cout<<a[i]<<"\t";
        s=s+"--------";
    }
    cout<<"\n"<<s<<"\n";

    selsort(a,n);
    return 0;
}
