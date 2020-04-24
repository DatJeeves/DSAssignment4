#ifndef WINDOW_H
#define WINDOW_H
#include <iostream>
#include "student.h"

using namespace std;

class Window {
public:
	Window();
	~Window();

	bool isFree();
	void incrementIdle();
	int  GetTimeToComplete();
	void SetProcessTime(int prTime);
	void ProcessStudent();
	int  GetIdleTime();

private:
	int timeToCompleteTransaction;
	int idleTime;
};
#endif
