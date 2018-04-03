#ifndef STACK_H
#define STACK_H

typedef struct node{
	struct node* next;
	int l_c, l_r, r_c, r_r;
}node;

typedef struct stack{
	volatile int size;
	node* top;
}stack;

node* create_node(int, int, int, int);
void print_stack(stack*);
void push(stack*, node*);
node* pop(stack*);
stack* create_stack(node*);

#endif
