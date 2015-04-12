#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int readTxt(string filename, vector<double> &v){
	    
    string line;
    ifstream infile;
    infile.open(filename.c_str());

    if (!infile) return 1;

    double number;

    while (getline(infile, line) && !line.empty()){
        for (istringstream numbers_iss(line); numbers_iss >> number;){
            v.push_back(number);
        }
        i++;
    }

    return 0;
}

int readCod(string filename, vector< vector<int> > &cod){
	
	string line;
    ifstream infile;
    infile.open(filename.c_str());

	if (!infile) return 1;

    int number;
	int i = 0;

	while (getline(infile, line) && !line.empty()) {        
        cod.resize(cod.size() + 1);
        for (istringstream numbers_iss(line); numbers_iss >> number;){
            cod[i].push_back(number);            
        }

        i += 1;
    }

	return 0;
}

int main(int argc, char *argv[]){
    
	vector<double> lpc, gain;
	vector< vector<int> > cod;

	if (argc != 5){ 
		fprintf(stderr, "Error: Invalid input parameters\n");
		return 1;
	}

	string lpcFile = argv[1];
	string gainFile = argv[2];
	string testIn = argv[3];
	string outFile = argv[4];

	if (readTxt(lpcFile, lpc) != 0) return 1;
	if (readTxt(gainFile, gain) != 0) return 1;
	if (readCod(testIn, cod) != 0) return 1;

    return 0;
}

