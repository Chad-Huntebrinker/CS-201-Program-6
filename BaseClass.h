
#ifndef SJF_HEADER
#define SJF_HEADER

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//This is the base class for the three types of classes (FIFO, SJF, and MLQ).
class BaseClass {
public:
	//constructor
	BaseClass() {
		timeArrived = 0;
		department = 'Z';
		numPages = 0;
		tickDone = 0;
		tickStarted = 0;
	}
	//constructor
	BaseClass(int userTimeArrived, char userDepartment, int userNumPages) {
		timeArrived = userTimeArrived;
		department = userDepartment;
		numPages = userNumPages;
		tickDone = 0;
		tickStarted = 0;
	}
	//setters
	void setTimeArrived(int userInput) { timeArrived = userInput; }
	void setDepartment(char userInput) { department = userInput; }
	void setNumPages(int userInput) { numPages = userInput; }
	void setTickStarted(int userInput) { tickStarted = userInput; }

	//This function calculates how long the job will take by taking the numPages and dividing that by
	//150 and adding 1 to that answer.  After that, the function rounds the decimal and keeps that in the
	//class variable called tickDone.
	void setTickDone() {
		double temp;
		temp = numPages;
		tickDone = round((temp / 150) + 1);

	}
	//getters
	int getTimeArrived() { return timeArrived; }
	char getDepartment() { return department; }
	int getNumPages() { return numPages; }
	int getTickDone() { return tickDone; }
	int getTickStarted() { return tickStarted; }

	//This function calculates when the job will be done by taking the tick when the job started (tickStarted)
	//and adding it to how long the job will take to get done (tickDone).
	int completionTime() {
		return tickStarted + tickDone;
	}
	//Abstract class for the child classes to change as they see fit.
	virtual void printQueue(bool& printerOpen, int currTick, vector<int>& summaryStat) = 0;

	//Vairables of the class.
protected:
	int timeArrived;
	char department;
	int numPages;
	int tickDone;
	int tickStarted;
};



#endif