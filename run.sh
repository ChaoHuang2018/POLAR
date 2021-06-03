make && \
    ./benchmark1_relu 0.05 50 4 6 0 && \
    ./benchmark1_relu_tanh 0.05 35 4 6 0 && \
    ./benchmark1_sigmoid 0.05 35 4 6 0 && \
    ./benchmark1_tanh 0.05 25 4 6 0  && \

    ./benchmark2_relu 0.1 10 4 6 0 && \
    ./benchmark2_relu_tanh 0.1 10 4 6 0 && \
    ./benchmark2_sigmoid 0.1 9 4 6 1 && \
    ./benchmark2_tanh 0.1 7 4 6 0 && \

    ./benchmark3_relu 0.05 60 4 6 0 && \
    ./benchmark3_relu_sigmoid 0.05 60 4 6 0 && \
    ./benchmark3_sigmoid 0.05 60 4 6 0 && \
    ./benchmark3_tanh 0.05 60 4 6 0 && \

    ./benchmark4_relu 0.01 10 4 6 0 && \
    ./benchmark4_relu_tanh 0.01 10 4 6 0 && \
    ./benchmark4_sigmoid 0.01 10 4 6 0 && \
    ./benchmark4_tanh 0.01 10 4 6 0 && \

    ./benchmark5_relu 0.01 10 4 6 0 && \
    ./benchmark5_relu_tanh 0.01 10 4 6 0 && \
    ./benchmark5_sigmoid 0.01 10 4 6 0 && \
    ./benchmark5_tanh 0.01 10 4 6 0 && \

    ./benchmark6_relu 0.01 10 4 6 0 && \
    ./benchmark6_relu_tanh 0.01 10 4 6 0 && \
    ./benchmark6_sigmoid 0.01 10 4 6 0 && \
    ./benchmark6_tanh 0.01 10 4 6 0
#    ./nn_attitude_control_sigmoid
