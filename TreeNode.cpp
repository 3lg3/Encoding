#include <iostream>
#include "TreeNode.h"

#include <string>

TreeNode::TreeNode() {
}
TreeNode::TreeNode(unsigned char Val, unsigned int Frequency)
{
	val = Val;
	frequency = Frequency;
	left = NULL;
	right = NULL;
}

unsigned TreeNode::getFrequency()
{
	return frequency;
}
unsigned TreeNode::getVal()
{
	return val;
}
bool TreeNode::isLeafNode() {
	if (left == NULL && right == NULL) return true;
	return false;

}
//puts left as the left child and right as the right child of this node
void TreeNode::join(TreeNode * Left, TreeNode * Right) {
	left = Left;
	right = Right;

}

TreeNode * TreeNode::getLeft() {
	return left;

} //returns the left child
TreeNode * TreeNode::getRight() {
	return right;
} //returns the right child

TreeNode::~TreeNode() {
}

