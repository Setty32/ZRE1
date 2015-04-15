#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

#include "synthesize.h"

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

int readCod(string filename, vector< vector<double> > &cod){
	
	string line;
    ifstream infile;
    infile.open(filename.c_str());

	if (!infile) return 1;

    double number;
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
    u_int32_t samplesPerSec = 8000;
    u_int16_t bitsPerSample = 16;

    if(fileName.empty()) return 1;

    FILE *outFile;
    outFile = fopen(fileName.c_str(),"wb");

    u_int16_t channels = 1;
    int n = ss.size();

    u_int32_t ckSize = n * channels * (bitsPerSample / 8);
//    cerr << ckSize << endl;
    u_int32_t value = ckSize + 36;
    //RIFF header
    fwrite("RIFF",sizeof(u_char),4,outFile);
    //file size - 8
    fwrite(&value,sizeof(u_int32_t),1,outFile);
    fwrite("WAVEfmt ",sizeof(u_char),8,outFile);
    //size of fmt chunk
    value = 16;
    fwrite(&value,sizeof(u_int32_t),1,outFile);
    //sample format code
    u_int16_t val = 1;
    fwrite(&val,sizeof(u_int16_t),1,outFile);
    //channels
    fwrite(&channels,sizeof(u_int16_t),1,outFile);
    //sample rate
    fwrite(&samplesPerSec,sizeof(u_int32_t),1,outFile);
    //bytes per sec
    u_int32_t bps = samplesPerSec * bitsPerSample/8;
    fwrite(&bps,sizeof(u_int32_t),1,outFile);
    //block align
    val = 2;
    fwrite(&val,sizeof(u_int16_t),1,outFile);
    fwrite(&bitsPerSample,sizeof(u_int16_t),1,outFile);
    fwrite("data",sizeof(u_char),4,outFile);
    fwrite(&ckSize,sizeof(u_int32_t),1,outFile);

    //data
    for(unsigned m = 0; m < ss.size(); m++){
        int16_t val = (int16_t)(ss.at(m) * 32767);
        fwrite(&val,sizeof(int16_t),1,outFile);
    }
    fclose(outFile);

    return 0;
}

int main(int argc, char *argv[]){
    
    vector<double> gain;
    vector< vector<double> > cod, lpc;

	if (argc != 5){ 
		fprintf(stderr, "Error: Invalid input parameters\n");
		return 1;
	}

	string lpcFile = argv[1];
	string gainFile = argv[2];
	string testIn = argv[3];
	string outFile = argv[4];

    if (readCod(lpcFile, lpc) != 0) return 1;
    if (readTxt(gainFile, gain) != 0) return 1;
    if (readCod(testIn, cod) != 0) return 1;


    vector<double> asym;
    vector<double> gsym;
    vector<double> lags;

    for(unsigned i = 0; i < cod.size(); i++){
        asym.push_back(cod.at(i).at(0));
        gsym.push_back(cod.at(i).at(1));
        lags.push_back(cod.at(i).at(2));
    }

    vector<vector<double> > Adecoded;
    vector<double> Gdecoded;

    for(unsigned i = 0; i < cod.size(); i++){
        vector<double> assist;
        Adecoded.push_back(assist);
        for(unsigned j = 0; j < lpc.size(); j++){
            Adecoded.at(i).push_back(lpc.at(j).at(asym.at(i) - 1));
        }

        Gdecoded.push_back(gain.at(gsym.at(i)));
    }

    synthesize syn(&Adecoded, &Gdecoded,&lags,10,160);
    syn.run();
    vector<double> *ss = syn.get_result();
    if(dataToWav(*ss,outFile) != 0) return 1;


    return 0;
}

