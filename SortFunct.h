#pragma once
#include "Node.h"

vector<bool> code;
map<char, vector<bool>> table;
int sizeALF;
int countBit;
char bufTree;
int countSymTree;
list<char> temp;
list<bool> bits;

struct SortFunct
{
	bool operator()(Node* l, Node* r)
	{
		return l->weight < r->weight;
	}
};

void way(Node* root)
{
	if (root->left != NULL)
	{
		code.push_back(0);
		way(root->left);
	}

	if (root->right != NULL)
	{
		code.push_back(1);
		way(root->right);
	}

	if (root->left == NULL && root->right == NULL)
		table[root->symbol] = code;
	if (code.size() != 0)
		code.pop_back();
}

string& operator <<(string& out, char& buf)
{
	out += buf;
	return out;
}

void writeInFile(ostream& out, Node* nd) // запись в файл дерева
 {
	if (countBit == 8)
	{
		countBit = 0;
		out << bufTree;
		bufTree = 0;
	}
	if (nd->left != NULL)
	{
		bufTree = bufTree | 0 << (7 - countBit);
		countBit++;
		writeInFile(out, nd->left);
	}
	if (nd->right != NULL)
	{
		bufTree = bufTree | 0 << (7 - countBit);
		countBit++;
		writeInFile(out, nd->right);
	}
	if (nd->left == NULL && nd->right == NULL)
	{
		bufTree = bufTree | 1 << (7 - countBit);
		countBit++;
		if (countBit == 8)
		{
			countBit = 0;
			out << bufTree;
			bufTree = 0;
		}
		temp.push_back(nd->symbol);
	}
}

void Tree(Node*& root)
{
	bool b = bits.front();
	bits.pop_front();
	if (b == 1)
	{
		root->symbol = temp.front();
		temp.pop_front();
		return;
	}
	if (root->left == NULL)
	{
		Node* left = new Node;
		root->left = left;
		Tree(root->left);
		b = bits.front();
		bits.pop_front();
	}
	if (b == 1)
	{
		Node* right = new Node;
		root->right = right;
		root->right->symbol = temp.front();
		temp.pop_front();
		return;
	}
	if (root->right == NULL)
	{
		Node* right = new Node;
		root->right = right;
		Tree(root->right);
	}
}

Node* readToFile(istream& in) // чтения дерева из файла
{
	char symbol = in.get();
	while (symbol != '|')
	{
		countSymTree = countSymTree * 10 + (symbol - '0');
		symbol = in.get();
	}

	symbol = in.get();
	int i = 0;
	while (i != countSymTree)
	{
		bool b = symbol & (1 << (7 - countBit));
		bits.push_back(b);
		countBit++;
		
		if (b == 1)
			i++;
		if (countBit == 8)
		{
			symbol = in.get();
			countBit = 0;
		}
	}

	i = 0;
	if (countBit == 0)
	{
		temp.push_back(symbol);
		i++;
	}
	while (i != countSymTree)
	{
		symbol = in.get();
		temp.push_back(symbol);
		i++;
	}

	Node* root = new Node;
	Tree(root);

	return root;
}

ostream& operator <<(ostream& out, list<char>& tr)
{
	while (tr.size() != 0)
	{
		out << tr.front();
		tr.pop_front();
	}

	return out;
}

int len(int n) // узнаём длину интового числа
{
	int i = 0;
	while (n != 0)
	{
		i++;
		n /= 10;
	}
	return i;
}

char* trans(int n) // перевод из int в char
{
	int m = len(n);
	char* ans = new char[m];
	ans[m] = 0;
	int j = m - 1;
	while (n != 0)
	{
		int i = n % 10;
		ans[j] = i + '0';
		j--;
		n /= 10;
	}

	return ans;
}

char* trans(string str)
{
	char* out = new char[str.size()];
	out[str.size()] = 0;

	for (int i = 0; i < str.size(); i++)
	{
		out[i] = str[i];
	}

	return out;
}
