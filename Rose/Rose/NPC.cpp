#include "NPC.h"
#include <iostream>
#include "WorldManager.h"
#include "Info.h"


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
		move(Vector2f(1.0f * (position.x - endPoint.x < 0.0 ? 1 : -1), 0), dt);
		return false;
	}

	else if(abs(position.y - endPoint.y) > 1.0f){
		move(Vector2f(0, 1.0f * (position.y - endPoint.y < 0.0 ? 1 : -1)), dt);
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




Echo::Echo() : NPC(Vector2f(0, 100), Vector2f(32, 32), "Echo", 50)
{

	
	NPCAction* arr[] = {
		new NPCAction(WAIT), 
		new NPCAction(TALK, "Welcome to Avantheim!"),
		new NPCAction(WAIT_FOR_TEXTBOX),
		0
	};
	NPCActionList list = NPCActionList(arr);
	Graph::Node * node_1 = new Graph::Node(list, []() {return true; });


	NPCActionList list2 = NPCActionList();
	list2.addAction(new NPCAction(WAIT));
	list2.addAction(new NPCAction(TALK, "OH! You have the key! You may certainly pass now"));
	list2.addAction(new NPCAction(WAIT_FOR_TEXTBOX));
	Graph::Node * node_2 = new Graph::Node(list2, []() {return Info::x == 7; });


	NPCActionList list3 = NPCActionList();
	list3.addAction(new NPCAction(WAIT));
	list3.addAction(new NPCAction(TALK, "I cannot let you pass until you talk to the Flugel over there"));
	list3.addAction(new NPCAction(WAIT_FOR_TEXTBOX));
	Graph::Node * node_3 = new Graph::Node(list3, []() {return Info::x != 7; });


	NPCActionList list4 = NPCActionList();
	list4.addAction(new NPCAction(WAIT));
	list4.addAction(new NPCAction(TALK, "I already said you could pass. What's your problem?"));
	list4.addAction(new NPCAction(WAIT_FOR_TEXTBOX));
	Graph::Node * node_4 = new Graph::Node(list4, []() {return true; });


	actionGraph.connectNode(actionGraph.currentNode, node_1);
	actionGraph.connectNode(node_1, node_2);
	actionGraph.connectNode(node_1, node_3);

	actionGraph.connectNode(node_3, node_3);
	actionGraph.connectNode(node_3, node_2);

	actionGraph.connectNode(node_2, node_4);
	actionGraph.connectNode(node_4, node_4);

	actionGraph.addNode(node_1);
	actionGraph.addNode(node_2);
	actionGraph.addNode(node_3);
	actionGraph.addNode(node_4);
	
}

Jibril::Jibril() : NPC(Vector2f(-100, 100), Vector2f(32, 32), "Jibril", 50)
{
	NPCActionList list = NPCActionList();
	list.addAction(new NPCAction(WAIT));
	list.addAction(new NPCAction(TALK, "Hello Hero, what brings you here?"));
	list.addAction(new NPCAction(WAIT_FOR_TEXTBOX));

	list.addAction(new NPCAction(WAIT));
	list.addAction(new NPCAction(TALK, "Oh of course, here is the key."));
	list.addAction(new NPCAction(LAMBDA, []() {Info::x = 7; }));
	list.addAction(new NPCAction(WAIT_FOR_TEXTBOX));
	Graph::Node * node_1 = new Graph::Node(list, []() {return true; });


	NPCActionList list2 = NPCActionList();
	list2.addAction(new NPCAction(WAIT));
	list2.addAction(new NPCAction(TALK, "Please stop bothering me"));
	list2.addAction(new NPCAction(WAIT_FOR_TEXTBOX));
	Graph::Node * node_2 = new Graph::Node(list2, []() {return true; });

	actionGraph.connectNode(actionGraph.currentNode, node_1);
	actionGraph.connectNode(node_1, node_2);
	actionGraph.connectNode(node_2, node_2);

	actionGraph.addNode(node_1);
	actionGraph.addNode(node_2);


}
