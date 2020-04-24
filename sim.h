#ifndef SIM_H
#define SIM_H
#include <iostream>
#include "student.h"
#include "window.h"

using namespace std;

class Sim {
public:
	Sim();
	~Sim();

	void Start(string filename);
	void SetUpSim(string file);

private:
	void ProcessTransactions();
	void ProcessIdle(int tickCount);
	void GenerateMetrics();
	float CalculateMedian();

	Queue<Student*> inlineStudents;
	Queue<Student*> processedStudents;
	Queue<Student*> atWindow;

	Queue<Window*> freeWindows;
	Queue<Window*> busyWindows;


	int numOfWindows;
};
#endif
