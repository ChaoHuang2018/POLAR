#include <fstream>
#include <iostream>
#include "NeuralNetwork.h"

Layer::Layer()
{
}

Layer::Layer(int last_layer_dim, int dim, string act, Matrix<Interval> w, Matrix<Interval> b)
{
    neuron_number_last_layer = last_layer_dim;
    neuron_number_this_layer = dim;
    activation = act;
    weight = w;
    bias = b;
}

NeuralNetwork::NeuralNetwork()
{
}

NeuralNetwork::NeuralNetwork(string filename)
{
    std::ifstream input(filename);
    std::string line;

    // Parse the structure of neural networks
    if (getline(input, line))
    {
    }
    else
    {
        cout << "failed to read file" << endl;
    }
    try
    {
        num_of_inputs = stoi(line);
    }
    catch (std::invalid_argument &e)
    {
        cout << "Problem during string/integer conversion!" << endl;
        cout << line << endl;
    }
    getline(input, line);
    num_of_outputs = stoi(line);
    getline(input, line);
    num_of_hidden_layers = stoi(line);

    // cout << "num_of_inputs" << num_of_inputs << ", " << num_of_outputs << ", " << num_of_hidden_layers;

    std::vector<int> network_structure(num_of_hidden_layers + 1, 0);
    for (int idx = 0; idx < num_of_hidden_layers; idx++)
    {
        getline(input, line);
        network_structure[idx] = stoi(line);
    }
    network_structure[network_structure.size() - 1] = num_of_outputs;

    // parse the activation function
    std::vector<std::string> activation;
    for (int idx = 0; idx < num_of_hidden_layers + 1; idx++)
    {
        getline(input, line);
        activation.push_back(line);
    }

    // Parse the input text file and store weights and bias

    // a question here. need to confirm on 10/20/2020 afternoon.
    // compute parameters of the input layer
    double value;
    Interval I(0.0, 0.0);
    Matrix<Interval> weight0(network_structure[0], num_of_inputs);
    Matrix<Interval> bias0(network_structure[0], 1);
    for (int i = 0; i < network_structure[0]; i++)
    {
        for (int j = 0; j < num_of_inputs; j++)
        {
            getline(input, line);
            value = stod(line);
            I.set(value, value);
            weight0[i][j] = I;
        }
        getline(input, line);
        value = stod(line);
        I.set(value);
        bias0[i][0] = I;
    }
    Layer input_layer(num_of_inputs, network_structure[0], activation[0], weight0, bias0);
    // cout << "weight0: " << weight0 << endl;
    // cout << "bias0: " << bias0 << endl;
    layers.push_back(input_layer);

    // compute the parameters of hidden layers
    for (int layer_idx = 0; layer_idx < num_of_hidden_layers; layer_idx++)
    {
        Matrix<Interval> weight(network_structure[layer_idx + 1], network_structure[layer_idx]);
        Matrix<Interval> bias(network_structure[layer_idx + 1], 1);

        for (int i = 0; i < network_structure[layer_idx + 1]; i++)
        {
            for (int j = 0; j < network_structure[layer_idx]; j++)
            {
                getline(input, line);
                value = stod(line);
                I.set(value);
                weight[i][j] = I;
            }
            getline(input, line);
            value = stod(line);
            I.set(value);
            bias[i][0] = I;
        }

        // cout << "weight_" + to_string(layer_idx + 1) + ":" << weight << endl;
        // cout << "bias_" + to_string(layer_idx + 1) + ":" << bias << endl;
        Layer hidden_layer(network_structure[layer_idx], network_structure[layer_idx + 1], activation[layer_idx + 1], weight, bias);
        layers.push_back(hidden_layer);
    }
    // Affine mapping of the output
    getline(input, line);
    value = stod(line);
    // cout << value << endl;
    I.set(value);
    offset = I;
    getline(input, line);
    value = stod(line);
    // cout << value << endl;
    I.set(value);
    scale_factor = I;
}