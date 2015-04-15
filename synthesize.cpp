#include "synthesize.h"
#include <iostream>
#include <random>
#include "filter.h"
#include <limits>

synthesize::synthesize(vector<vector<double>> *predictor_coeffs,
                       vector<double> *gains, vector<double> *lags,
                       unsigned predictor_order, unsigned window_length)
{
  this->window_length    = window_length;
  this->predictor_order  = predictor_order;
  this->predictor_coeffs = predictor_coeffs;
  this->gains            = gains;
  this->lags             = lags;
}

synthesize::~synthesize(){

}

void synthesize::run()
{
    int Nram = gains->size();
    vector<double> init;
    for(unsigned i = 0; i < predictor_order; i++){
        init.push_back(0.0f);
    }

    for(unsigned i = 0; i < Nram * window_length; i++){
        result.push_back(0.0f);
    }

    int nextVoiced = 0; // 1 in matlab index

    int from = 0; // 1 in matlab index
    int to = from + window_length -1; // maybey -2

    for(int n = 0 ; n < Nram; n++){
        vector<double>  a;
        a.push_back(1.0f);
        for(unsigned k = 0; k < predictor_coeffs->at(n).size(); k++){
            a.push_back(predictor_coeffs->at(n).at(k));
        }
        double g = gains->at(n);
        double l =  lags->at(n);

        vector<double> excit;

        if( l == 0){
            default_random_engine gen;
            normal_distribution<double> dist(0.0f,5.0f); //standar normal distribution

            for(unsigned m = 0; m < window_length; m++){
                double num = dist(gen);
                excit.push_back(num);
            }
        } else {
            vector<double> where;

            for(unsigned m = 0; m < window_length; m++){
                excit.push_back(0.0f);
            }

            int max = numeric_limits<int>::min();
            for(int m = nextVoiced; m < window_length; m+= l){  // pada pro m <= win_len!!
                where.push_back(m);
                if(m > max){
                    max = m;
                }

                excit.at(m) = 1;
            }
            where.clear();

            nextVoiced = max + l - window_length;
        }

        double sum = 0;
        for(unsigned m = 0; m < excit.size(); m++){
            sum += excit.at(m) * excit.at(m);
        }
        double power = sum / window_length;


        for(unsigned m = 0; m < excit.size(); m++){
            excit.at(m) = excit.at(m) / sqrt(power);
        }

        filter f;
        vector<double> g1;
        g1.push_back(g);
        f.loadInputData(&g1,&a,&excit,&init);
        f.doFilter();
        vector<double> *synt, *final;

        synt = f.getFirstOutput();
        final = f.getSecondOutput();

        int j = 0;
        for (int m = from; m <= to; m++) {
            result.at(m) = synt->at(j);
            j++;
        }

        for(unsigned m = 0; m < init.size(); m++){
            init.at(m) = final->at(m);
        }

        from = from + window_length;
        to = from + window_length - 1;

    }
}

vector<double> *synthesize::get_result()
{
  return &result;
}
