#pragma once
#include "NumberNode.h"

using namespace std;

class AVL
{
public:
	bool displayRotations = true;

	NumberNode* root;
	
	//might not use
	NumberNode* search(int numberSearch, bool showSearchPath);

	//calculates the height of sub tree
	int height(NumberNode* node);

	//difference between left and right subtrees
	int difference(NumberNode* node);

	//Rotations:
	NumberNode* RRrotation(NumberNode* parent);
	NumberNode* LLrotation(NumberNode* parent);
	NumberNode* LRrotation(NumberNode* parent);
	NumberNode* RLrotation(NumberNode* parent);
	
	//Balance
	NumberNode* balance(NumberNode* parent);

	//Insert
	NumberNode* Insert(NumberNode* parent,NumberNode* newNum);
};

