#ifndef MINHEAP_H
#define MINHEAP_H

#include "TreeNode.h"


using namespace std;

class MinHeap
{
	private:
		int n; //current number of elements
		int nmax; //Max number of elements
		TreeNode ** array;
		int mark;

	public:
		MinHeap();
		TreeNode * removeMin(); //returns root of heap
		void insert(TreeNode * val); //adds element to heap
		int getSize(); //returns size of heap
		~MinHeap();
};

#endif
