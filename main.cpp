#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include "Archiver.h"

using namespace std;

int main()
{
	coder("text.txt", "out.txt");
	decoder("out.txt", "text_out.txt");

	system("pause");
	return 0;
}
