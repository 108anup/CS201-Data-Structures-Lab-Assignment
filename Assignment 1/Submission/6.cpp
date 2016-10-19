/**
*
*   Assignment 1 - Sorting Q6.
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

//If Element exists then return its index else return -1 in O(log(n))
int BinarySearch(int a[], int l, int r, int q){

    while(l<=r){
        int mid = l+(r-l)/2;

        if(a[mid]==q){
            return mid;
        }
        else if(a[mid]<q){
            l = mid+1;
        }
        else if(a[mid]>q){
            r = mid-1;
        }
    }
    return -1;
}

//O(n*log(n)) Algorithm to find whether there exits elements a[i] + b[j] = m
bool misaplusb(int a[],int b[], int m, int n){
    //For each element in array: a use Binary search to find an element m-a in array: b => O(n*log(n))
    bool flag = false;
    for(int i= 0; i<n; i++){
        int index = BinarySearch(b,0,n-1,m-a[i]);
        if(index!=-1){
            flag = true;
            break;
        }
    }
    return flag;
}

int main()
{
    int n,m;
    cout<<"Enter Length of the 2 arrays:\t";
    cin>>n;

    int a[n];
    int b[n];

    cout<<"\nEnter First Array:\t";
    for(int i=0; i<n; i++){
        cin>>a[i];
    }

    cout<<"\nEnter Second Array:\t";
    for(int i=0; i<n; i++){
        cin>>b[i];
    }

    cout<<"\nEnter Value of m\t";
    cin>>m;

    //Sort one of the Arrays in O(n*log(n)) Time 
    MergeSort(b,0,n-1);

    //Find if there exists elements such that a[i] + b[j] = m in O(n*log(n))
    if(misaplusb(a,b,m,n))
        cout<<"\nYes, there exists a in A and b in B such that a+b = m\n";
    else
        cout<<"\nNo, there does not exist any a in A and b in B such that a+b = m\n";

    //Thus Overall Time Complexity is O(n*log(n))


    return 0;
}
