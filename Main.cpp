//Chad Huntebrinker
//12567690
//CS 201R
//*See thoughts on result in document title "Conclusion and Recommendation"*

#include <iostream>
#include <iomanip>
#include "FIFO.h"
#include "SJF.h"
#include "MLQ.h"
#include <vector>
#include <fstream>

using namespace std;

void statOutput(vector<int> stat);
vector<SJF> sortSJFVector(vector<SJF> vector);
vector<MLQ> sortMLQVector(vector<MLQ> vector);

template<typename printType>
void startJob(vector<printType> &queueList, vector<int> &sumOfStat, int currTick, bool &printerOpen);

template<typename theType>
vector<theType> fileInfo(vector<theType> userVector);

template<typename theType>
void transferListInfo(vector<theType>& origList, vector<theType> &queueList, int currTick);


int main() {
	vector<FIFO> origList1, queueList1;
	vector<SJF> origList2, queueList2;
	vector<MLQ> origList3, queueList3;
	vector<int> sumOfStat = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int currTick = 0;
	bool printerOpen = true;
	
	//These three functions get the information from the file and put it in the vector of each type (FIFO,
	// SJF, and MLQ).
	origList1 = fileInfo(origList1);
	origList2 = fileInfo(origList2);
	origList3 = fileInfo(origList3);

	//This for loop is for the First-In, First Out (FIFO) type of printing.  It is worth noting that
	//even if a job gets done at some tick and the printer is open, a new job will NOT take it's place
	//right away.  This is to take in consideration for possible scenarios that arrise when printing
	//a new job (like putting in new paper, printer running out of ink, bad connection to the printer or
	//the printer gets jammed, etc.)
	for (currTick = 0; origList1.size() == queueList1.size() == 0; ++currTick) {
		transferListInfo(origList1, queueList1, currTick);

		startJob(queueList1, sumOfStat, currTick, printerOpen);
	}
	cout << "First-In, First-Out Stats:" << endl;
	cout << setw(26) << setfill('=') << "" << endl;
	cout << setfill(' ');
	statOutput(sumOfStat);
	cout << "Final tick when all jobs are done: " << currTick << endl << endl << endl;

	printerOpen = true;
	sumOfStat = { 0,0,0,0,0,0,0,0,0 };

	//This for loop is for the Shortes Job First (SJF) type of printing. It's the same as
	//the FIFO loop, but there is a sorting function that is used whenever the queueList vector
	//of the type SJF has elements in it.
	for (currTick = 0; origList2.size() == queueList2.size() == 0; ++currTick) {
		transferListInfo(origList2, queueList2, currTick);
		
		if (queueList2.size() != 0) {
			queueList2 = sortSJFVector(queueList2);
		}

		startJob(queueList2, sumOfStat, currTick, printerOpen);
	}
	cout << "Shortest Job First Stats:" << endl;
	cout << setw(24) << setfill('=') << "" << endl;
	cout << setfill(' ');
	statOutput(sumOfStat);
	cout << "Final tick when all jobs are done: " << currTick << endl << endl << endl;

	printerOpen = true;
	sumOfStat = { 0,0,0,0,0,0,0,0,0 };

	//This for loop is for the Multi-Level Queue (MLQ) type of printing. It's the same as the
	//FIFO loop, but there is a sorting function that is used whenever the queueList vector of
	//the type MLQ has elements in it.
	for (currTick = 0; origList3.size() == queueList3.size() == 0; ++currTick) {
		transferListInfo(origList3, queueList3, currTick);
		
		if (queueList3.size() != 0) {
			queueList3 = sortMLQVector(queueList3);
		}

		startJob(queueList3, sumOfStat, currTick, printerOpen);
	}
	cout << "Multi-Level Queue Stats:" << endl;
	cout << setw(23) << setfill('=') << "" << endl;
	cout << setfill(' ');
	statOutput(sumOfStat);
	cout << "Final tick when all jobs are done: " << currTick << endl << endl << endl;

	return 0;
}

//This function reports the statistics for the three types of jobs (Amdinistation, faculty, and student).
void statOutput(vector<int> stat) {
	cout << "ADMINISTRATION STATISTICS:" << endl;
	cout << "Administration jobs completed: " << stat.at(0) << endl;
	cout << "Longest wait for Administation jobs: " << stat.at(1) << endl;
	cout << "Total waiting time for Administation jobs: " << stat.at(2) << endl << endl;

	cout << "FACULTY STATISTICS: " << endl;
	cout << "Faculty jobs completed: " << stat.at(3) << endl;
	cout << "Longest wait for Faculty Jobs: " << stat.at(4) << endl;
	cout << "Total waiting time for Faculty jobs: " << stat.at(5) << endl << endl;

	cout << "STUDENT STATISTICS: " << endl;
	cout << "Student jobs completed: " << stat.at(6) << endl;
	cout << "Longest wait for Student Jobs: " << stat.at(7) << endl;
	cout << "Total waiting time for Student Jobs: " << stat.at(8) << endl << endl;
}

//This function reads in the information from the file and stores it in the userVector.
//Once everything is read from the file, the userVector is returned to the main program.
//Because it is a template, all three types (FIFO, SJF, and MLQ) use this function.
template<typename theType>
vector<theType> fileInfo(vector<theType> userVector) {
	int numPages, tickArrived;
	char department;
	theType temp;
	ifstream fin;
	fin.open("Program6Data.txt");

	while (fin >> tickArrived) {
		fin >> department >> numPages;
		temp.setTimeArrived(tickArrived);
		temp.setDepartment(department);
		temp.setNumPages(numPages);
		temp.setTickDone();
		userVector.push_back(temp);
	}
	fin.close();
	return userVector;
}

//This function transfers the print jobs from the origList vector to the queueList vector when
//the job "arrives" to the print shop (or when the current tick matches the arrival time of the job).
//Because this function is a template, all three types use this function.
template<typename theType>
void transferListInfo(vector<theType>& origList, vector<theType> &queueList, int currTick) {
	theType temp;
	do {
		if (origList.size() != 0 && origList.front().getTimeArrived() == currTick) {
			temp = origList.front();
			queueList.push_back(temp);
			origList.erase(origList.begin());
		}
	} while (origList.size() != 0 && origList.front().getTimeArrived() == currTick);
}

//This function decides what to do with the vector queueList. If queueList has elements in it, then three
//things can happen.  First, the queueList will have the variable temp be the first element in the vector and
//temp will then start the printQueue function.  Depending on what type temp is (FIFO, SJF, MLQ) will decide
//what type of printQueue to do.  Second, if the front element has the constructor's value for the
//class variable tickStarted (that is, tickStarted = 0), then the first element will be temp which has the 
//updated version of tickStarted. Finally, if the first element (or temp) is at the completionTick (the tick
//when the job is considered done), the function erases the first element from the queueList vector.  After
//all this is checked, then the function is over. This function is used by all three types.
template<typename printType>
void startJob(vector<printType> &queueList, vector<int> &sumOfStat, int currTick, bool& printerOpen) {
	printType temp;

		if (queueList.size() != 0) {
			temp = queueList.front();
			temp.printQueue(printerOpen, currTick, sumOfStat);

			if (queueList.front().getTickStarted() == 0) {
				queueList.front() = temp;
			}

			if (temp.completionTime() == currTick) {
				queueList.erase(queueList.begin());
			}
		}
}

//This function sorts the SJF type of vector by the shortest job. Shorter jobs are closer to
//the front of the vector and longer jobs are closer to the back.
vector<SJF> sortSJFVector(vector<SJF> userVector) {
	int i, j;
	SJF temp;

	for (i = 1; i < userVector.size(); ++i) {
		j = i;
		while (j > 0 && userVector.at(j).getTickDone() < userVector.at(j - 1).getTickDone() &&
			userVector.at(j - 1).getTickStarted() == 0) {
			temp = userVector.at(j);
			userVector.at(j) = userVector.at(j - 1);
			userVector.at(j - 1) = temp;
			--j;
		}
	}
	return userVector;
}

//This function sorts the MLQ type of vector by the department where the job comes from.
//Administation jobs are closer to the front, Faculty is near the middle, and Student is near the back.
vector<MLQ> sortMLQVector(vector<MLQ> userVector) {
	int i, j;
	MLQ temp;

	for (i = 1; i < userVector.size(); ++i) {
		j = i;
		while (j > 0 && userVector.at(j).getDepartment() < userVector.at(j - 1).getDepartment() &&
			userVector.at(j - 1).getTickStarted() == 0) {
			temp = userVector.at(j);
			userVector.at(j) = userVector.at(j - 1);
			userVector.at(j - 1) = temp;
			--j;
		}
	}
	return userVector;
}


