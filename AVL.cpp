#include "AVL.h"

int AVL::height(NumberNode* node)
{
	int h = 0;
	//helps break recursion when we reach the end of the branches
	if (node != NULL) {
		int leftH = height(node->leftChild);
		int rightH = height(node->rightChild);

		//max gets the bigger height
		int maxH = max(leftH, rightH);
		h = maxH + 1;
	}
	return h;
}

//difference between the left and right side heights of the tree
int AVL::difference(NumberNode* node)
{
	//if the tree is empty it is balanced, return 0
	if (node == NULL)
		return 0;

	int leftH = height(node->leftChild);
	int rightH = height(node->rightChild);
	int balanceFactor = leftH - rightH;

	return balanceFactor;
}

NumberNode* AVL::RRrotation(NumberNode* parent)
{
	NumberNode* temp = parent->rightChild;
	parent->rightChild = temp->leftChild;
	temp->leftChild = parent;
	if (displayRotations)
		cout << "RR rotation on " << parent->number << endl;

	return temp;
}

NumberNode* AVL::LLrotation(NumberNode* parent)
{
	NumberNode* temp = parent->leftChild;
	parent->leftChild = temp->rightChild;
	temp->rightChild = parent;
	if (displayRotations)
		cout << "LL rotation on " << parent->number << endl;

	return temp;
}

NumberNode* AVL::LRrotation(NumberNode* parent)
{
	NumberNode* temp = parent->leftChild;
	parent->leftChild = RRrotation(temp);
	if (displayRotations)
		cout << "LR rotation on " << parent->number << endl;
	return LLrotation(parent);
}

NumberNode* AVL::RLrotation(NumberNode* parent)
{
	NumberNode* temp = parent->rightChild;
	parent->rightChild = LLrotation(temp);
	if (displayRotations)
		cout << "RL rotation on " << parent->number << endl;
	return RRrotation(parent);
}
//returns a prent, whether new or not but will be balanced
NumberNode* AVL::balance(NumberNode* parent)
{
	//get the balance factor
	int balanceFactor = difference(parent);

	//if the balance factor it not -1,0,1 then work out what rotations to use
	if (balanceFactor > 1) {
		//left branch is heavy, work out which child is heavy
		if (difference(parent->leftChild) > 0) {
			//left child heavy
			parent = LLrotation(parent);
		}
		else {
			//right child heavy
			parent = LRrotation(parent);
		}
	}
	else if (balanceFactor < -1) {
		//right branch is heavy, which child is heavy
		if (difference(parent->rightChild) > 0) {
			//left child heavy
			parent = RLrotation(parent);
		}
		else {
			//right child heavy
			parent = RRrotation(parent);
		}
	}

	return parent;
}

//insert a number then display the tree
NumberNode* AVL::Insert(NumberNode* parent, NumberNode* newNum)
{
	//if sub tree is empty newNumber becomes the parent
	if (parent == NULL) {
		parent = newNum;
		return parent;
	}

	//parent is not null so there isn't an empty space yet
	//go down left or right
	if (newNum->number < parent->number) {
		parent->leftChild = Insert(parent->leftChild, newNum);
		parent = balance(parent);
	}
	else {
		parent->rightChild = Insert(parent->rightChild, newNum);
		parent = balance(parent);
	}
	//TODO: run a Breadth-First Traversal and write the levels out in a txt file
	
	return parent;
}
