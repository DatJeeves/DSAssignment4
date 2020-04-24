#include "sim.h"
#include <fstream>

using namespace std;

Sim::Sim() {

}

void Sim::SetUpSim(string file) {

		ifstream stream;
		stream.open(file, ios::in);

		if (!stream) {
			cout << "The file " << file << " had an issue." << endl;
			cout << "File Stream is not good, please check the file and try again." << endl;
			exit(1);
		}

		//obtained from: https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c
		else if (stream.peek() == std::ifstream::traits_type::eof()) {
			cout << "Your file " << file << " is empty, please enter a valid file." << endl;
			exit(1);
		}
		
		string line;
		cout << endl << "SETTING UP SIMULATION" << endl;
		//Gets windows
		stream >> numOfWindows;
		cout << "You will have " << numOfWindows << " windows to process students. " << endl;

		for (int i = 0; i < numOfWindows; ++i) {
			freeWindows.Enqueue(new Window());
		}
		
		int arTime;
		int trTime;
		int numStudents;
		
		// Read in the file which has the following format:
		// 1. The arrival time (or tick) the students will join the queue
		// 2. The number of Students at that time which will arrive
		// 3. The time it will take to process that student

		while (stream >> arTime) {

			stream >> numStudents;

			cout << "At tick: " << arTime << " , The Num of students arriving is  " << numStudents << endl;
			for (int i = 0; i < numStudents; ++i) {
				stream >> trTime;
				cout <<  "   - Student " << (i+1) << " has transaction time of " << trTime << endl;

				// Add students to the Queue in arrival time order
				inlineStudents.Enqueue(new Student(arTime, trTime));
			}
		}

		cout << "End of set up please get ready  for the simulation." << endl << endl;
}

void Sim::ProcessTransactions() {

	int sizeOfList = atWindow.Size();
	Student* popStudent;

	for (int i = 0; i < sizeOfList; ++i) {
		popStudent = atWindow.Dequeue();
		if (popStudent->GetTransactionTime() != 0) {
			popStudent->DecrementTransactionTime();
			atWindow.Enqueue(popStudent);
		}
		else {
			processedStudents.Enqueue(popStudent);
			freeWindows.Enqueue(busyWindows.Dequeue());
		}
	}
}

void Sim::ProcessIdle(int tickCount) {

	int sizeOfList = inlineStudents.Size();
	Student* popStudent;

	for (int i = 0; i < sizeOfList; ++i) {
		popStudent = inlineStudents.Dequeue();
		if (popStudent->GetWaitTime() < tickCount) {
			popStudent->IncrementWaitTime();
		}
		inlineStudents.Enqueue(popStudent);		
	}

	sizeOfList = freeWindows.Size();
	Window* popWindow;

	for (int i = 0; i < sizeOfList; ++i) {
		popWindow = freeWindows.Dequeue();
		popWindow->incrementIdle();
		freeWindows.Enqueue(popWindow);
	}
}

float Sim::CalculateMedian() {
	int sizeOfList = processedStudents.Size();
	int tempArray[sizeOfList];

	// Populate tempary Array
	Student* popStudent;
	for (int i = 0; i < sizeOfList; ++i) {
		popStudent = processedStudents.Dequeue();
		tempArray[i] = popStudent->GetWaitTime();
		processedStudents.Enqueue(popStudent);
	}

	int tempValue;
	// Sort array in ascending order
	for (int i = 0; i < sizeOfList; ++i)
	{
		// Check the neighbor value
		for (int j = i + 1; j < sizeOfList; ++j)
		{
			if (tempArray[i] > tempArray[j])
			{
				// Swap values
				tempValue = tempArray[i];
				tempArray[i] = tempArray[j];
				tempArray[j] = tempValue;
			}
		}
	}

	//Calculates the median which is the middle number
	float median = 0.0;
	if (sizeOfList % 2 != 0) {
		// We can take the middle number of an odd list so
		median = (float)tempArray[sizeOfList / 2];
	}
	else {
		// Need to get the average number of two middle numbers
		float n1, n2;
		n1 = tempArray[(sizeOfList - 1) / 2];
		n2 = tempArray[sizeOfList / 2];

		median = ((n1+n2) / 2);
	}

	return median;
}

void Sim::GenerateMetrics() {
	cout << endl << "==================================" << endl;
	cout << "Your final metrics" << endl;

	int sizeOfList = processedStudents.Size();
	int maxIdleTime = 0;
	int tempTimeCount = 0;
	float sum = 0;

	Student* popStudent;

	for (int i = 0; i < sizeOfList; ++i) {
		popStudent = processedStudents.Dequeue();

		//cout << "Student-" << i << " wait time was " << popStudent->waitTime << endl;
		sum += popStudent->GetWaitTime();
		if (popStudent->GetWaitTime() > 10) {
			++tempTimeCount;
		}

		if (maxIdleTime < popStudent->GetWaitTime()) {
			maxIdleTime = popStudent->GetWaitTime();
		}
		processedStudents.Enqueue(popStudent);
	}

	cout << "1. The mean student wait time is " << (sum/ sizeOfList) << endl;
	cout << "2. The median student wait time is " << CalculateMedian() << endl;
	cout << "3. The longest student wait time is " << maxIdleTime << endl;
	cout << "4. The number of students waiting over 10 minutes is " << tempTimeCount << endl;

	

	sizeOfList = freeWindows.Size();
	maxIdleTime = 0;
	tempTimeCount = 0;
	sum = 0;

	Window* popWindow;

	for (int i = 0; i < sizeOfList; ++i) {
		popWindow = freeWindows.Dequeue();

		//cout << "Window-" << i << " idle time was " << popWindow->GetIdleTime() << endl;
		sum += popWindow->GetIdleTime();
		if (popWindow->GetIdleTime() > 5) {
			++tempTimeCount;
		}
		if (maxIdleTime < popWindow->GetIdleTime()) {
			maxIdleTime = popWindow->GetIdleTime();
		}
		freeWindows.Enqueue(popWindow);
	}
	cout << "5. The mean window idle time is " << (sum / sizeOfList) << endl;
	cout << "6. The longest window idle time is " << maxIdleTime << endl;
	cout << "7. The number of window waiting over 5 minutes is " << tempTimeCount << endl;
	cout << "==================================" << endl << endl;
}

void Sim::Start(string filename) {
	cout << endl << "========================================" << endl;
	SetUpSim(filename);
	cout << "========================================" << endl << endl;

	Student* tempStudent;
	Student* popStudent;

	// Need to start simulator at tick count 0 per instructions
	int tickCount = 0;

	cout << "=================" << "TICK COUNT " << tickCount << endl << endl;
	// At the begining of the tick process anyone at the window

	cout << "At the start of the tick you have: " << endl;
	cout << " -- " << atWindow.Size() << " students being process" << endl << endl;

	// Now for the real simulation
	++tickCount;
	while (!inlineStudents.isEmpty()) {
		cout << "=================" << "TICK COUNT " << tickCount << endl;
		// At the begining of the tick process anyone at the window	
		cout << " At the start of the tick you have: " << endl;
		cout << " -- " << atWindow.Size() << " students being process" << endl;

		ProcessTransactions();

		bool keepRunning = true;
		tempStudent = inlineStudents.Peek();
		if ((tempStudent->GetArrivalTime() <= tickCount) &&
			(!freeWindows.isEmpty())){
			keepRunning = true;
		}
		else {
			keepRunning = false;
		}

		while (keepRunning) {

			popStudent = inlineStudents.Dequeue();

			cout << " -- " << " Student who arrived at tick count " << popStudent->GetArrivalTime();
			cout << " moves to an open window,";
			cout << " they will take " << popStudent->GetTransactionTime() << " ticks to process." << endl;
			
			// Adding student to the atWindow server queue"
			// Count this tick as the processing count since a tick is a minute long
			popStudent->DecrementTransactionTime();
			atWindow.Enqueue(popStudent);

			// Move the window from free a to busy
			busyWindows.Enqueue(freeWindows.Dequeue());

			if (!inlineStudents.isEmpty()) {
				// If we still have students in line then check if the student arrived before our tick time
				// and check if we have a free window, otherwise exit the loop.
				tempStudent = inlineStudents.Peek();
				if ((tempStudent->GetArrivalTime() <= tickCount) &&
					(!freeWindows.isEmpty())) {

					//This is the case where the student has arrived and windws are free
					keepRunning = true;
				}
				else {

					//This is the case where the student has arrived and windws are free
					cout << endl << "-- " << atWindow.Size() << " servers are processing others." << endl;
					cout << "  -- " << "Students are waiting." << endl;
					keepRunning = false;
				}
			}
			else {
				// No more students in line
				keepRunning = false;
			}
		}

		cout << endl << endl;
		ProcessIdle(tickCount);
		++tickCount;

		cout << "At the end of the tick you have: " << endl;
		cout << "  -- " << processedStudents.Size() << " students have been processed." << endl << endl;
	}

	// Now that we have all students in line we need to process them.
	while (!atWindow.isEmpty()) {
		cout << "=================" << "TICK COUNT " << tickCount << endl;

		cout << "At the start of the tick you have: " << endl;
		cout << endl << "-- " << atWindow.Size() << " servers are processing others." << endl;
		cout << "  -- " << "Students are not waiting." << endl;

		ProcessTransactions();

		cout << endl << "At the end of the tick you have: " << endl;
		cout << "  -- " << processedStudents.Size() << " students have been processed." << endl;
		cout << endl << endl;

		++tickCount;
	}

	GenerateMetrics();
}


Sim::~Sim() {
}

