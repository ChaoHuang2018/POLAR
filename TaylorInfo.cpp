#include "POLAR/Continuous.h"
#include "TaylorInfo.h"

using namespace flowstar;
using namespace std;

TaylorInfo::TaylorInfo()
{
}

TaylorInfo::TaylorInfo(Global_Computation_Setting g_setting, unsigned int order, unsigned int bernstein_order, unsigned int partition_num, Interval cutoff_threshold)
{
    this->g_setting = g_setting;
    this->order = order;
    this->cutoff_threshold = cutoff_threshold;
    this->bernstein_order = bernstein_order;
    this->partition_num = partition_num;
}