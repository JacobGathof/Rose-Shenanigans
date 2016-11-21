#include "Graph.h"



void Graph::update(){

	for (auto n : currentNode->nodes) {
		if (n->condition()) {
			currentNode = n;
			return;
		}
	}
	std::cout << "Graph failure, no paths remain" << std::endl;

}

void Graph::printData()
{
	std::cout << currentNode->data << std::endl;
}

void Graph::destroy()
{
	for (auto n : allNodes) {
		delete n;
	}
}

void Graph::addNode(Node * n){
	allNodes.push_back(n);
}

void Graph::connectNode(Node * n1, Node * n2)
{
	n1->addNode(n2);
}

Graph::Graph(){
	Node * n = new Node("Beginning of Graph", []() {return true; });
	currentNode = n;
	allNodes.push_back(n);


}


Graph::~Graph()
{
}

Graph::Node::Node(std::string d, bool(*func)()){
	data = d;
	condition = func;

}

void Graph::Node::addNode(Node * n){
	nodes.push_back(n);
}
