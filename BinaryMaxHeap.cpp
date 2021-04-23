//

#include "BinaryMaxHeap.h"
//get the left child's index
int BinaryMaxHeap::leftChildIndex(int parent)
{
	int leftChild = 2 * parent + 1;
	if (leftChild < heap.size())
		return leftChild;
	else
		return-1;
}
//get the right child's index
int BinaryMaxHeap::rightChildIndex(int parent)
{
	int rightChild = 2 * parent + 2;
	if (rightChild < heap.size())
		return rightChild;
	else
		return -1;
}
//get the parent's index
int BinaryMaxHeap::parentIndex(int child)
{
	int parent = (child - 1) / 2;
	if (child == 0)
		return -1;
	else
		return parent;
}

//after we insert we heapify up form where the new number ended up
void BinaryMaxHeap::heapifyup(int index)
{
	//If the index is not negative
	//And the parent index is not negative
	//And the index's number is greater than the parent index's number
	if (index >= 0 && parentIndex(index) >= 0 && heap[index].number > heap[parentIndex(index)].number) {
		//then swap
		NumberNode temp = heap[index];
		heap[index] = heap[parentIndex(index)];
		heap[parentIndex(index)] = temp;
		//since there was a swap we run heapifyup recurively on the parent index
		heapifyup(parentIndex(index));
	}
}

//compares the number at index with that of it's children, if it's less than either of them, swap
void BinaryMaxHeap::heapifydown(int index)
{
	//get left and right children index
	int childL = leftChildIndex(index);
	int childR = rightChildIndex(index);
	//child variable representing the path we'' compare down
	int childIndex = childL;
	//if child index is not the root and not negative
	//and current node's number is smalled thant the child node's rank
	if (childL >= 0 && heap[index].number < heap[childIndex].number) {
		//we should the current node with the child, because bigger numbers go to the top
		NumberNode temp = heap[index];
		heap[index] = heap[childIndex];
		heap[childIndex] = temp;
		//keep going down
		heapifydown(childIndex);
	}
}

//inserts at the lowest next free level
void BinaryMaxHeap::Insert(NumberNode element)
{
	heap.push_back(element);
	//run heapifyup to move the element into the correct position
	heapifyup(heap.size() - 1);
}

//removes the first element in the heap (the largest numbers)
void BinaryMaxHeap::DeleteMax()
{
	//if heap is empty then can't delete anything
	if (heap.size() == 0) {
		cout << "Heap is empy" << endl;
		return;
	}
	//replace the first element with the last
	heap[0] = heap[heap.size() - 1];
	//delete last element
	heap.pop_back();
	//then heapifydown starting from root
	heapifydown(0);
}

//this shows the top of the heap, being the largest number
NumberNode* BinaryMaxHeap::ExtractMax()
{
	//if heap is empty then no numbers to return
	if (heap.empty())
		return NULL;
	return &(heap.front());
}

//used to write the heap to the file
void BinaryMaxHeap::writeHeap(ofstream& writeFile) {
	for (NumberNode num : heap) {
		writeFile << num.number<<" ";
	}
	writeFile << endl;
}