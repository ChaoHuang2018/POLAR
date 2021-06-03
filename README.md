# POLAR prototype for NeurIPS 21
POLAR is a reachability analysis framework for neural-network controlled systems (NNCSs) based on polynomial arithmetic. Compared with existing arithmetic approaches that use standard Taylor models, our framework uses a novel approach to iteratively overapproximate the neuron output ranges layer-by-layer with a combination of Bernstein polynomial interpolation for continuous activation functions and Taylor model arithmetic for the other operations. This approach can overcome the main drawback in the standard Taylor model arithmetic, i.e. its inability to handle functions that cannot be well approximated by Taylor polynomials, and significantly improve the accuracy and efficiency of reachable states computation for NNCSs. To further tighten the overapproximation, our method keeps the Taylor model remainders symbolic under the linear mappings when estimating the output range of a neural network. Experiment results across a suite of benchmarks show that POLAR significantly outperforms the state-of-the-art techniques.

## Installation

#### System Requirements
Ubuntu 18.04, MATLAB 2016a or later

#### Up-to-date Installation
- Install dependencies through apt-get install
```
sudo apt-get install m4 libgmp3-dev libmpfr-dev libmpfr-doc libgsl-dev gsl-bin bison flex gnuplot-x11 libglpk-dev gcc-8 g++-8 libopenmpi-dev
```

#### Compile POLAR

```

./compile.sh # under the root directory ./

```

## Running Examples - POLAR results

### Attitude control
./run_attitude_control.sh

### Example #1 to #6
./run.sh

### Checking Result
All results will be stored in ./outputs/

For SYSTEM, the results include a txt file that show the verification result and the POLAR running time, and a M file (with .m extension) that is used to plot the reachable sets computed by POLAR. One can check the result of SYSTEM by following commands.

```

# verification result
vim SYSTEM_0.txt

# plotted reachable sets. Run the following command in MATLAB.
SYSTEM_0.m
