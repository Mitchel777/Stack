#pragma once
#include <iostream>
#include <string>
using namespace std;
class Stack
{
public:
	Stack();
	~Stack();
	void Insert(string& substr);
	void Print();
	void Undo();
	void Redo();
	void Delete(int number);
	void Help();
	void StringParse(string& str, string& substr1, string& substr2);
	
private:
	string str;
	int capacity_undo;
	int size_undo;
	string* pUndo;
	int growFactor;
	int capacity_redo;
	int size_redo;
	string* pRedo;
	bool isTheLastCommandUndo;
	int undoCount;
	
	void Error(int numberOfError);
	void ResizeUndo();
	void ResizeRedo();
};