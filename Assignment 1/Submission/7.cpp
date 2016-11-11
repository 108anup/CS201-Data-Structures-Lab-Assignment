/**
*
*   Assignment 1 - Sorting Q7.
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
int Merge(int a[], int l, int mid, int r){

    int invcount = 0;
    int i = l;
    int j = mid+1;
    int k = 0;
    int c[r-l+1];

    while(i<=mid && j<=r && k<r-l+1){
        if(a[i]>a[j]){
            //if there is an element a[i] > a[j] implies a[j] < all of {a[i],a[i+1],a[i+2]...a[mid]} 
            //and thus there are mid-i+1 inversions for element a[j].
            invcount+=mid-i+1; 
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
    return invcount;
}

//Recursively Sort 2 Halves and then Merge => T(n) = 2*T(n/2) + O(n) => T(n) = O(n*log(n))
int MergeSort(int a[], int l, int r){
    int invcount = 0;
    if(l<r){
        int mid = (l+r)/2;
        invcount+=MergeSort(a,mid+1,r);
        invcount+=MergeSort(a,l,mid);
        invcount+=Merge(a,l,mid,r);
    }
    return invcount;
}

int main()
{
    int n;

    cout<<"Enter Size of Array for Input:\t";
    cin>>n;

    cout<<"\nEnter Array:\t";

    int a[n];
    for(int i = 0; i<n; i++){
        cin>>a[i];
    }

    int inv = MergeSort(a,0,n-1);
    cout<<"\nSorted Array:\t";
    printarray(a,n);

    //Since Inversions are counted within Merge Sort routine without any extra Time costs 
    //Thus Time complexity for Inversion calculation stands as O(n*log(n))
    cout<<"\nNumber of Inversions are:\t"<<inv;
    return 0;
}
