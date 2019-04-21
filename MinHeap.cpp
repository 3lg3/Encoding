#include <iostream>
#include <climits>

#include "MinHeap.h"



//implement the methods in MinHeap.h
MinHeap::MinHeap()
{
	n = 0;
	nmax = 1000;
	array = (TreeNode **) malloc (nmax * sizeof(TreeNode *));
	mark = 0;
}

void MinHeap::insert(TreeNode * val)
{
	if (n == nmax) {
		nmax = nmax * 2;
		array = (TreeNode **)realloc(array,nmax * sizeof(TreeNode *));
	}
	array[n] = val;	
	n++;
	mark++;
	int child = n - 1;
	int parent = (child-1)/2;
	while (child > 0) {
		if (array[child]->getFrequency() >= array[parent]->getFrequency()) break;
		TreeNode * tmp = array[child];
		array[child] = array[parent];
		array[parent] = tmp;
		child = parent;
		parent = (child-1)/2;
	}


}

int MinHeap::getSize()
{
	return n;
}

TreeNode * MinHeap::removeMin()
{
	if (n <= 0) return NULL;
	TreeNode * minkey = array[0];
	n--;
	if (n == 0) return minkey;
	array[0] = array[n];
	int parent = 0;
	int left = 2 * parent +1;
	int right = 2 * parent + 2;
	while (left < n) {
		int minchild = left;
		if (right < n && array[right]->getFrequency() < array[left]->getFrequency()) {
			minchild = right;
		}
		if (array[parent]->getFrequency() <= array[minchild]->getFrequency()) break;
		TreeNode * tmp = array[minchild];
		array[minchild] = array[parent];
		array[parent] = tmp;
		parent = minchild;
		left = 2 * parent + 1;
		right = 2 * parent + 2;
	}
	return minkey;		
}
MinHeap::~MinHeap() {
	//if (getSize() > 0) {
	//	for (i = mark-1; i < nmax; i++) {
	//	free(array[i]);
	//	}
		free(array);
//	}
}



	

