#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "NumberNode.h"
#include "AVL.h"
#include "BinaryMaxHeap.h"

using namespace std;


void ErrorRep(int err, int numberOfNums) {
	switch (err) {
	case 0://when end of file is reached before the loop has reached numberOfNums, means there are less numbers than given
		cout << "ERROR:\n--There are less than " << numberOfNums << " numbers in the file.\nPlease fix." << endl;
		cout << "Closing..." << endl;
		break;
	case 1: //when end of file is not reached, means there are more numbers than given in numberOfNums
		cout << "ERROR:\n--There are more than " << numberOfNums << " numbers in the file.\nPlease fix." << endl;
		cout << "Closing..." << endl;
		break;
	}

}
void Question1() {
	AVL avl;
	ifstream readFile;

	int numberOfNums;

	readFile.open("input-q1a2.txt");
	readFile >> numberOfNums;

	//loop as many times as the amount of numbers that are being inserted
	for (int i = 1; i <= numberOfNums; i++) {
		//checks if it's the end of the file, this means there isn't enough numbers in the file. Tell the user to add more numbers or adjust the first number accordingly
		if (readFile.eof()) {
			ErrorRep(numberOfNums, 0);
			return;
		}
		int currNum;

		readFile >> currNum;
		avl.insert(new NumberNode(currNum));
	}
	//checks if the end of file has not been reached, this means there are more numbers in the file than given
	if (!readFile.eof()) {
		ErrorRep(1, numberOfNums);
		readFile.close();
		return;
	}
	readFile.close();

	//run a Breadth-First traversal
	avl.bft(avl.root);
}

void Question2() {
	BinaryMaxHeap heap;
	ifstream readFile;
	ofstream writeFile;
	int numberOfNums;
	//open both files since we'll be writing to the the output file and reading from the input file in the same loop
	readFile.open("input-q2a2.txt");
	writeFile.open("output-q2a2.txt");

	readFile >> numberOfNums;
	//run for as many times as given in the first number in the file
	for (int i = 0; i < numberOfNums; i++) {
		//if the end of the file has been reached before this has run numberOfNums times then there aren't enough numbers in the file, report, close both files and exit.
		if (readFile.eof()) {
			ErrorRep(0, numberOfNums);
			writeFile << "===Please fix first number in Input file or remove some numbers===";
			writeFile.close();
			readFile.close();
			return;
		}
		int currNum;
		readFile >> currNum;
		//writing heap to file before the insert, then inserting the number, then writing the heap to file again
		heap.writeHeap(writeFile);
		heap.Insert(NumberNode(currNum));
		heap.writeHeap(writeFile);
	}
	//if the end of the file hasn't been reached this means there are more numbers left, report an error, close the files and exit;
	if (!readFile.eof()) {
		ErrorRep(1, numberOfNums);
		writeFile << "===Please fix first number in Input file or enter more numbers===";
		writeFile.close();
		readFile.close();
		return;
	}
	writeFile.close();
	readFile.close();
}

void main() {
	Question1();
	Question2();
	system("pause");
}