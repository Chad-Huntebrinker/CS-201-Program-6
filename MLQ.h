#include "BaseClass.h"


class MLQ : public BaseClass {

public:
	//This function calculates what to do when a job comes. If the printer isn't open and the 
	//completion time is equal to the current tick, then that job is done.  Once a job is done,
	// the printerOpen variable is now true (or the printer is now open) and the function figures
	//out which department it is from (Administation, Faculty, or Student) and
	//adds 1 to the completion of that type of job.  If that printer is open, then it figures out what
	//department the job is from.  It then sees how long the job has waited and adds that to the summaryStat
	//vector.  If the job has waited the longest out of the departement, then it is now the new longest wait
	//for that departement.  Finally, it then sets at what tick the job started using the setTickStarted function.
	void printQueue(bool& printerOpen, int currTick, vector<int>& summaryStat) {

		if (printerOpen == false && completionTime() == currTick) {
			printerOpen = true;
			if (department == 'A') {
				++summaryStat.at(0);
			}
			else if (department == 'F') {
				++summaryStat.at(3);
			}
			else {
				++summaryStat.at(6);
			}
		}

		else if (printerOpen == true) {

			if (department == 'A') {
				summaryStat.at(2) = currTick - timeArrived + summaryStat.at(2);
				if (currTick - timeArrived > summaryStat.at(1)) {
					summaryStat.at(1) = currTick - timeArrived;
				}
			}

			else if (department == 'F') {
				summaryStat.at(5) = currTick - timeArrived + summaryStat.at(5);
				if (currTick - timeArrived > summaryStat.at(4)) {
					summaryStat.at(4) = currTick - timeArrived;
				}
			}

			else {
				summaryStat.at(8) = currTick - timeArrived + summaryStat.at(8);
				if (currTick - timeArrived > summaryStat.at(7)) {
					summaryStat.at(7) = currTick - timeArrived;
				}
			}
			printerOpen = false;
			setTickStarted(currTick);
		}
	}


};
