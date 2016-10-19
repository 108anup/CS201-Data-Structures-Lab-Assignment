/**
*
*   Assignment 1 - Sorting
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
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <fstream>

#define MAX 50000
#define MOD int(1e9+7)
#define CPMS (CLOCKS_PER_SEC/1000.0)

int comp = 0; //To count number of comparisons of two elements of array
int invcount = 0;
int threshold = 0;

using namespace std;

struct computation{

    int iscomp;
    int isbcomp;
    int mcomp;
};

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = a;
}
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
            comp++;
        }
        else if(a[mid]>q){
            r = mid-1;
            comp++;
        }
    }

    //If all the elements are greater than q then l-1 is returned else l is returned.
    comp++;
    if(a[l]<=q)
        return l;
    else return l-1;
}

//Sort in O(n^2)
void InsertionSort(int a[], int l, int r){

    for(int i = l+1; i<=r; i++){
        //Array is sorted till length i;
        int j=i-1;
        int temp = a[i];

        //Linearly Check Where to Insert the current Element in O(j)
        comp++;
        while(a[j]>temp && j>=l){
            comp++;
            a[j+1]=a[j];    //Shift Elements
            j--;
        }
        a[j+1] = temp;  //Insert the new element at the correct location
    }

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

void Merge(int a[], int l, int mid, int r){

    int i = l;
    int j = mid+1;
    int k = 0;
    int c[r-l+1];

    while(i<=mid && j<=r && k<r-l+1){
        comp++;
        if(a[i]>a[j]){
            invcount+=mid-i+1;
            c[k++] = a[j++];
        }
        else
            c[k++] = a[i++];
    }

    while(i<=mid && k<r-l+1)
        c[k++]=a[i++];
    while(j<=r && k<r-l+1)
        c[k++]=a[j++];

    for(i= l; i<=r; i++){
        a[i] = c[i-l];
    }
}

void MergeSort(int a[], int l, int r){
    if(r-l<threshold){
        InsertionSort_Binary(a,l,r);
    }
    if(l<r){
        int mid = (l+r)/2;
        MergeSort(a,mid+1,r);
        MergeSort(a,l,mid);
        Merge(a,l,mid,r);
    }
}

//O(n*log(n)) Algorithm to find whether there exits elements a[i] + b[j] = m
bool misaplusb(int a[],int b[], int m, int n){
    bool flag = false;
    for(int i= 0; i<n; i++){
        int index = BinarySearch(b,0,n-1,a[i]);
        if(index!=-1 && b[index]==a[i]){
            flag = true;
            break;
        }
    }
    return flag;
}

/** Codes to Test Above Written Modules */
computation Compute_Comparisons(int n, bool v=false){

    int a[n];
    int b[n];
    int c[n];

    for(int i= 0; i<n; i++){
        c[i] = b[i] = a[i] = rand()%MOD;
    }

    if(v){
        cout<<"\n\n\nInitial Array of size: "<<n<<" :\n";
        printarray(a,n);
        cout<<"\n\n";
    }

    computation my;

    comp = 0;
    InsertionSort(a,0,n-1);
    my.iscomp = comp;

    comp = 0;
    InsertionSort_Binary(b,0,n-1);
    my.isbcomp = comp;

    comp = 0;
    MergeSort(c,0,n-1);
    my.mcomp = comp;

    if(v){
        printarray(a,n);
        cout<<"\n(Insertion Sort) Comparisons = "<<my.iscomp<<"\n\n";
        printarray(b,n);
        cout<<"\n(Insertion Sort with Binary Search) Comparisons = "<<my.isbcomp<<"\n\n";
        printarray(c,n);
        cout<<"\n(Merge Sort) Comparisons = "<<my.mcomp<<"\nTime = "<<"\n\n";
    }

    return my;
}


void Check_Insertions_Sort(int n){
    int a[n];
    //Check Binary Search with Insertion Sort
    for(int i= 0; i<n; i++){
        a[i] = rand()%MOD;
    }
    printarray(a,n);
    cout<<"\n";
    InsertionSort(a,0,n-1);
    cout<<"\n\nSorted Using Insertion Sort\n";
    printarray(a,n);
}

void Check_Insertions_Sort_Binary(int n){
    int a[n];
    //Check Binary Search with Insertion Sort
    for(int i= 0; i<n; i++){
        a[i] = rand()%MOD;
    }
    printarray(a,n);
    cout<<"\n";
    InsertionSort_Binary(a,0,n-1);
    cout<<"\n\nSorted Using Insertion Sort with Binary Search\n";
    printarray(a,n);
}

void Check_MergeSort(int n){
    int a[n];
    //Check Binary Search with Insertion Sort
    for(int i= 0; i<n; i++){
        a[i] = rand()%MOD;
    }
    printarray(a,n);
    cout<<"\n";
    MergeSort(a,0,n-1);
    cout<<"\n\nSorted Using MergeSort\n";
    printarray(a,n);
}

void generateGraph_Threshold(){

    ofstream fout;
    fout.open("graph5.txt",ios::out);
    for(threshold = 2; threshold<80; threshold++){
        double elapsedTime = 0;
        for(int i = 2; i<10000; i++){
            int a[i];
            for(int j= 0; j<i; j++){
                a[j] = rand()%MOD;
            }
            double t = clock();
            MergeSort(a,0,i-1);
            double time_taken = clock() - t;
            elapsedTime += time_taken;
        }
        cout<<threshold<<" "<<elapsedTime/10000<<"\n";
        fout<<threshold<<" "<<elapsedTime/10000<<"\n";
    }
}
void generateGraph_Comparisons(){
    FILE* fout = fopen("graph.txt","w");
    for(int i=1; i<100; i++){
        computation comps = Compute_Comparisons(i,false);
        fprintf(fout,"%d %d %d %d\n",i,comps.iscomp,comps.isbcomp,comps.mcomp);
    }
}
void generateGraph_Time(){
    FILE* fout = fopen("graph3.txt","w");

    void (*sorting_algo[3])(int a[], int f, int l) = {InsertionSort, InsertionSort_Binary, MergeSort};

    for(int n = 2; n<500; n++){
        fprintf(fout,"%d ", n);
        for(int s = 0; s<3; s++){
            double start = clock();
            for(int i=0; i<1000; i++){
                int a[n];
                for(int j = 0; j<n; j++)
                    a[j] = rand()%MOD;
                sorting_algo[s](a,0,n-1);
            }
            double time_taken = clock() - start;
            fprintf(fout,"%.9f ", time_taken);
        }
        fprintf(fout,"\n");
        cout<<n<<"\n";
    }
}

int main()
{
    generateGraph_Threshold();

    return 0;
}
