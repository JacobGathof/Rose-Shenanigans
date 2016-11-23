#pragma once
#include <vector>
#include <iostream>
#include "NPCAction.h"


class Graph
{
public:

	class Node {
	public:

		Node(NPCActionList data, bool(*func)()) : data(data), condition(func) {};
		NPCActionList data;
		std::vector<Node*> nodes;
		bool (*condition)();
		void addNode(Node* n) {
			nodes.push_back(n);
		};
	};


	Node* currentNode;
	std::vector<Node*> allNodes;

	void update() {
		for (auto n : currentNode->nodes) {
			if (n->condition()) {
				currentNode = n;
				return;
			}
		}
		currentNode = 0;
	}

	NPCActionList getData() {
		return currentNode->data; 
	}

	void destroy() {
		for (auto n : allNodes) {
			delete n;
		}
	}

	void connectNode(Node* n1, Node* n2) {
		n1->addNode(n2);
	}

	void addNode(Node * n) {
		allNodes.push_back(n);
	}

	Graph() {
		Node * n = new Node(NPCActionList(), []() {return true; });
		currentNode = n;
		allNodes.push_back(n);
	}

	~Graph() {
	};

};

