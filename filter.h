#ifndef FILTER_H
#define FILTER_H

#include <vector>

class filter
{
private:
    std::vector<double> *b; //Numeral coefficients of rational transfer func.
    std::vector<double> *a; //Determinator coefficients of rational transfer func.
    std::vector<double> *input; //X input vector
    std::vector<double> *zi; //Initial conditions

    std::vector<double> output1;
    std::vector<double> output2;
public:


    filter();
    void loadInputData(std::vector<double> *b1, std::vector<double> *a1, std::vector<double> *X1, std::vector<double> *z1);
    void doFilter();
    std::vector<double> *getFirstOutput();
    std::vector<double> *getSecondOutput();
};

#endif // FILTER_H

//function [Y, z] = myFilter(b, a, X, z)
//% Author: Jan Simon, Heidelberg, (C) 2011
//n    = length(a);
//z(n) = 0;      % Creates zeros if input z is omitted
//b = b / a(1);  % [Edited, Jan, 26-Oct-2014, normalize parameters]
//a = a / a(1);
//Y    = zeros(size(X));
//for m = 1:length(Y)
//   Y(m) = b(1) * X(m) + z(1);
//   for i = 2:n
//      z(i - 1) = b(i) * X(m) + z(i) - a(i) * Y(m);
//   end
//end
//z = z(1:n - 1);
