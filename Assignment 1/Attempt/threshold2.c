#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10020
#define RANGE_OF_NUMBERS 10020
#define MAX_THRESHOLD 80
#define MIN_THRESHOLD 1
#define SAMPLE_SIZE 10000
void output(int*);
int* input();
void merge(int *a, int p, int q, int r);
void merge_sort(int *a,int p,int r, int threshold );
void binary_sort(int *p, int low, int high);
int binary_search(int *p , int key ,int low, int end);
void test1(int);
double test2(int);
int threshold, array_size;


void main(){
	for(int i = MIN_THRESHOLD;i<MAX_THRESHOLD;i++){
		test1(i);
	}

}
double test2(int threshold){//will return time taken by a fixed threshold on a 
	int *p;
	time_t t;
	clock_t clk;
	double time_taken;
	srand((unsigned)time(&t));
	p = input();
	clk = clock();
	merge_sort(p, 0, array_size-1,threshold);// nlg(n) time
	clk = clock() - clk ;
	time_taken = ((double)clk)/CLOCKS_PER_SEC;
	free(p);
	return time_taken;
}
void test1(int threshold){
	FILE *fp;
	double time_taken = 0;
	for (int i = 0; i < SAMPLE_SIZE; ++i){
		array_size = i+20;
		time_taken += test2(threshold);
	}
	fp = fopen("data3.csv","a");
	fprintf(fp,"%d,%lf\n",threshold,time_taken);
	printf("%d",threshold);
	fclose(fp);
}

void merge_sort(int *a,int p,int r ,int threshold){
	int q;
	if (p+threshold-1< r )
	{
		q = (p + r)/2;
		merge_sort(a, p, q,threshold);
		merge_sort(a, q+1, r,threshold);
		merge(a, p, q, r);
	}
	else
	{
		binary_sort(a,p,r);
	}

}
void merge(int *a, int p, int q, int r){
	int *c, i, j, k, l;
	c = (int*)malloc((r-p+1)*sizeof(int));
	for ( i = p, l = 0; i <=q; ++i, l++)
	{
		c[l] = a[i];
	}
	for ( j = q+1; j <= r; ++j,l++)
	{
 		c[l] = a[j];
	}
	i = p;
	j = q+1;
	for ( k = p; k <= r && j<=r && i<=q; ++k)
	{
		if (c[i] <= c[j])
			a[k] = c[i++];
		else{
			a[k] = c[j++];
		}
	}
	if(j>r){
		while(k<=r)
		a[k++] = c[i++];

	}
	else if(i>q){
		while(k<=r)
		a[k++] = c[j++];

	}
	free(c);
}
void binary_sort(int *p, int low, int high){
	int *start,j,k,key;
	start = p;
	for(int i = low+1;i <= high;i++)
	{
		key = p[i];
		j = i-1;
		if(p[j] > key){
			k = binary_search(start,key,low,j);
			for( int l = j; l>=k ; l--){
				p[l+1] = p[l];
			}
			p[k] = key;
		}
	}
}
int binary_search(int *p , int key ,int low, int end){
	int high = end,mid = (low + high)/2;
	while(low <= high ){
		if(p[mid]>key){
			if(p[mid-1]<=key || mid == low){ 
				return mid;
			}else{
				high = mid - 1 ;
				mid = (low + high)/2;
			}
		}
		else{
			if(p[mid+1]>key){
				return mid + 1;
			}else{
				low = mid + 1;
				mid = (low + high)/2;
			}
		}
		}
	if(low>high)
			return mid;
}

int* input(){
	int *p,*start;
	start = (int*)malloc(array_size*sizeof(int));
	p = start;
	for (int i = 0; i < array_size ; ++i)
	{
		*p = rand()%RANGE_OF_NUMBERS;
		p++;
	}
	return start;
} 
void output(int *p){
	for (int i= 0; i < array_size ;i++)
	{
		printf("%d ",*p);
		p++;
	}
	printf("\n");
}
