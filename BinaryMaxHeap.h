#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <fstream>
#include "NumberNode.h"

using namespace std;

class BinaryMaxHeap
{
public:
	vector<NumberNode> heap;
	int leftChildIndex(int parent);
	int rightChildIndex(int parent);
	int parentIndex(int child);

	void heapifyup(int index);
	void heapifydown(int index);

	void Insert(NumberNode element);
	void DeleteMax();
	NumberNode* ExtractMax();
	void writeHeap(ofstream& writeFile);
};

