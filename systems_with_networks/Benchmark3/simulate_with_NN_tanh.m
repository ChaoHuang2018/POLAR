plot( [-0.15, -0.05, -0.05, -0.15, -0.15], [0.1,0.1,0.2,0.2,0.1] , 'color' , [72/255 130/255 197/255], 'LineWidth', 2.0);
hold on;
clear;
Ts = 0.2;  % Sample Time
N = 3;    % Prediction horizon
Duration = 4; % Simulation horizon

global simulation_result;
global disturb_range;

disturb_range = 0.1; % Disturbance range

formatSpec = '%f %f %f\n';

fileID = fopen('nn_3_tanh.txt','w');

% Initial sets limits [-1,1]^2

for m=1:100

x0 = 0.3 + 0.1*rand(1);
y0 = 0.3 + 0.1*rand(1);
z0 = -0.4 + 0.1*rand(1);
x = [x0;y0;z0];

simulation_result = x;



% Things specfic to the model  ends here

options = optimoptions('fmincon','Algorithm','sqp','Display','none');
uopt = zeros(N,1);

u_max = 0;


x_now = zeros(3,1);
x_next = zeros(3,1);
z = zeros(4,1);

x_now = x;

% Start simulation
for ct = 1:(Duration/Ts) 
     % u = NN_output(x_now,10,1,'nn_16_relu');
     u = NN_output_tanh(x_now,0,10,'nn_3_tanh');
     % u = NN_output_sigmoid(x_now, 0.5, 20, 'nn_16_sigmoid');

     
     z(1) = x_now(1) ;
     z(2) = x_now(2) ;
     z(3) = x_now(3) ;

     z(4) = u ;
     
    x_next = system_eq_dis(x_now, Ts, u);

    x = x_next;
    x_now = x_next;

end
plot(simulation_result(1,:),simulation_result(2,:), 'color', [223/255, 67/255, 69/255]);
% title('Benchmark 5 (tanh)', 'FontSize', 14)
% xlabel('x1', 'FontSize', 14);
% ylabel('x2', 'FontSize', 14);
set(gca,'FontSize',16)
hold on;

fprintf(fileID, formatSpec, simulation_result(1:3,:));

end
fclose(fileID);

% fig = gcf;
% fig.PaperPositionMode = 'auto';
% fig_pos = fig.PaperPosition;
% fig.PaperSize = [fig_pos(3) fig_pos(4)];
% print(fig,'../Benchmarks/benchmark5_tanh','-dpdf')
% export_fig ../Benchmarks/benchmark5_tanh.pdf