#include "NPC.h"
#include <iostream>
#include "WorldManager.h"
#include "UI_Manager.h"
#include "Info.h"
#include <sstream>


NPC::NPC(Vector2f pos, Vector2f scale, TextureName texName, float speed) : Entity(pos, scale, texName, speed){
	name = "";
}

NPC::NPC()
{
}


NPC::~NPC(){
	
	tempGraphName.destroy();
}

void NPC::update(float dt){

	/*
	if (!currentTaskList.isFinished()) {
		Task * t = currentTaskList.getAction();

		t->target = this;
		t->act(dt);
		if (t->finished) {
			currentTaskList.advance();
		}
	}

	else {
		currentTaskList.reset();
		tempGraphName.update();
		currentTaskList = tempGraphName.getData();
	}
	*/
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

bool NPC::moveTo(Vector2f endPoint, float dt){

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

void NPC::addActionListToGraph(TaskList l, bool(*condition)()){

	//Graph<NPCActionList>::Node * node = new Graph<NPCActionList>::Node(l, condition);
	//actionGraph.addNode(node);

}

void NPC::parseScriptFile(std::string filename){

	std::cout << "Loading " << name << std::endl;

	std::ifstream file;
	file.open(filename, file.in);

	char lineBuffer[65536];
	char b1[1];


	std::stringstream line;

	while (!file.eof()) {

		file.getline(lineBuffer, 65536);

		line << lineBuffer;
		//std::cout << line.str();

	
		line.getline(b1, 1);


		if (b1[0] == '\0') {
			continue;
		}

		if (b1[0] == '#') {

		}

		/*
		while (!line.eof()) {

			line.getline(buffer, 4, ',');
			if (buffer[0] == '\0') continue;
			int t = std::stoi(&buffer[0]);
			tileTextures[ptr++] = t;
		}
		*/
		line.str("");

	}
	std::cout << "Loaded " << name << std::endl;

}

//void NPC::addNodeToGraph(Graph<NPCActionList>::Node n, bool(*condition)()){
	//actionGraph.addNode(n);
//}




Echo::Echo() : NPC(Vector2f(0, 100), Vector2f(32, 32), TextureName::Echo_Tex, 50){


	Task* arr[] = {
		new Task(WAIT), 
		new Task(TALK, "Welcome to Avantheim!"),
		new Task(WAIT_FOR_TEXTBOX),
		0
	};

	Task * arr0[] = {
		new Task(TALK,"Hello Adventurer, Welcome to the town of Astraeus"),
		new Task(TALK,"My name is Echo, who are you?"),
		new Task(TALK,"That's fine, you don't need to answer."),
		0 };

	//Graph::Node * node_1 = new Graph::Node(arr, []() {return true; });

	/*
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
	list4.addAction(new NPCAction(TALK, "I already said you could pass. What's your problem"));
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
	*/

}

Jibril::Jibril() : NPC(Vector2f(-100, 100), Vector2f(32, 32), TextureName::Jibril_Tex, 50)
{
	/*
	NPCActionList list = NPCActionList();
	list.addAction(new NPCAction(WAIT));
	list.addAction(new NPCAction(TALK, "Hello Hero, what brings you here"));
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
	*/

}
