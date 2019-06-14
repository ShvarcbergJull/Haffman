#pragma once
#include "Node.h"

vector<bool> code;
map<char, vector<bool>> table;

struct SortFunct
{
	bool operator()(Node* l, Node* r)
	{
		return l < r;
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
