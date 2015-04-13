#include "synthesize.h"

void synthesize::run()
{
  unsigned nextvoiced = 1;
  unsigned power = 0;
  vector<double> coeffs(predictor_coeffs.size() + 1, 1.0);
  vector<double> excit(window_length);
  vector<double> init(predictor_order, 1.0);
  vector<unsigned> where;

  auto random = bind(normal_distribution<double>(), mt19937(0));

  for (int i = 0; i < gains.size(); ++i)
  {
    for (int j = 1; j <= predictor_coeffs.size(); ++j)
      coeffs[j] = predictor_coeffs[j][i];

    if (lags[i] == 0)
      //fill(excit.begin(), excit.end(), 1.0);
      for (vector<double>::iterator it = excit.begin(); it != excit.end(); ++it)
        *it = random();
    else
    {
      for (unsigned j = lags[i]; j <= window_length; j += lags[i])
        where.push_back(j);

      nextvoiced = where.back() + lags[i] - window_length; 

      fill(excit.begin(), excit.end(), 0.0);
      for (vector<unsigned>::iterator it = where.begin(); it != where.end(); ++it)
        excit[*it] = 1.0;
    }

    power = 0;
    for (vector<double>::iterator it = excit.begin(); it != excit.end(); ++it)
      power += *it**it;
    power = sqrt(power/window_length); 
    for (vector<double>::iterator it = excit.begin(); it != excit.end(); ++it)
      *it = *it / power;

    vector<double> tmp;
    tmp.push_back(gains[i]);
    filter f;
    f.loadInputData(&tmp, &coeffs, &excit, &init);
    f.doFilter();
    
    vector<double> *tmp_ptr = f.getFirstOutput();
    for (vector<double>::iterator it = tmp_ptr->begin(); it != tmp_ptr->end(); ++it)
      result.push_back(*it);

    tmp_ptr = f.getSecondOutput();
    init.swap(*tmp_ptr);
  }
}

/*void synthesize::check()
{

}*/
