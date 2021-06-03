#include "POLAR/Continuous.h"

using namespace flowstar;
using namespace std;

class Result_Info
{
protected:
    // computation time list
    vector<double> time;
    // safe (0) or unsafe (1) or unknown (2) or fail (3)
    vector<int> result;

public:
    Result_Info();
    Result_Info(vector<double> time, vector<int> result);

    vector<double> get_time()
    {
        return this->time;
    }

    vector<int> get_result()
    {
        return this->result;
    }

    void set_time(vector<double> time)
    {
        this->time = time;
    }

    void set_result(vector<int> result)
    {
        this->result = result;
    }

    double get_safe_rate()
    {
        int safe_number = 0;
        for (int i = 0; i < this->result.size(); i++)
        {
            if (this->result[i] == 0)
            {
                safe_number = safe_number + 1;
            }
        }
        // cout << "safe_number: " << safe_number << endl;
        return safe_number * 1.0 / this->result.size();
    }

    double get_average_time()
    {
        double total = 0;
        for (int i = 0; i < this->time.size(); i++)
        {
            total = total + this->time[i];
        }
        return total / this->time.size();
    }
};
