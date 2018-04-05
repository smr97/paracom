#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "matrix.h"
#include <omp.h>
#include <time.h>

#define THREADCOUNT 10

volatile int busy[THREADCOUNT];
volatile int f[16];	//Cache line aligned
int elem;	//see if you want to align this

struct timespec start[THREADCOUNT], end[THREADCOUNT];
double st, en;

int** generate_matrix(int size){
	int** data = (int**) malloc(size*sizeof(int*));
	int i = 0;
	for(i = 0; i<size; i++){
		data[i] = (int*) malloc(size*sizeof(int));
	}
	#pragma omp parallel num_threads(THREADCOUNT)
	{
		int x, y;
		int compute_block = size/THREADCOUNT;
		for(x = omp_get_thread_num()*compute_block; x<((omp_get_thread_num()+1)*compute_block)&&x<size; x++){
			for(y = 0; y<size; y++){
				data[x][y] = x*size+y;
			}
		}
	}
	return data;
}

void notfound(stack* s){
	int i = 0;
	for(; i<THREADCOUNT; i++){
		if(busy[i]==1){
			//printf("%d is busy\n", i);
			return;
		}
	}
	if(s->size!=0||f[0]==1)
		return;
	f[0] = 1;
	en = omp_get_wtime();
	//printf("element not found, time:%lf\n", en-st);
}

void found(int row, int col){
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, end+omp_get_thread_num());
	f[0] = 1;
	en = omp_get_wtime();
	//printf("Found %d at (%d, %d). Time taken:%lf\n", elem, row, col, en-st);//(end[omp_get_thread_num()].tv_nsec-start[omp_get_thread_num()].tv_nsec)/1000);
}

void prod_consume(int** mat, stack* s){
	f[0] = 0;
	#pragma omp parallel num_threads(THREADCOUNT)
	{
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, start+omp_get_thread_num());
		//printf("%d\n", omp_get_num_threads());
		while(f[0] == 0){
			node* n = pop(s);
			//print_stack(s);
			busy[omp_get_thread_num()] = 1;
			//printf("%d\n", omp_get_thread_num());
			if(n==NULL){
				//printf("NULL\n");
				busy[omp_get_thread_num()] = 0;
				notfound(s);
				continue;
			}
			int nrows = (n->r_r)-(n->l_r)+1;
			int ncols = (n->r_c)-(n->l_c)+1;
			if(nrows==1||ncols==1){
				//printf("1\n");
				binary_search(mat, n);
			}
			else if(nrows==2||ncols==2){
				//printf("2\n");
				double_bs(mat, s, n);
			}
			else{
				//printf("3\n");
				matrix_search(mat, s, n);
			}
			busy[omp_get_thread_num()] = 0;
		}
	}
}

int main(int argc, char* argv[]){
	int tsize = (int)argv[1][0]-(int)'0';
	//size is in log base 10
	int i = 0;
	for(; i<strlen(argv[2]); i++){
		elem = elem*10 + ((int)argv[2][i]-(int)'0');
	}
	int size = 10;
	for(i = 1; i<tsize; i++){
		size*=10;
	}
	int** mat = generate_matrix(size);
	stack *s;
	st = omp_get_wtime();
	int c1 = mat[size/2-1][size/2-1], c2 = mat[size/2][size/2];
	//printf("%d %d\n", c1, c2);
	if(elem==c1)
		found(size/2-1, size/2-1);
	else if(elem==c2)
		found(size/2, size/2);
	else if(c1<elem&&elem<c2){
		node *n1 = create_node(0, size/2, size/2-1, size-1);
		node *n2 = create_node(size/2, 0, size-1, size/2-1);
		s = create_stack(n1);
		push(s, n2);
	}
	else if(elem<c1){
		node *n1 = create_node(0, 0, size/2-2, size/2-2);
		node *n2 = create_node(0, size/2-1, size/2-2, size-1);
		node *n3 = create_node(size/2-1, 0, size-1, size/2-2);
		s = create_stack(n2);
		push(s, n1);
		push(s, n3);
	}
	else{
		node *n1 = create_node(0, size/2+1, size/2, size-1);
		node *n2 = create_node(size/2+1, size/2+1, size-1, size-1);
		node *n3 = create_node(size/2+1, 0, size-1, size/2);
		s = create_stack(n1);
		push(s, n3);
		push(s, n2);
	}
	//print_stack(s);
	prod_consume(mat, s);
}
