#ifndef SYNTHESIZE_H
#define SYNTHESIZE_H

#include <vector>
#include <algorithm>
#include <random>

#include "filter.h"

using namespace std;

class synthesize
{
  public:
 //   synthesize();
    synthesize(vector<vector<double> > *predictor_coeffs, vector<double> *gains, vector<double> *lags, unsigned predictor_order, unsigned window_length);
~synthesize();

/*    unsigned get_predictor_order();
    void set_predictor_order(unsigned predictor_order);
    unsigned get_window_length();
    void set_window_length(unsigned window_length);
    vector<double> &get_lags();
    void set_lags(vector<double> &lags);
    vector<double> &get_gains();
    void set_gains(vector<double> &gains);
    vector<vector<double>> &get_predictor_coeffs();
    void set_predictor_coeffs(vector<vector<double>> &predictor_coeffs);
*/    vector<double> *get_result();

    void run();

  private:
    vector<double> *lags;
    vector<double> *gains;
    vector<vector<double>> *predictor_coeffs;
    unsigned predictor_order;
    unsigned window_length;

    vector<double> result;
    
 //   void check();
};

#endif // SYNTHESIZE_H
