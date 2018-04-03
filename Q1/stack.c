#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

static omp_lock_t l;

node* create_node(int l_r, int l_c, int r_r, int r_c){
	node* temp = (node*) malloc(sizeof(node));
	temp->next = NULL;
	temp->l_r = l_r;
	temp->l_c = l_c;
	temp->r_r = r_r;
	temp->r_c = r_c;
	return temp;
}

stack* create_stack(node* n){
	stack* news = (stack*) malloc(sizeof(stack));
	n->next = NULL;
	news->top = n;
	news->size = 1;
	omp_init_lock(&l);
}

void print_stack(stack* s){
	node* itr = s->top;
	while(itr!=NULL){
		printf("(%d, %d), (%d, %d)\n", itr->l_r, itr->l_c, itr->r_r, itr->r_c);
		itr = itr->next;
	}
}

void push(stack* s, node* n){
	while(omp_test_lock(&l)==0){}
	n->next = s->top;
	s->top = n;
	s->size++;
	omp_unset_lock(&l);
}

node* pop(stack* s){
	node* temp;
	while(omp_test_lock(&l)==0){}
	if(s->size<=0){
		omp_unset_lock(&l);
		return NULL;
	}
	temp = s->top;
	s->top = s->top->next;
	s->size--;
	omp_unset_lock(&l);
	return temp;
}

