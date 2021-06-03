#include "Trajectories.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace flowstar;
using namespace std;

Trajectories::Trajectories()
{
}

Trajectories::Trajectories(int dimension, string filename)
{
    this->dimension = dimension;

    // parse the traces from "filename"
    std::ifstream input(filename);
    std::string line;

    vector<vector<vector<double>>> traces;
    vector<vector<double>> trace;
    while (getline(input, line))
    {
        if (line == "*")
        {
            traces.push_back(trace);
            trace.clear();
        }
        else
        {
            string stateStr;
            stringstream ss(line);

            vector<double> state;
            while (ss >> stateStr)
            {
                // cout << stateStr << endl;
                state.push_back(stod(stateStr));
            }
            // cout << state[0] << " " << state[1] << endl;
            trace.push_back(state);
        }
    }

    this->traces = traces;
}