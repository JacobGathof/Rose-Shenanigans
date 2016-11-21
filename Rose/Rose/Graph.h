#pragma once
#include <vector>
#include <iostream>
#include "NPC.h"



class Graph
{
public:

	class Node {
	public:

		Node(std::string d, bool (*func)());
		std::string data;
		std::vector<Node*> nodes;
		bool (*condition)();
		void addNode(Node* n);
	};

	Node * currentNode;
	std::vector<Node*> allNodes;
	void update();
	void printData();
	void destroy();
	void connectNode(Node* n1, Node* n2);
	void addNode(Node * n);

	Graph();
	~Graph();

};

