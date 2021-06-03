Ts = 1;  % Sample Time
N = 3;    % Prediction horizon
Duration = 17; % Simulation horizon

radius = 0.1;

global simulation_result;
global disturb_range;

disturb_range = 0.1; % Disturbance range

formatSpec = '%f %f %f\n';

fileID = fopen('nn_tora_relu.txt','w');

for m=1:100

    
x0 = 0.8 + radius*rand(1);
y0 = -0.5 + radius*rand(1);
z0 = -0.2 + radius*rand(1);
w0 = 0.8 + radius*rand(1);


x = [x0;y0;z0;w0;];

simulation_result = x;


options = optimoptions('fmincon','Algorithm','sqp','Display','none');
uopt = zeros(N,1);

u_max = 0;

% Apply the control input constraints
LB = -3*ones(N,1);
UB = 3*ones(N,1);

x_now = zeros(4,1);
x_next = zeros(4,1);
z = zeros(5,1);

x_now = x;

for ct = 1:(Duration/Ts)
    
     u = NN_output(x_now,10,1,'nn_tora_relu');

     
     z(1) = x_now(1) ;
     z(2) = x_now(2) ;
     z(3) = x_now(3) ;
     z(4) = x_now(4) ;

     z(5) = u ;
     
      
%     x_next = system_eq_NN(x_now, Ts, u);
    x_next = system_eq_dis(x_now, Ts, u);

    x = x_next;
    x_now = x_next;
end

% plot(simulation_result(1,:),simulation_result(2,:), 'color', [223/255, 67/255, 69/255]);
% hold on
plot(simulation_result(1,:),simulation_result(2,:), 'color', [223/255, 67/255, 69/255]);
% title('Benchmark 8 (ReLU)', 'FontSize', 14)
% xlabel('x1', 'FontSize', 14);
% ylabel('x2', 'FontSize', 14);
set(gca,'FontSize',16)
hold on;

fprintf(fileID, formatSpec, simulation_result(1:3,:));

end
fclose(fileID);
% 
% fig = gcf;
% fig.PaperPositionMode = 'auto';
% fig_pos = fig.PaperPosition;
% fig.PaperSize = [fig_pos(3) fig_pos(4)];
% print(fig,'../Benchmarks/benchmark9_relu','-dpdf')
% export_fig ../Benchmarks/benchmark9_relu.pdf
