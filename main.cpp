#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

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
//        i++;
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

int dataToWav(vector<double> &ss,string fileName){
    unsigned samplesPerSec = 8000;
    unsigned bitsPerSample = 16;

    if(fileName.empty()) return 1;

    FILE *outFile;
    outFile = fopen(fileName.c_str(),"wb");

    int channels = 1;
    int n = ss.size();

    unsigned ckSize = n * channels * (bitsPerSample / 2);
    unsigned int value = ckSize + 36;
    //RIFF header
    fwrite("RIFF",sizeof(u_char),4,outFile);
    //file size - 8
    fwrite(&value,sizeof(u_int32_t),1,outFile);
    fwrite("WAVEfmt",sizeof(u_char),7,outFile);
    //size of fmt chunk
    value = 16;
    fwrite(&value,sizeof(u_int32_t),1,outFile);
    //sample format code
    value = 1;
    fwrite(&value,sizeof(u_int16_t),1,outFile);
    //channels
    fwrite(&channels,sizeof(u_int16_t),1,outFile);
    //sample rate
    fwrite(&samplesPerSec,sizeof(u_int32_t),1,outFile);
    //bytes per sec
    int bps = samplesPerSec * bitsPerSample/8;
    fwrite(&bps,sizeof(u_int32_t),1,outFile);
    //block align
    value = channels * bitsPerSample/8;
    fwrite(&value,sizeof(u_int16_t),1,outFile);
    fwrite(&bitsPerSample,sizeof(u_int16_t),1,outFile);
    fwrite("data",sizeof(u_char),4,outFile);
    fwrite(&ckSize,sizeof(u_int32_t),1,outFile);

    //data
    fwrite(&ss,sizeof(int16_t),ss.size(),outFile);
    fclose(outFile);

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

