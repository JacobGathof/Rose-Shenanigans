#include "NPC.h"
#include <iostream>
#include "WorldManager.h"


NPC::NPC(Vector2f pos, Vector2f scale, std::string texName, float speed) : Entity(pos, scale, texName, speed){
	name = "gary";
}

NPC::NPC()
{
}


NPC::~NPC(){
	for (auto a : actionGraph.allNodes) {
		for (auto b : a->data.actions) {
			delete b;
		}
	}
	actionGraph.destroy();
}

void NPC::update(float dt){

	if (!currentActionList.isEmpty()) {
		NPCAction * a = currentActionList.getAction();

		a->target = this;
		a->act(dt);
		if (a->finished) {
			currentActionList.advance();
		}
	}

	else {
		currentActionList.reset();
		actionGraph.update();
		currentActionList = actionGraph.getData();
	}

	triggered = false;

}

void NPC::tick(){

	Entity::tick();
}


void NPC::trigger(){
	triggered = true;
}

bool NPC::print(std::string str){

	UIManager::textbox.print(str);
	return true;
}

bool NPC::moveTo(Vector2f endPoint, float dt)
{

	if (abs(position.x - endPoint.x) > 1.0f) {
		move(Vector2f(1 * (position.x - endPoint.x < 0.0 ? 1 : -1), 0), dt);
		return false;
	}

	else if(abs(position.y - endPoint.y) > 1.0f){
		move(Vector2f(0, 1 * (position.y - endPoint.y < 0.0 ? 1 : -1)), dt);
		return false;
	}

	return true;

}

bool NPC::idle(){
	return triggered;
}

bool NPC::detectPlayer()
{
	return ((this->position^Res::player->position) <= 16.0f);
}

void NPC::interact(){
	print("We must save my family!");
}

void NPC::act(){

}

void NPC::addActionListToGraph(NPCActionList l, bool(*condition)()){

	//Graph<NPCActionList>::Node * node = new Graph<NPCActionList>::Node(l, condition);
	//actionGraph.addNode(node);

}

//void NPC::addNodeToGraph(Graph<NPCActionList>::Node n, bool(*condition)()){
	//actionGraph.addNode(n);
//}




Echo::Echo() : NPC(Vector2f(100, 100), Vector2f(32, 32), "Echo", 50)
{

	
	NPCActionList list = NPCActionList();
	list.addAction(new NPCAction(MOVE, Vector2f(0, 0)));
	list.addAction(new NPCAction(TALK, "Hello World"));
	list.addAction(new NPCAction(WAIT_FOR_TEXTBOX));
	Graph::Node * node_helloworld = new Graph::Node(list, []() {return true; });


	NPCActionList list2 = NPCActionList();
	list2.addAction(new NPCAction(TALK, "Goodbye Hero"));
	list2.addAction(new NPCAction(WAIT_FOR_TEXTBOX));
	Graph::Node * node_farewell = new Graph::Node(list2, []() {return true; });

	
	actionGraph.connectNode(actionGraph.currentNode, node_helloworld);
	actionGraph.connectNode(node_helloworld, node_farewell);
	actionGraph.connectNode(node_farewell, node_helloworld);

	actionGraph.addNode(node_helloworld);
	actionGraph.addNode(node_farewell);
	
}


