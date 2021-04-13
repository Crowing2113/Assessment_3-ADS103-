#include <fstream>
#include <iostream>
#include <string>
#include "NumberNode.h"
#include "AVL.h"
using namespace std;

void Question1() {
	AVL avl;
	ifstream readFile;

	int numberOfNums;
	readFile.open("input-q1a2.txt");
	readFile >> numberOfNums;
	//loop as many times as the amount of numbers that are being inserted
	for (int i = 1; i <= numberOfNums; i++) {
		int currNum;
		readFile >> currNum;
		avl.insert(new NumberNode(currNum));
	}
	readFile.close();

	//run a Breadth-First traversal
	avl.bft(avl.root);
}
void main() {
	Question1();
	system("pause");
}