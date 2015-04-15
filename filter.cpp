#include "filter.h"
#include <iostream>

filter::filter()
{
}

void filter::loadInputData(std::vector<double> *b1, std::vector<double> *a1, std::vector<double> *X1, std::vector<double> *z1){
    this->b = b1;
    this->a = a1;
    this->input = X1;
    this->zi = z1;
}

std::vector<double> * filter::getFirstOutput(){
    return &output1;
}

std::vector<double> * filter::getSecondOutput(){
    return zi;
}

void filter::doFilter(){
    unsigned n = a->size();
    if(zi->size() != n){
        zi->resize(n);
    }
//    for(unsigned i = 0; i < zi->size(); i++){
//        zi->at(i) = 0;
//    }

//    for (unsigned i = 0; i < b->size(); i++) {
//        b->at(i) = b->at(i) / b->at(0);
//    }
//    for(unsigned i = 0; i < a->size(); i++){
//        a->at(i) = a->at(i) / a->at(0);
//    }

    output1.clear();
    output1.resize(input->size());
    for(unsigned i = 0; i < output1.size(); i++){
        output1.at(i) = b->at(0) * input->at(i) + zi->at(0);
        for (unsigned j = 1; j < n; j++) {
            zi->at(j - 1) = zi->at(j) - a->at(j) * output1.at(i);
        }
    }
}
