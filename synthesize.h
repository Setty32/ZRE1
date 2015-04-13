#ifndef SYNTHESIZE_H
#define SYNTHESIZE_H

#include <vector>
#include <algorithm>
#include <functional>
#include <random>

#include "filter.h"

using namespace std;

class synthesize
{
  public:
    synthesize(vector<vector<double>> &predictor_coeffs, vector<double> &gains, vector<double> &lags, unsigned predictor_order, unsigned window_length) : lags(lags), gains(gains), predictor_coeffs(predictor_coeffs), predictor_order(predictor_order), window_length(window_length) {}
    ~synthesize() {}

    inline unsigned get_predictor_order() { return predictor_order; }
    inline void set_predictor_order(unsigned predictor_order) { this->predictor_order = predictor_order; }
    inline unsigned get_window_length() { return window_length; }
    inline void set_window_length(unsigned window_length) { this->window_length = window_length; }
    inline vector<double> &get_lags() { return lags; }
    inline void set_lags(vector<double> &lags) { this->lags = lags; }
    inline vector<double> &get_gains() { return gains; }
    inline void set_gains(vector<double> &gains) { this->gains = gains; }
    inline vector<vector<double>> &get_predictor_coeffs() { return predictor_coeffs; }
    inline void set_predictor_coeffs(vector<vector<double>> &predictor_coeffs) { this->predictor_coeffs = predictor_coeffs; }
    inline vector<double> &get_result() { return result; }

    void run();

  private:
    vector<double> &lags;
    vector<double> &gains;
    vector<vector<double>> &predictor_coeffs;
    unsigned predictor_order;
    unsigned window_length;

    vector<double> result;
    
 //   void check();
};

#endif // SYNTHESIZE_H
