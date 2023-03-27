#include "Stack.h"
Stack::Stack()
{
	str = "";
	growFactor = 2;
	capacity_undo = 2;
	size_undo = 0;
	capacity_redo = 2;
	size_redo = 0;
	pUndo = new string[capacity_undo];
	pRedo = new string[capacity_redo];	
	pUndo[size_undo++] = str;
	isTheLastCommandUndo = false;
	undoCount = 0;
}

Stack::~Stack()
{
	delete[] pUndo;
	delete[] pRedo;
}

void Stack::StringParse(string& str, string& substr1, string& substr2)
{
	int i = 0;
	string substring1 = "";
	string substring2 = "";
	while (str[i] != ' ' && i != str.size())
		substring1 += str[i++];
	i++;
	while (i <= str.size() - 1)
		substring2 += str[i++];
	substr1 = substring1;
	substr2 = substring2;
}

void Stack::Insert(string& substr)
{
	str += substr;
	pUndo[size_undo++] = str;
	if (size_undo == capacity_undo)
		ResizeUndo();
	isTheLastCommandUndo = false;
	undoCount = 0;
	size_redo = 0;
}

void Stack::Print()
{
	cout << "���� ������: " << str << endl;
}

void Stack::Delete(int number)
{
	if (str.size() < number)
		Error(1);
	else 
	{
		str.erase(str.size() - number, str.size());
		pUndo[size_undo++] = str;
		if (size_undo == capacity_undo)
			ResizeUndo();
		isTheLastCommandUndo = false;
		undoCount = 0;
		size_redo = 0;
	}
	
}

void Stack::ResizeUndo()
{
	capacity_undo *= growFactor;
	//int sizeInBytes = sizeof(string);
	string* newpUndo = new string[capacity_undo];
	//memcpy_s(newpDo, sizeInBytes, pUndo, sizeInBytes);
	for (int i = 0; i < size_undo; i++)
		newpUndo[i] = pUndo[i];
	delete[] pUndo;
	pUndo = newpUndo;
}

void Stack::ResizeRedo()
{
	capacity_redo *= growFactor;
	//int sizeInBytes = sizeof(string);
	string* newpRedo = new string[capacity_redo];
	//memcpy_s(newpDo, sizeInBytes, pUndo, sizeInBytes);
	for (int i = 0; i < size_redo; i++)
		newpRedo[i] = pRedo[i];
	delete[] pRedo;
	pRedo = newpRedo;
}

void Stack::Undo()
{
	if (size_undo == 1)
		Error(2);
	else 
	{
		pRedo[size_redo++] = str;
		if (size_redo == capacity_redo)
			ResizeRedo();

		str = pUndo[(--size_undo) - 1];
		
		isTheLastCommandUndo = true;
		undoCount++;
	}
}

void Stack::Error(int numberOfError)
{
	setlocale(LC_ALL, "ru");
	if (numberOfError == 1)
		cout << "� ����� ������ ������ �������, ��� �� ������ �������" << endl;
	else if (numberOfError == 2)
		cout << "�� ��������� � ������������ �������� ����� ������" << endl;
	else
		cout << "� ��� ������ ��� ���������� ��������" << endl;
}

void Stack::Redo()
{
	if (isTheLastCommandUndo && undoCount > 0)
	{
		str = pRedo[(--size_redo)];

		pUndo[size_undo++] = str;
		if (size_undo == capacity_undo)
			ResizeUndo();
		undoCount--;
	}
	else
		Error(3);
}

void Stack::Help()
{
	setlocale(LC_ALL, "ru");
	cout << "������ ������� ����������. ��� ���������� ������" << endl;
	cout << "INSERT\t\t�������� ���-�� � ������" << endl;
	cout << "DELETE\t\t������� n-�� ���������� �������� �� ������" << endl;
	cout << "PRINT\t\t������� ������ ������" << endl;
	cout << "UNDO\t\t�������� ��������� ��������" << endl;
	cout << "REDO\t\t�������� ������ ���������� ��������" << endl;
	cout << "BREAK\t\t��������� ���������" << endl;
}