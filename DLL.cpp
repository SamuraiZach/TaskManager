
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <stdlib.h>
using namespace std;


	DLL::DLL(){  // constructor - initializes an empty list
		last = NULL;
		first = NULL;
		numTasks = 0;
		tothrs = 0;
		totmin = 0;
	}
	DLL::DLL(string t, int p, int h, int m){  // constructor, initializes a list with one new node with data x
		DNode *n = new DNode (t,p,h,m);
		first = n;
		last = n;
		numTasks=1;
		tothrs = h;
		totmin = m;
	}
	/***************************************************************************************************/
	/*Part 1																																		*/
	/***************************************************************************************************/
	void DLL::push(string n, int p, int h, int m) {  
    // does what you'd think, with a caveat that if the
	//priority isn't 3, it will move the task up to the end of the set of tasks with that priority.
	//In other words, if the priority is 1, it will traverse the list in reverse order until it finds a
	//task with a priority of 1, and insert the new task between the last task with a priority of
	//1 and the first task with a priority of 2
	//it also updates the total time of the list
		DNode *newNode = new DNode(n,p,h,m);
		numTasks += 1;
		tothrs += h;
		totmin += m;
		DNode *temp;
		if(first == NULL){
			first = newNode;
		}
	    else if (first->task->priority > newNode->task->priority ) {
	        newNode->next = first;
	        newNode->next->prev = newNode;
	        first = newNode;
	    }
	    else {
	        temp = first;
	        while (temp->next != NULL && temp->next->task->priority <= newNode->task->priority){
	        	temp = temp->next;
	        }
	        newNode->next = temp->next;
	        if (temp->next != NULL){
	            newNode->next->prev = newNode;
	        }
	        temp->next = newNode;
	        newNode->prev = temp;
	    }

	}

	Task *DLL::pop() { 
	//does what you'd think - make sure to update the total time of the list.
	//Note -this isn’t all that necessary for this particular project, but I 
	//kinda had to make you write pop because it’s //fundamental to so much of 
	//linked list data type uses (e.g., stack, undo).
		DNode *temp = last;
		tothrs -= last->task->hr;
		totmin -= last->task->min;
		last = temp->prev;
		last->next = NULL;
		numTasks -= 1;
		return(temp->task);

	}

	void DLL::printList() {
		//prints out the entire list, along with the total time necessary to complete all tasks 
		//on the list
		DNode *temp = first;
		int hs = tothrs + totmin/60;
		int min =totmin - ((totmin/60)*60);
		cout << "Total Time Required:  "<<hs<<":"<< min << endl;
		while(temp != NULL){
			temp->task->printTask();
			temp = temp->next;
		}
	}

	void DLL::printList(int p) {
		//print out only all the tasks with a priority of p, along with the total time necessary
		//to complete the tasks with a priority of p
		DNode *temp = first;
		DNode *temp1 = first;
		int hs = 0;
		int ms = 0;
		while(temp != NULL){
			if(temp->task->priority == p){
				hs += temp->task->hr;
				ms += temp->task->min;
				temp = temp->next;
			}else{
				temp = temp->next;
			}
		}
		int hss = hs + ms/60;
		int msin =ms - ((ms/60)*60);
		cout << p<<": "<<"Total Time Required:  "<<hss<<":"<< msin << endl;
		while(temp1 != NULL){
			if(temp1->task->priority == p){
				temp1->task->printTask();
				temp1 = temp1->next;
			}else{
				temp1 = temp1->next;
			}
		}
	}

	void DLL::moveUp(int tn) {
		// moves task with number tn up one in the list.
	    //If it is at the beginning of the list,
        //it will be moved to the end of the list.
		// NOTE: if this moves a task up before a task with a higher priority (1 is
		// higher priority than 2 - I know the wording is a bit weird), then this
		// changes the priority of the task being moved to that higher priority
		DNode *temp = first;
		DNode *tempprev;
		DNode *tempnext;
		bool x = true;
		while(temp != NULL && x){
			if(temp->task->tasknum == tn){
				x = false;
				tempprev = temp->prev;
				tempnext = temp->next;
			}else{
				temp=temp->next;
			}
		}
		if(temp == first){
			first = first->next;
			first->prev = NULL;

			last->next = temp;
			temp->prev = last;
			last = last->next;
			last->next = NULL;
			last->task->priority = last->prev->task->priority;
		}else{
			temp->prev = tempprev->prev;
			temp->next = tempprev;
			temp->prev->next = temp;
			tempprev->prev = temp;
			tempprev->next = tempnext;
			tempnext->prev = tempprev;
			if(temp->next->task->priority < temp->task->priority && temp->prev->task->priority < temp->task->priority){
				temp->task->priority = temp->prev->task->priority;
			}
		}
	}

	void DLL::listDuration(int *th, int *tm,int tp) {
		// gets the list duration in hours and minutes (passed
		//in as pointers) of a particular priority (so the total time
		//needed to complete all tasks with priority of p)
		// I had you pass in the parameters as pointers for practice.
		DNode *temp = first;
		int hs = 0;
		int ms = 0;
		while(temp != NULL){
			if(temp->task->priority == tp){
				hs += temp->task->hr;
				ms += temp->task->min;
				temp = temp->next;
			}else{
				temp = temp->next;
			}
		}
		*th += hs + (ms/60);
		*tm += ms - ((ms/60)*60);
	}
	
	
	void DLL::moveDown(int tn) {
		//moves task with task number tn down one in the list.
		//If it is at the end of the list, it will move to
		//beginning of the list.
		//NOTE: if this moves a task after a task with a lower priority (again, 3 is
		//a lower priority than 2) then this changes the priority of the task being
		//moved.
		DNode *temp = first;
		DNode *tempprev;
		DNode *tempnext;
		bool x = true;
		while(temp != NULL && x){
			if(temp->task->tasknum == tn){
				x = false;
				tempprev = temp->prev;
				tempnext = temp->next;
			}else{
				temp=temp->next;
			}
		}
		if(temp == last){
			last=last->prev;
			last->next = NULL;

			first->prev = temp;
			temp->prev = NULL;
			temp->next = first;
			first = temp;
		}else{
			temp->next = tempnext->next;
			temp->prev = tempnext;
			temp->next->prev = temp;
			tempnext->next = temp;
			tempnext->prev = tempprev;
			tempprev->next = tempnext;
			if(temp->next->task->priority > temp->task->priority && temp->prev->task->priority > temp->task->priority){
				temp->task->priority = temp->prev->task->priority;
			}
		}
	}

	int DLL::remove(int tn) {
		//removes a task (based on its number) and updates the total time of the list
		//Make sure you link the next to the previous and the previous to the next.  The 
		//biggest catch with this method is making sure you test to make sure the node 
		//after and/or the node before the node you’re deleting aren’t NULL (i.e., you’re 
		//not deleting the first or last node in the list)
		DNode *temp = first;
		bool x = true;
		while(temp != NULL && x){
			if(temp->task->tasknum == tn){
				cout<<"Removing: ";
				temp->task->printTask();
				x = false;
				if(temp->next == NULL){
					last = temp;
				}
			}else{
				temp = temp->next;
			}
		}
		if(last == temp){
			tothrs -= temp->task->hr;
			totmin -= temp->task->min;
			last = temp->prev;
			last->next = NULL;
			temp->prev = NULL;
			numTasks -= 1;
		}else{
			tothrs -= temp->task->hr;
			totmin -= temp->task->min;
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			numTasks -= 1;
		}
		return temp->task->tasknum;
	}

	void DLL::changePriority(int tn, int newp) {
		//changes the priority of the task.  This method also moves the task to the end 
		//of the set of tasks with 
		//that priority.  In other words, if you have the following:
		/*task1, 1, 2:20
		task2, 1, 3:20
		task3, 1, 1:15
		task4, 2, 3:10
		task5, 2, 1:10
		task6, 3, 3:15
		task7, 3, 2:54

		And you change task6’s priority to 1, the resulting list should be:
		task1, 1, 2:20
		task2, 1, 3:20
		task3, 1, 1:15
		task6, 1, 3:15
		task4, 2, 3:10
		task5, 2, 1:10
		task7, 3, 2:54
		*/
		DNode *temp = first;
		bool firstloop = true;
		bool secondloop = true;
		string s;
		while(temp != NULL && firstloop){
			if(temp->task->tasknum == tn){
				firstloop = false;
			}else{
				temp = temp->next;
			}
		}
		if(temp->task->priority < newp){
			s = "down";
		}
		else if(temp->task->priority > newp){
			s = "up";
		}
		temp->task->priority = newp;
		while(secondloop){
			if(s == "up"){
				moveUp(temp->task->tasknum);
				if(temp->task->priority == temp->prev->task->priority){
					secondloop = false;
				}
			}else if(s == "down"){
				moveDown(temp->task->tasknum);
				if(temp->task->priority == temp->next->task->priority){
					secondloop = false;
				}
			}
		}
	}

	DLL::~DLL(){
		DNode *tmp = first;
		DNode *tmp2 = first->next;
		while (tmp != NULL) {
			delete tmp;
			tmp = tmp2;
			if (tmp != NULL) {
				tmp2 = tmp2->next;
			}
		}
		first = NULL;
		last = NULL;
		numTasks = 0;
		tothrs = 0;
		totmin = 0;
	}

	/******************Optional Helper Methods********************************/
	void DLL::addTime(int h, int m) {
	}

	void DLL::removeTime(int h, int m) {
	}
	/********************End of Optional Helper Methods ********************/
