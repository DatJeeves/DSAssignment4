#include "student.h"

using namespace std;

Student::Student() {
	arrivalTime = 0;
	transactionTime = 0;
	waitTime = 0;
}

Student::Student(int arTime, int trTime) {
	arrivalTime = arTime;
	transactionTime = trTime;
	waitTime = 0;
}

int Student::GetTransactionTime() {
	return transactionTime;
}

int Student::GetArrivalTime() {
	return arrivalTime;
}

int Student::GetWaitTime() {
	return waitTime;
}

int Student::IncrementWaitTime() {
	++waitTime;
}

int Student::DecrementTransactionTime() {
	--transactionTime;
}

Student::~Student() {
	delete this;
}

