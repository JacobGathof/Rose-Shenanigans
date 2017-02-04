#pragma once
#include <vector>
#include <iostream>
#include "Task.h"


class Graph{

public:
	
	
	std::vector<TaskList> data;

	void addTaskList(TaskList t) {
		data.push_back(t);
	};

	int currentIndex = 0;

	void update() {

		int nextIndex = data[currentIndex].nextIndex;
		currentIndex = nextIndex;

	}

	TaskList getData() {
		return data[currentIndex]; 
	}

	void destroy() {
		for (auto t : data) {
			for (auto task : t.actions) {
				delete task;
			}
		}
	}


	Graph() {
		data.push_back(TaskList());
	}

	~Graph() {
	};
	
};

