/**
*
*   Assignment 1 - Sorting Q5.
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

//Find Index of the (rightmost - in case of repetitions) largest element <= q in O(log2(r-l+1))
int BinarySearch(int a[], int l, int r, int q){

    while(l<r){
        //Since we update l = mid and r = mid-1 so the mid element
        //should point towards the right median in case of even length array
        int mid = l+ (r-l+1)/2;

        //Define Predicate as a[mid]<=q
        if(a[mid]<=q){
            l = mid;
        }
        else if(a[mid]>q){
            r = mid-1;
        }
    }

    //If all the elements are greater than q then l-1 is returned else l is returned.
    if(a[l]<=q)
        return l;
    else return l-1;
}

void InsertionSort_Binary(int a[], int l, int r){

    for(int i = l+1; i<=r; i++){
        int temp = a[i];

        //Find Index of the (rightmost - in case of repetitions)
        //largest element <= a[i] in the array from 0 to i-1 in O(i)
        int j = BinarySearch(a,l,i-1,a[i]);

        //Linearly Shift Elements O(i-j-1)
        for(int k = i-1; k>=j+1; k--){
            a[k+1] = a[k];
        }
        a[j+1]=temp;
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
void MergeSort(int a[], int l, int r, int threshold){
    if(r-l<threshold){
        InsertionSort_Binary(a,l,r);
    }
    if(l<r){
        int mid = (l+r)/2;
        MergeSort(a,mid+1,r,threshold);
        MergeSort(a,l,mid,threshold);
        Merge(a,l,mid,r);
    }
}

int main()
{
    int threshold = 55;
    int n;
    cout<<"Enter Length of Array to be sorted using Merge Sort:\t";
    cin>>n;
    int a[n];
    cout<<"\nEnter Array:\t";
    for(int i= 0; i<n; i++){
        cin>>a[i];
    }
    MergeSort(a,0,n-1,threshold);
    cout<<"\nSorted Using MergeSort with Binary Insertion Sort:\t";
    printarray(a,n);
    return 0;
}
