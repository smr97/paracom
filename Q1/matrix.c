#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#define THRESH 100000

extern void found(int, int);
extern int elem;

void matrix_search(int** mat, stack* s, node* n){
	int nrows = (n->r_r) - (n->l_r) + 1;
	int ncols = (n->r_c) - (n->l_c) + 1;
	int l_r = n->l_r;
	int l_c = n->l_c;
	int r_r = n->r_r;
	int r_c = n->r_c;
	free(n);
	int topl = mat[n->l_r][n->l_c];
	int botr = mat[n->r_r][n->r_c];
	/*if(topl>elem){
		//printf("%d, (%d, %d);(%d, %d)", elem, l_r, l_c, r_r, r_c);
		return;
	}
	else if(topl==elem)
		return found(l_r, l_c);
	else if(botr<elem){
		//printf("%d, (%d, %d);(%d, %d)", elem, l_r, l_c, r_r, r_c);
		return;
	}
	else if(botr==elem)
		return found(r_r, r_c);*/
	if(nrows*ncols>THRESH){
		if(nrows<ncols){
			node* n1 = create_node(l_r, l_c, l_r+nrows-1, l_c+nrows-1);
			node* n2 = create_node(l_r, l_c+nrows, r_r, r_c);
			push(s, n1);
			push(s, n2);
		}
		else if(ncols<nrows){
			node* n1 = create_node(l_r, l_c, l_r+ncols-1, l_c+ncols-1);
			node* n2 = create_node(l_r+ncols, l_c, r_r, r_c);
			push(s, n1);
			push(s, n2);
		}
		else{
			if(nrows%2==0){
				int c1 = mat[l_r+nrows/2-1][l_c+nrows/2-1];
				int c2 = mat[l_r+nrows/2][l_c+nrows/2];
				if(elem==c1)
					return found(l_r+nrows/2-1, l_c+nrows/2-1);
				else if(elem==c2)
					return found(l_r+nrows/2, l_c+nrows/2);
				else if(elem<c1){
					node *n1 = create_node(l_r, l_c, l_r+nrows/2-2, l_c+nrows/2-2);
					node *n2 = create_node(l_r, l_c+nrows/2-1, l_r+nrows/2-2, r_c);
					node *n3 = create_node(l_r+nrows/2-1, l_c, r_r, l_c+nrows/2-2);
					push(s, n1);
					push(s, n2);
					push(s, n3);
				}
				else if(elem>c2){
					node *n1 = create_node(l_r+nrows/2+1, l_c+nrows/2+1, r_r, r_c);
					node *n2 = create_node(l_r, l_c+nrows/2+1, l_r+nrows/2, r_c);
					node *n3 = create_node(l_r+nrows/2+1, l_c, r_r, l_c+nrows/2);
					push(s, n1);
					push(s, n2);
					push(s, n3);
				}
				else{
					node *n1 = create_node(l_r+nrows/2, l_c, r_r, l_c+nrows/2-1);
					node *n2 = create_node(l_r, l_c+nrows/2, l_r+nrows/2-1, r_c);
					push(s, n1);
					push(s, n2);
				}
			}
			else{
				int mid = mat[l_r+nrows/2][l_c+nrows/2];
				if(elem==mid)
					return found(l_r+nrows/2, l_c+nrows/2);
				else if(elem>mid){
					node *n1 = create_node(l_r+nrows/2+1, l_c+nrows/2+1, r_r, r_c);
					node *n2 = create_node(l_r, l_c+nrows/2+1, l_r+nrows/2, r_c);
					node *n3 = create_node(l_r+nrows/2+1, l_c, r_r, l_c+nrows/2);
					push(s, n1);
					push(s, n2);
					push(s, n3);
				}
				else if(elem<mid){
					node *n1 = create_node(l_r, l_c, l_r+nrows/2-1, l_c+nrows/2-1);
					node *n2 = create_node(l_r, l_c+nrows/2, l_r+nrows/2-1, r_c);
					node *n3 = create_node(l_r+nrows/2, l_c, r_r, l_c+nrows/2-1);
					push(s, n1);
					push(s, n2);
					push(s, n3);
				}

			}
		}
	}
	else{
		int rowi = l_r;
		int coli = r_c;
		//start at top right, if greater, go down. If lesser, go left.
		while(rowi<=r_r&&coli>=l_c){
			if(elem==mat[rowi][coli])
				return found(rowi, coli);
			else if(elem<mat[rowi][coli]){
				coli--;
				continue;
			}
			else{
				rowi++;
				continue;
			}
		}
		return;
	}
}

void binary_search(int** mat, node* n){
	int l_r = n->l_r;
	int l_c = n->l_c;
	int r_r = n->r_r;
	int r_c = n->r_c;
	int lval = mat[l_r][l_c];
	int rval = mat[r_r][r_c];
	free(n);
	/*if(elem>rval||elem<lval){
		//printf("%d, (%d, %d);(%d, %d)", elem, l_r, l_c, r_r, r_c);
		return;
	}
	if(elem==rval)
		return found(r_r, r_c);
	if(elem==lval)
		return found(l_r, l_c);*/
	//This subproblem has the solution:
	if(r_r==l_r){
		int left = l_c;
		int right = r_c;
		int mid;
		while((right-left)>1){
			mid = (left+right)/2;
			if(elem>mat[l_r][mid]){
				left = mid;
			}
			else if(elem<mat[l_r][mid]){
				right = mid;
			}
			else{
				return found(l_r, mid);
			}
		}
		if(mat[l_r][left]==elem)
			return found(l_r, left);
		if(mat[l_r][right]==elem)
			return found(l_r, right);
	}
	else{
		int left = l_r;
		int right = r_r;
		int mid;
		while((right-left)>1){
			mid = (left+right)/2;
			if(elem>mat[mid][l_c]){
				left = mid;
			}
			else if(elem<mat[mid][l_c]){
				right = mid;
			}
			else{
				return found(mid, l_c);
			}
		}
		if(mat[left][l_c]==elem)
			return found(left, l_c);
		if(mat[right][l_c]==elem)
			return found(right, l_c);

	}
}

void double_bs(int** mat, stack* s, node* n){
	int l_r = n->l_r;
	int l_c = n->l_c;
	int r_r = n->r_r;
	int r_c = n->r_c;
	int lval = mat[l_r][l_c];
	int rval = mat[r_r][r_c];
	free(n);
	/*if(elem>rval||elem<lval){
		//printf("%d, (%d, %d);(%d, %d)", elem, l_r, l_c, r_r, r_c);
		return;
	}
	if(elem==rval)
		return found(r_r, r_c);
	if(elem==lval)
		return found(l_r, l_c);*/
	//This subproblem has the solution:
	if((r_r-l_r+1)*(r_c-l_c+1)>THRESH){
		if((r_r-l_r)==1){
			int c1 = mat[l_r][(l_c+r_c)/2];
			int c2 = mat[r_r][(l_c+r_c)/2];
			if(elem<c1){
				node* temp = create_node(l_r, l_c, l_r, (l_c+r_c)/2-1);
				return binary_search(mat, temp);
			}
			else if(elem>c2){
				node* temp = create_node(r_r, (r_c+l_c)/2+1, r_r, r_c);
				return binary_search(mat, temp);
			}
			else if(c1<elem&&elem<c2){
				node* n1 = create_node(l_r, (l_c+r_c)/2+1, l_r, r_c);
				node* n2 = create_node(r_r, l_c, r_r, (l_c+r_c)/2);
				push(s, n1);
				return binary_search(mat, n2);
			}
			else if(c1==elem)
				return found(l_r, (l_c+r_c)/2);
			else
				return found(r_r, (l_c+r_c)/2);
		}
		else{
			int c1 = mat[(l_r+r_r)/2][l_c];
			int c2 = mat[(l_r+r_r)/2][r_c];
			if(elem<c1){
				node* temp = create_node(l_r, l_c, (l_r+r_r)/2-1, l_c);
				return binary_search(mat, temp);
			}
			else if(elem>c2){
				node* temp = create_node((r_r+l_r)/2+1, r_c, r_r, r_c);
				return binary_search(mat, temp);
			}
			else if(c1<elem&&elem<c2){
				node* n1 = create_node((l_r+r_r)/2+1, l_c, l_r, l_c);
				node* n2 = create_node(l_r, r_c, (r_r+l_r)/2-1, r_c);
				push(s, n1);
				return binary_search(mat, n2);
			}
			else if(c1==elem)
				return found(l_r, (l_c+r_c)/2);
			else
				return found(r_r, (l_c+r_c)/2);
		}
	}
	else{
		int rowi = l_r;
		int coli = r_c;
		//start at top right, if greater, go down. If lesser, go left.
		while(rowi<=r_r&&coli>=l_c){
			if(elem==mat[rowi][coli])
				return found(rowi, coli);
			else if(elem<mat[rowi][coli]){
				coli--;
				continue;
			}
			else{
				rowi++;
				continue;
			}
		}
		return;
	}
}


