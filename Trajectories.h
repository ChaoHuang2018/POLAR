#include "POLAR/Continuous.h"

using namespace flowstar;
using namespace std;

class Trajectories
{
protected:
    // the dimension of the system state
    int dimension;
    //
    vector<vector<vector<double>>> traces;

public:
    Trajectories();
    Trajectories(int dimension, string filename);

    int get_dimension()
    {
        return this->dimension;
    }

    vector<vector<vector<double>>> get_traces()
    {
        return this->traces;
    }

    void set_dimension(int dimension)
    {
        this->dimension = dimension;
    }

    void set_traces(vector<vector<vector<double>>> traces)
    {
        this->traces = traces;
    }
};
