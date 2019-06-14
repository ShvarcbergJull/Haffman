#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
	Node* left;
	Node* right;
	int weight;
	char symbol;

	Node()
	{
		left = right = NULL;
		weight = 0;
		symbol = 0;
	}

	Node(Node* l, Node* r)
	{
		left = l;
		right = r;
		weight = l->weight + r->weight;
		symbol = 0;
	}
};
