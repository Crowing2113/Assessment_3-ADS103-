#include "AVL.h"

NumberNode* AVL::search(int numberSearch, bool showSearchPath)
{
	return nullptr;
}

//get the height of the sub tree
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

//right right rotation for the tree if right branch and right child is heavy
NumberNode* AVL::RRrotation(NumberNode* parent)
{
	NumberNode* temp = parent->rightChild;
	parent->rightChild = temp->leftChild;
	temp->leftChild = parent;
	if (displayRotations)
		cout << "RR rotation on " << parent->number << endl;

	return temp;
}
//left left rotations for the tree if left branch and left child is heavy
NumberNode* AVL::LLrotation(NumberNode* parent)
{
	NumberNode* temp = parent->leftChild;
	parent->leftChild = temp->rightChild;
	temp->rightChild = parent;
	if (displayRotations)
		cout << "LL rotation on " << parent->number << endl;

	return temp;
}

//left right rotation for the tree if left branch and right child is heavy
NumberNode* AVL::LRrotation(NumberNode* parent)
{
	NumberNode* temp = parent->leftChild;
	parent->leftChild = RRrotation(temp);
	if (displayRotations)
		cout << "LR rotation on " << parent->number << endl;
	return LLrotation(parent);
}

//right left rotation for the tree if left branch and right is heavy
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

//insert a number into the tree
NumberNode* AVL::InsertAVL(NumberNode* parent, NumberNode* newNum)
{
	//if sub tree is empty newNumber becomes the parent
	if (parent == NULL) {
		parent = newNum;
		return parent;
	}
	//parent is not null so there isn't an empty space yet
	//go down left or right
	if (newNum->number < parent->number) {
		parent->leftChild = InsertAVL(parent->leftChild, newNum);
		parent = balance(parent);
	}
	else {
		parent->rightChild = InsertAVL(parent->rightChild, newNum);
		parent = balance(parent);
	}
	return parent;
}

//insert new number into tree by calling insert AVL function
void AVL::insert(NumberNode* newNum)
{
	//calls insertAVL which returns a new node for the tree
	root = InsertAVL(root, newNum);
}

//traverses the tree in a level order and writes them to file
void AVL::printLevel(NumberNode* root, int level, ofstream& writeFile)
{
	//if root is null return
	if (root == NULL)
		return;
	//if level is 0 it's the root
	if (level == 0)
		writeFile << " " << root->number;
	//if level is greater than 0 go down next level by calling this function and using left child as root and level - 1, do same for right child
	if (level > 0) {
		printLevel(root->leftChild, level - 1, writeFile);
		printLevel(root->rightChild, level - 1, writeFile);
	}
}

//breadth-first traversal
//traverse through the tree by levels starting at the root
void AVL::bft(NumberNode* root)
{
	//get height of the tree
	int h = height(root);
	ofstream writeFile;
	writeFile.open("output-q1a2.txt", ios_base::ate);

	//for loop runs through thew tree and displays each level
	for (int i = 0; i < h; i++) {
		writeFile << i << ":";
		//calls the print level function
		printLevel(root, i, writeFile);
		writeFile << endl;
	}
}

