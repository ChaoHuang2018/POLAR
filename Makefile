CXX = g++-8
HOME= /usr/local/include
NN_HOME = ./
LIB_HOME = ./POLAR
LIBS = -lflowstar -lmpfr -lgmp -lgsl -lgslcblas -lm -lglpk
CFLAGS = -I . -I $(HOME) -g -O3 -std=c++11
LINK_FLAGS = -g -L$(LIB_HOME) -L/usr/local/lib -L$(NN_HOME)
OBJS = NeuralNetwork.o Activation.o Neuron.o TaylorInfo.o NNTaylor.o Result_Info.o
	   # systems/reachnn_benchmark_1_relu.o $(OBJS) systems/reachnn_benchmark_1_relu_tanh.o $(OBJS) systems/reachnn_benchmark_1_sigmoid.o $(OBJS) systems/reachnn_benchmark_1_tanh.o $(OBJS) \
	   # systems/reachnn_benchmark_2_relu.o $(OBJS) systems/reachnn_benchmark_2_relu_tanh.o $(OBJS) systems/reachnn_benchmark_2_sigmoid.o $(OBJS) systems/reachnn_benchmark_2_tanh.o $(OBJS) \
	   # systems/reachnn_benchmark_3_relu.o $(OBJS) systems/reachnn_benchmark_3_relu_sigmoid.o $(OBJS) systems/reachnn_benchmark_3_sigmoid.o $(OBJS) systems/reachnn_benchmark_3_tanh.o $(OBJS) \
	   # systems/reachnn_benchmark_4_relu.o $(OBJS) systems/reachnn_benchmark_4_relu_tanh.o $(OBJS) systems/reachnn_benchmark_4_sigmoid.o $(OBJS) systems/reachnn_benchmark_4_tanh.o $(OBJS) \
	   # systems/reachnn_benchmark_5_relu.o $(OBJS) systems/reachnn_benchmark_5_relu_tanh.o $(OBJS) systems/reachnn_benchmark_5_sigmoid.o $(OBJS) systems/reachnn_benchmark_5_tanh.o $(OBJS) \
	   # systems/reachnn_benchmark_6_tora_relu.o $(OBJS) systems/reachnn_benchmark_6_tora_relu_tanh.o $(OBJS) systems/reachnn_benchmark_6_tora_sigmoid.o $(OBJS) systems/reachnn_benchmark_6_tora_tanh.o $(OBJS)

all: benchmark1_relu benchmark1_relu_tanh benchmark1_sigmoid benchmark1_tanh benchmark2_relu benchmark2_relu_tanh benchmark2_sigmoid benchmark2_tanh benchmark3_relu benchmark3_relu_sigmoid benchmark3_sigmoid benchmark3_tanh benchmark4_relu benchmark4_relu_tanh benchmark4_sigmoid benchmark4_tanh benchmark5_relu benchmark5_relu_tanh benchmark5_sigmoid benchmark5_tanh benchmark6_relu benchmark6_relu_tanh benchmark6_sigmoid benchmark6_tanh nn_attitude_control_sigmoid motivating
# all: benchmark6_tanh

runtime: $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) $^ $(LIBS)

benchmark1_relu: systems/reachnn_benchmark_1_relu.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark1_relu_tanh: systems/reachnn_benchmark_1_relu_tanh.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark1_sigmoid: systems/reachnn_benchmark_1_sigmoid.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark1_tanh: systems/reachnn_benchmark_1_tanh.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark2_relu: systems/reachnn_benchmark_2_relu.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark2_relu_tanh: systems/reachnn_benchmark_2_relu_tanh.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark2_sigmoid: systems/reachnn_benchmark_2_sigmoid.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark2_tanh: systems/reachnn_benchmark_2_tanh.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark3_relu: systems/reachnn_benchmark_3_relu.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark3_relu_sigmoid: systems/reachnn_benchmark_3_relu_sigmoid.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark3_sigmoid: systems/reachnn_benchmark_3_sigmoid.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark3_tanh: systems/reachnn_benchmark_3_tanh.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark4_relu: systems/reachnn_benchmark_4_relu.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark4_relu_tanh: systems/reachnn_benchmark_4_relu_tanh.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark4_sigmoid: systems/reachnn_benchmark_4_sigmoid.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark4_tanh: systems/reachnn_benchmark_4_tanh.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark5_relu: systems/reachnn_benchmark_5_relu.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark5_relu_tanh: systems/reachnn_benchmark_5_relu_tanh.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark5_sigmoid: systems/reachnn_benchmark_5_sigmoid.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark5_tanh: systems/reachnn_benchmark_5_tanh.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark6_relu: systems/reachnn_benchmark_6_tora_relu.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark6_relu_tanh: systems/reachnn_benchmark_6_tora_relu_tanh.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark6_sigmoid: systems/reachnn_benchmark_6_tora_sigmoid.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

benchmark6_tanh: systems/reachnn_benchmark_6_tora_tanh.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

# nn_attitude_control_relu: systems/reachnn_nn_attitude_control_relu.o $(OBJS)
# 	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)
#
# nn_attitude_control_relu_tanh: systems/reachnn_nn_attitude_control_relu_tanh.o $(OBJS)
# 	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

nn_attitude_control_sigmoid: systems/nn_attitude_control_sigmoid.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

# nn_attitude_control_tanh: systems/reachnn_nn_attitude_control_tanh.o $(OBJS)
# 	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

motivating: systems/motivating.o $(OBJS)
	g++-8 -O3 -w $(LINK_FLAGS) -o $@ $^ $(LIBS)

%.o: %.cc
	$(CXX) -O3 -c $(CFLAGS) -o $@ $<
%.o: %.cpp
	$(CXX) -O3 -c $(CFLAGS) -o $@ $<
%.o: %.c
	$(CXX) -O3 -c $(CFLAGS) -o $@ $<


clean:
	rm -f *.o systems/*.o runtime test

