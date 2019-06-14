#pragma once
#include <map>
#include "Node.h"
#include "SortFunct.h"

map<char, int> numb_charact;
char sym;
Node* root;

void createTree(ifstream& in)
{
	sym = in.get();
	while (!in.eof())
	{
		numb_charact[sym]++;
		sym = in.get();
	}

	list<Node*> heap_nodes;

	for (map<char, int>::iterator it = numb_charact.begin(); it != numb_charact.end(); it++)
	{
		Node* pnode = new Node;
		pnode->symbol = it->first;
		pnode->weight = it->second;
		heap_nodes.push_back(pnode);
	}

	while (heap_nodes.size() != 1)
	{
		heap_nodes.sort(SortFunct());
		Node* left_sun = heap_nodes.front();
		heap_nodes.pop_front();
		Node* right_sun = heap_nodes.front();
		heap_nodes.pop_front();

		Node* parent = new Node(left_sun, right_sun);
		heap_nodes.push_back(parent);
	}

	root = heap_nodes.front();

	way(root);
}

void coder(const char* inFileName, const char* outFileName)
{
	ifstream in(inFileName, ios::binary);
	createTree(in);
	in.clear();
	in.seekg(0);
	ofstream filezip(outFileName, ios::binary);// закодированные данные
	int count = 0;//счётчик бит
	char buf = 0;

	sym = in.get();
	while (!in.eof())
	{
		vector<bool> x = table[sym];
		for (int i = 0; i < x.size(); i++)
		{
			buf = buf | x[i] << (7 - count);
			count++;
			if (count == 8)
			{
				count = 0;
				filezip << buf;
				buf = 0;
			}
		}
		sym = in.get();
	}

	if (count != 0)
	{
		filezip << buf;
	}

	in.close();
	filezip.close();
}

void decoder(const char* inFileName, const char* outFileName)
{
	ifstream in(inFileName, ios::binary);
	ofstream out(outFileName, ios::binary);

	Node* pos = root;
	int count = 0;
	char byte = in.get();
	while (!in.eof())
	{
		bool b = byte & (1 << (7 - count));
		if (b == 1)
			pos = pos->right;
		else
			pos = pos->left;

		if (pos->left == NULL && pos->right == NULL)
		{
			out << pos->symbol;
			pos = root;
		}

		count++;
		if (count == 8)
		{
			count = 0;
			byte = in.get();
		}
	}

	in.close();
	out.close();
}
