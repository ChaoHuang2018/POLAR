#include "Result_Info.h"

using namespace flowstar;
using namespace std;

Result_Info::Result_Info()
{
}

Result_Info::Result_Info(vector<double> time, vector<int> result)
{
    this->time = time;
    this->result = result;
}
