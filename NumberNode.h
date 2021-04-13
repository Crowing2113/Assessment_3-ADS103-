#pragma once
#include <iostream>
#include <string>

using namespace std;

class NumberNode
{
public:
	int number;
	NumberNode* leftChild;
	NumberNode* rightChild;

	NumberNode(int number);
};

