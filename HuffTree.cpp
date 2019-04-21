#include <iostream>
#include "HuffTree.h"
#include <string.h>

HuffTree::HuffTree() {
 //default constructor
}

void HuffTree::buildTree(MinHeap * mh) {
	TreeNode *e, *f, *g;
	while (mh->getSize() > 1) {
		e = mh->removeMin();
		f = mh->removeMin();
		g = new TreeNode('*', e->getFrequency() + f->getFrequency());
		g->join(e,f);
		mh->insert(g);
	}
	root = mh->removeMin();
}

void HuffTree::generateCodes() {
	char * path = (char*)malloc(sizeof(char) * 1000);
	tvsHuffTree(root,path,0);
	free(path);
}

void HuffTree::tvsHuffTree(TreeNode * r, char * path, int current) {
	if (r->getLeft() != NULL) {
		path[current] = '1';
		tvsHuffTree(r->getLeft(),path,current +1);
	}
	if (r->getRight() != NULL) {
                path[current] = '0';
                tvsHuffTree(r->getRight(),path,current +1);
        }
	if (r->isLeafNode() == true) {
		path[current] = '\0';
		//cout << (char)r->getVal() << ": " << path << "\r\n";
		string s(path);
		array[r->getVal()] = s;
		return;	
	}
}
void HuffTree::deleteTree() {
	deleteLeaves(root);
} 




void HuffTree::deleteLeaves(TreeNode * r) {
	if (r->isLeafNode() == true) {
		delete r;
	}
	else {
		deleteLeaves(r->getRight());
		deleteLeaves(r->getLeft());
		delete r;
	}
}
TreeNode * HuffTree::getRoot() {
	return root;
}

string HuffTree::getCharCode(int c) {
	return array[c];

}

HuffTree::~HuffTree() {
	deleteTree();
}
