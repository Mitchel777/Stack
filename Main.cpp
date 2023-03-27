#include "Stack.h"
#include <iostream>
#include <string>
using namespace std;
int main()
{
    setlocale(LC_ALL, "ru");
    string str;
    string substr1;
    string substr2;
    Stack a;
    while (true)
    {
        getline(cin, str);
        a.StringParse(str, substr1, substr2);
        if (substr1 == "insert")
            a.Insert(substr2);
        else if (substr1 == "print")
            a.Print();
        else if (substr1 == "delete")
            a.Delete(stoi(substr2));
        else if (substr1 == "undo")
            a.Undo();
        else if (substr1 == "redo")
            a.Redo();
        else if (substr1 == "break")
            break;
        else
            a.Help();
    }
    return 0;
}
