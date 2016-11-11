/**
*
*   Assignment 1 - Sorting Q4.
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

using namespace std;

void printarray(int a[], int n){
    for(int i = 0; i<n; i++){
        cout<<a[i]<<" ";
    }
}

//Merge in Linear Time: O(n)
void Merge(int a[], int l, int mid, int r){

    int i = l;
    int j = mid+1;
    int k = 0;
    int c[r-l+1];

    while(i<=mid && j<=r && k<r-l+1){
        if(a[i]>a[j]){
            c[k++] = a[j++];
        }
        else
            c[k++] = a[i++];
    }

    //Append remaining elements
    while(i<=mid && k<r-l+1)
        c[k++]=a[i++];
    while(j<=r && k<r-l+1)
        c[k++]=a[j++];

    for(i= l; i<=r; i++){
        a[i] = c[i-l];
    }
}

//Recursively Sort 2 Halves and then Merge => T(n) = 2*T(n/2) + O(n) => T(n) = O(n*log(n))
void MergeSort(int a[], int l, int r){
    if(l<r){
        int mid = (l+r)/2;
        MergeSort(a,mid+1,r);
        MergeSort(a,l,mid);
        Merge(a,l,mid,r);
    }
}

int main()
{
    int n;
    cout<<"Enter Length of Array to be sorted using Merge Sort:\t";
    cin>>n;
    int a[n];
    cout<<"\nEnter Array:\t";
    for(int i= 0; i<n; i++){
        cin>>a[i];
    }
    MergeSort(a,0,n-1);
    cout<<"\nSorted Using MergeSort:\t";
    printarray(a,n);
    return 0;
}
