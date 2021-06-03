figure;
ex1_sig_tmp;
reachnn_benchmark_1_sigmoid_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark1_sigmoid','-dpdf');
% export_fig ./Benchmarks_symbolic/benchmark1_sigmoid.pdf;

figure;
ex1_tanh_tmp;
reachnn_benchmark_1_tanh_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark1_tanh','-dpdf');
% export_fig ./Benchmarks_symbolic/benchmark1_tanh.pdf;

figure;
reachnn_benchmark_1_relu_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark1_relu','-dpdf');
% export_fig ./Benchmarks_symbolic/benchmark1_relu.pdf;

figure;
reachnn_benchmark_1_relu_tanh_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark1_relu_tanh','-dpdf');
% export_fig ./Benchmarks_symbolic/benchmark1_relu_tanh.pdf;

figure;
ex2_sig_tmp;
reachnn_benchmark_2_sigmoid_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark2_sigmoid','-dpdf');


figure;
ex2_tanh_tmp;
reachnn_benchmark_2_tanh_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark2_tanh','-dpdf');


% figure;
% reachnn_benchmark_2_relu_1;
% 
% fig = gcf;
% fig.PaperPositionMode = 'auto';
% fig_pos = fig.PaperPosition;
% fig.PaperSize = [fig_pos(3) fig_pos(4)];
% print(fig,'./Benchmarks_symbolic/benchmark2_relu','-dpdf');


figure;
reachnn_benchmark_2_relu_tanh_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark2_relu_tanh','-dpdf');

figure;
ex3_sig_tmp;
reachnn_benchmark_3_sigmoid_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark3_sigmoid','-dpdf');


figure;
ex3_tanh_tmp;
reachnn_benchmark_3_tanh_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark3_tanh','-dpdf');


% figure;
% reachnn_benchmark_3_relu_1;
% 
% fig = gcf;
% fig.PaperPositionMode = 'auto';
% fig_pos = fig.PaperPosition;
% fig.PaperSize = [fig_pos(3) fig_pos(4)];
% print(fig,'./Benchmarks_symbolic/benchmark3_relu','-dpdf');


figure;
reachnn_benchmark_3_relu_sigmoid_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark3_relu_sigmoid','-dpdf');


figure;
ex4_sig_tmp;
reachnn_benchmark_4_sigmoid_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark4_sigmoid','-dpdf');


figure;
% ex4_tanh_tmp;
reachnn_benchmark_4_tanh_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark4_tanh','-dpdf');


figure;
reachnn_benchmark_4_relu_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark4_relu','-dpdf');


figure;
reachnn_benchmark_4_relu_tanh_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark4_relu_tanh','-dpdf');

figure;
ex5_sig_tmp;
reachnn_benchmark_5_sigmoid_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark5_sigmoid','-dpdf');


figure;
ex5_tanh_tmp;
reachnn_benchmark_5_tanh_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark5_tanh','-dpdf');


figure;
reachnn_benchmark_5_relu_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark5_relu','-dpdf');


figure;
reachnn_benchmark_5_relu_tanh_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark5_relu_tanh','-dpdf');

figure;
tora_sig_tmp;
reachnn_benchmark_6_tora_sigmoid_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark6_sigmoid','-dpdf');


figure;
tora_tanh_tmp;
reachnn_benchmark_6_tora_tanh_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark6_tanh','-dpdf');


figure;
reachnn_benchmark_6_tora_relu_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark6_relu','-dpdf');


figure;
reachnn_benchmark_6_tora_relu_tanh_1;

fig = gcf;
fig.PaperPositionMode = 'auto';
fig_pos = fig.PaperPosition;
fig.PaperSize = [fig_pos(3) fig_pos(4)];
print(fig,'./Benchmarks_symbolic/benchmark6_relu_tanh','-dpdf');