#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define EPS 1.0E-9
#define SQ(a) ((a) * (a))


typedef struct {
	int real;
	int imag;
} complex_t;

int fibonacci(int n);
int is_equal(double a, double b);
int compare_complex( const void * elem1, const void * elem2 ); 

int main(void) {
	for(int f = 0; f < 12; f++) {
		printf("fib(%d): %d\n", f, fibonacci(f));	
	}

	printf("is_equal(4.1, 4.10001): %d\n", is_equal(4.1, 4.10001));
	printf("is_equal(4.1, 4.1+smth): %d\n\n", is_equal(4.1, 4.1 + pow(10, -9.01)));

	complex_t *zzz;
	zzz = (complex_t*)malloc(1000 * sizeof(complex_t));

	if(zzz == NULL) {
		fprintf(stderr, "Failed malloc for zzz");
		return EXIT_FAILURE;
	} else {
		complex_t *ptr = zzz;
		srand (time(NULL));
		for(int i = 0; i < 1000; i++) {
			ptr->real = rand()%1000;
			ptr->imag = rand()%1000;
			ptr++;
		}
		qsort(zzz, 1000, sizeof(complex_t), compare_complex);
		printf("Smallest complex is: (%d, %d)\n", zzz->real, zzz->imag);
		printf("Greatest complex is: (%d, %d)\n\n", (zzz+999)->real, (zzz+999)->imag);
		free(zzz);
	}
}

int fibonacci(int n) {
	if(n <= 0) {
		return 0;
	}
	if(n == 1) {
		return 1;
	}
	return fibonacci(n-1) + fibonacci(n-2);
}

int is_equal(double a, double b) {
	if(fabs(a-b) < EPS) {
		return 1;
	} else {
		return 0;
	}	
}

int compare_complex( const void * a, const void * b ) {
	if(a == b) return 0;	
	double diff = (SQ(((complex_t*)a)->real) + SQ(((complex_t*)a)->imag)) -	(SQ(((complex_t*)b)->real) + SQ(((complex_t*)b)->imag));
	if(is_equal(diff, 0)) return 0;
	if(diff < 0) return -1;
	return 1;
} 
