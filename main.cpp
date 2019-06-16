#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <list>
#include "Archiver.h"

using namespace std;

int main(/*int argc, char** argv*/)
{
	setlocale(LC_ALL, "Russian");

	/*if (argc < 3)
	{
		cout << "Пример вызова программы: nameprogram.exe inFileName outFileName" << endl;
	}*/

	cout << "Welcome!" << endl;

	const char* inFileName = "out.txt"; // argv[1];
	const char* outFileName = "text_out.txt"; //argv[2];

	cout << "Если хотите архивировать введите coder, разархивировать - decoder: ";
	string action;
	getline(cin, action);

	if (action == "coder")
	{
		coder(inFileName, outFileName);
		cout << "Архивирование завершено" << endl;
	}
	else if (action == "decoder")
	{
		decoder(inFileName, outFileName);
		cout << "Разархивирование завершено" << endl;
	}
	else
		cout << "Вы неправильно ввели команду" << endl;

	system("pause");
	return 0;
}
