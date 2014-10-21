#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void bottom_up_heap_sort(int*, int);
void heap_sort(int*, int);
void sift_up(int*, int);
void sift_down(int*, int);
void build_max_heap(int*, int); 
void bottom_up_build_max_heap(int*, int);
void randomize_in_place(int*, int);
int* generate_array(int);
void swap(int*, int*);
int cmp(int, int);
void print_array(int*, int);

int heapsize;
unsigned long comparison_counter;
clock_t begin, end;
double time_spent;

int main() {
	int k, N;
	int* A;
	int* B;
	int i;

	printf("Testing Sift_Down Heap Sort\n");
	for(k = 2; k <= 5; k++) {
		comparison_counter = 0;
		N = (int)pow((double)10, k);

		begin = clock();
		A = generate_array(N);
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("Time Spent Generating Array: %f\n", time_spent);

		// print the first unsorted array
		//printf("Unsorted Array:\n");
		//print_array(A, N);

		begin = clock();
		// call heap_sort on the first unsorted array
		heap_sort(A, N);
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

		// show that the array is now sorted
		//printf("Sorted array: \n");
		//print_array(A, N);
		printf("Done with k = %d\n", k);
		printf("Comparisons for Heap Sort: %lu\n", comparison_counter);
		printf("Time Spent on Heap Sort: %f\n", time_spent);
		printf("\n");
	}

	printf("----------------------------------\n");
	printf("Testing Sift_Up Heap Sort\n");
        for(k = 2; k <= 5; k++) {
		comparison_counter = 0;
                N = (int)pow((double)10, k);

		begin = clock();
                B = generate_array(N);
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		printf("Time Spent Generating Array: %f\n", time_spent);

                // print the unsorted array
                //printf("Unsorted Array:\n");
                //print_array(B, N);

		begin = clock();
                // call heap_sort on the unsorted array
                bottom_up_heap_sort(B, N);
		end = clock();
		time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

                // show that the array is now sorted
                //printf("Sorted array: \n");
                //print_array(B, N);
                printf("Done with k = %d\n", k);
		printf("Comparisons for Heap Sort: %lu\n", comparison_counter);
		printf("Time Spent on Heap Sort: %f\n", time_spent);
		printf("\n");
        }

	printf("----------------------------------\n");

	return 0;
}

void bottom_up_heap_sort(int* arr, int len) {
	int i;

	// build a max heap from the bottom up using sift up
	bottom_up_build_max_heap(arr, len);
	printf("Comparisons for heap construction: %lu\n", comparison_counter);
 	comparison_counter = 0;	
	for(i = len-1; i >= 0; i--) {
		// swap the last leaf and the root
		swap(&arr[i], &arr[0]);
		// remove the already sorted values
		len--;
		// repair the heap
		bottom_up_build_max_heap(arr, len);
	}
}

void heap_sort(int* arr, int len) {
	int i;

	// build a max heap from the array
	build_max_heap(arr, len);
	printf("Comparisons for heap construction: %lu\n", comparison_counter);
	comparison_counter = 0;
	for(i = len-1; i >= 1; i--) {
		swap(&arr[0], &arr[i]); // move arr[0] to its sorted place
		// remove the already sorted values
		heapsize--;
		sift_down(arr, 0);	// repair the heap
	}
}

void sift_down(int* arr, int i) {
	int c = 2*i+1;
	int largest;

	if(c >= heapsize) return;

	// locate largest child of i
	if((c+1 < heapsize) && cmp(arr[c+1], arr[c]) > 0) {
		c++;
	}

	// if child is larger than i, swap them
	if(cmp(arr[c], arr[i]) > 0) {
		swap(&arr[c], &arr[i]);
		sift_down(arr, c);
	}
}

void sift_up(int* arr, int i) {
	if(i == 0) return; // at the root

	// if the current node is larger than its parent, swap them
	if(cmp(arr[i], arr[(i-1)/2]) > 0) {
		swap(&arr[i], &arr[(i-1)/2]);
		// sift up to repair the heap
		sift_up(arr, (i-1)/2);
	}
}

void bottom_up_build_max_heap(int* arr, int len) {
	int i;
	for(i = 0; i < len; i++) {
		sift_up(arr, i);
	}
}

void build_max_heap(int* arr, int len) {
	heapsize = len;
	int i;
	for(i = len/2; i >= 0; i--) {
		// invariant: arr[k], i < k <= n are roots of proper heaps
		sift_down(arr, i);
	}
}

void randomize_in_place(int* arr, int n) {
	int j, k;
	double val;
	time_t t;
	// init the random number generator
	srand((unsigned)time(&t));

	// randomization code from class notes
	for(j = 0; j < n-1; j++) {
		val = ((double)random()) / 0x7FFFFFFF;
		k = j + val*(n-j);
		swap(&arr[k], &arr[j]);
	}
}

// this function is responsible for creating and populating an array 
// of size k, and randomizing the locations of its elements
int* generate_array(int k) {
	int* arr = (int*) malloc(sizeof(int)*k-1);
	int i, j, x, N;
	double val;
	time_t t;
	// init the random number generator
	srand((unsigned)time(&t));

	// fill the array with values from 1..N
	for(i = 0; i <= k-1; i++) {
		arr[i] = i+1;
	}

	N = (int)pow((double)10, 5);
	// randomize the elements of the arry for 10^5 iterations
	for(i = 0; i < N; i++) {
		randomize_in_place(arr, k);
	}

	return arr;
}

// swap two elements
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int cmp(int a, int b) {
	comparison_counter++;
	
	if(a > b) return 1;
	else if(a < b) return -1;
	else return 0;
}

// print out an array by iterating through
void print_array(int* arr, int size) {
	int i;
	for(i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
}
