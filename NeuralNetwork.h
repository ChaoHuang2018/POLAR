#include "POLAR/Continuous.h"

using namespace flowstar;
using namespace std;

class Layer
{
protected:
    // hidden layer and output layer (input layer excluded)
    int neuron_number_last_layer;
    int neuron_number_this_layer;
    // activation of this layer: can be 'ReLU' or 'tanh' or 'sigmoid'
    string activation;
    // even though weight and bias are real matrix, we use interval to describe the access of each matrix for convenience
    Matrix<Interval> weight;
    Matrix<Interval> bias;

public:
    Layer();
    Layer(int last_layer_dim, int dim, string act, Matrix<Interval> w, Matrix<Interval> b);

    int get_neuron_number_last_layer()
    {
        return this->neuron_number_last_layer;
    }

    int get_neuron_number_this_layer()
    {
        return this->neuron_number_this_layer;
    }

    string get_activation()
    {
        return this->activation;
    }

    Matrix<Interval> get_weight()
    {
        return this->weight;
    }

    Matrix<Interval> get_bias()
    {
        return this->bias;
    }
};

// Parse neural network and layer from a text file as classes
// Please provide the get and set function for each member in the two classes.

class NeuralNetwork
{

    //
protected:
    int num_of_inputs;
    // current version only support nn with scalar output, i.e., 1-dimesional output
    int num_of_outputs;
    int num_of_hidden_layers;
    // use interval type for offset and scale_factor
    // If needed, please declare the access of each matrix as a double
    Interval offset;
    Interval scale_factor;
    // include hidden layers and output layer
    vector<Layer> layers;

public:
    NeuralNetwork();
    NeuralNetwork(string filename);

    int get_num_of_inputs()
    {
        return this->num_of_inputs;
    }

    int get_num_of_outputs()
    {
        return this->num_of_outputs;
    }

    int get_num_of_hidden_layers()
    {
        return this->num_of_hidden_layers;
    }

    Interval get_offset()
    {
        return this->offset;
    }

    Interval get_scale_factor()
    {
        return this->scale_factor;
    }

    vector<Layer> get_layers()
    {
        return this->layers;
    }
};
