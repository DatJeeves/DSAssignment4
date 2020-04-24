#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>

using namespace std;

class Student {
public:
	Student();
	Student(int arTime, int trTime);
	~Student();

	int GetWaitTime();
	int GetArrivalTime();
	int IncrementWaitTime();
	int GetTransactionTime();
	int DecrementTransactionTime();



private:
	int arrivalTime;
	int waitTime;
	int transactionTime;
};
#endif
