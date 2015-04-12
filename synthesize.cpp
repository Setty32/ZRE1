#include "synthesize.h"
/*  public:
    synthesize();
    synthetize(vector<vector<double>> &predictor_coeffs, vector<double> &gains, vector<double> &lags, unsigned predictor_order, unsigned window_length);
    ~synthesize();

    unsigned get_predictor_order();
    void set_predictor_order(unsigned predictor_order);
    unsigned get_window_length();
    void set_window_length(unsigned window_length);
    vector<double> &get_lags();
    void set_lags(vector<double> &lags);
    vector<double> &get_gains();
    void set_gains(vector<double> &gains);
    vector<vector<double>> &get_predictor_coeffs();
    void set_predictor_coeffs(vector<vector<double>> &predictor_coeffs);
    vector<double> &get_result();

    void run();

  private:
    vector<double> &lags;
    vector<double> &gains;
    vector<vector<double>> &predictor_coeffs;
    unsigned predictor_order;
    unsigned window_length;

    vector<double> result;
    
    void check();
*/

synthetize::synthetize(vector<vector<double>> &predictor_coeffs, vector<double> &gains, vector<double> &lags, unsigned predictor_order, unsigned window_length)
{
  this.window_length    = window_length;
  this.predictor_order  = predictor_order;
  this.predictor_coeffs = predictor_coeffs;
  this.gains            = gains;
  this.lags             = lags;
}

void synthetize::run()
{
  unsigned nextvoiced = 1;
  unsigned power = 0;
  vector<double> coeffs(predictor_coeffs.size() + 1, 1.0);
  vector<double> excit(window_length);
  vector<double> init(predictor_order, 1.0);
  vector<unsigned> where;

  for (int i = 0; i < gains.size(); ++i)
  {
    for (int j = 1; j <= predictor_coeffs.size(); ++j)
      coeffs[j] = predictor_coeffs[j][i];

    if (lags[i] == 0)
      // bude nahradene tymto excit = random_numbers();
      fill(excit.begin(), excit.end(), 1.0);
    else
    {
      for (unsigned j = lags[i]; j <= window_length; j += lags[i])
        where.push_back(j);

      nextvoiced = where.back() + lags[i] - window_size; 

      fill(excit.begin(), excit.end(), 0.0);
      for (vector<unsigned>::iterator it = where.begin(); it != where.end(); ++it)
        excit[*it] = 1.0;
    }

    power = 0;
    for (vector<unsigned>::iterator it = excit.begin(); it != excit.end(); ++it)
      power += *it**it;
    power = sqrt(power/window_length); 
    for (vector<unsigned>::iterator it = excit.begin(); it != excit.end(); ++it)
      *it = *it / power;

    filter

    appendToResult
    copyOverToInit

    excit.clear();
  }
}

/*void synthesize::check()
{

}*/

vector<double> &synthetize::get_result()
{
  return result;
}
