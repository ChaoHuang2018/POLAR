#include "POLAR/Continuous.h"

using namespace flowstar;
using namespace std;

class TaylorInfo
{
public:
    Global_Computation_Setting g_setting;
    unsigned int order;
    Interval cutoff_threshold;
    unsigned int bernstein_order;
    unsigned int partition_num;

public:
    TaylorInfo();
    TaylorInfo(Global_Computation_Setting g_setting, unsigned int order, unsigned int bernstein_order, unsigned int partition_num, Interval cutoff_threshold);
};