#include "student.cpp"
#include "queue.h"
#include "list.h"
#include "node.h"
#include "window.cpp"
#include "sim.cpp"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
	Sim sim;
    if (argc < 2) {
        cout << "You must specify an input file." << endl;
        cout << argv[0] << "  <filename>" << endl;
    }
    else {        
        string filename = argv[1];
        
        // Best to check the file name is ok before starting the Sim
        if (FILE* file = fopen(filename.c_str(), "r")) {
            fclose(file);
            sim.Start(filename);
        }
        else {
            cout << "Something is wrong with the filename " << filename << endl;
            return 1;
        }
    }

	return 0;
}