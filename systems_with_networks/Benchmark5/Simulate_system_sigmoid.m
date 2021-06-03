plot( [-0.4, -0.15, -0.15, -0.4, -0.4], [-0.02,-0.02,0.02,0.02,-0.02], 'color' , [72/255 130/255 197/255], 'LineWidth', 2.0);
hold on;
clear;
Ts = 0.5;  % Sample Time
N = 3;
Duration = 7.5; % Simulation horizon

global simulation_result;
global disturb_range;

disturb_range = 0.1; % Disturbance range

formatSpec = '%f %f %f\n';

fileID = fopen('nn_5_sigmoid.txt','w');

radius = 0.05;

for m=1:100

    
x0 = 0.35 + radius*rand(1);
y0 = 0.45 + radius*rand(1);
z0 = 0.25 + radius*rand(1);

x = [x0;y0;z0;];

simulation_result = x;

options = optimoptions('fmincon','Algorithm','sqp','Display','none');
uopt = zeros(N,1);

u_max = 0;

% Apply the control input constraints
LB = -3*ones(N,1);
UB = 3*ones(N,1);

x_now  = zeros(3,1);
x_next = zeros(3,1);
z = zeros(4,1);


% Start simulation
for ct = 1:(Duration/Ts)
    uopt(1) = NN_output_sigmoid(x, 0.5, 22, 'nn_5_sigmoid');
    
    x = system_eq_dis(x, Ts, uopt(1));
    
end
plot(simulation_result(1,:),simulation_result(2,:), 'color', [223/255, 67/255, 69/255]);
% title('Benchmark 7 (sigmoid)', 'FontSize', 14)
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
% print(fig,'../Benchmarks/benchmark7_sigmoid','-dpdf')
% export_fig ../Benchmarks/benchmark7_sigmoid.pdf