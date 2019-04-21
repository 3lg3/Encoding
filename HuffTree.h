#ifndef HUFFTREE_H
#define HUFFTREE_H

#include "MinHeap.h"
#include "TreeNode.h"
#include <string>

#define MAXCODELENGTH 256
#define BYTESIZE 8

using namespace std;

class HuffTree
{
	private:
		//Add class members and methods	
		TreeNode * root;
		string array[256];
	public:
		HuffTree();

		//build a hiffman  tree  give a minheap
		void buildTree(MinHeap * mh);

		//generate codes by traversing the huffman tree
		//and store them in an internal data structure (array of strings for example)
		void generateCodes();
		

		void tvsHuffTree(TreeNode * r, char * path, int current);
		//returns root of the tree
		
		void deleteTree();
		void deleteLeaves(TreeNode *r);
		TreeNode * getRoot();

		//returns huffman code from  the ascii code
		string getCharCode(int c);
		~HuffTree();
		
};


#endif
