%plot( [-0.05, 0.05, 0.05, -0.05, -0.05] , [-0.05,-0.05,0.2,0.2,-0.05] , 'color' , [72/255 130/255 197/255], 'LineWidth', 2.0);
hold on;
clear;
Ts = 0.2;  % Sample Time
N = 3;    % Prediction horizon
Duration = 1.8; % Simulation horizon
number = 50;

% For a usual control 0.1 , 5, 20

% Things specfic to the model starts here 

% Limits of initial [-1,1]^2

global simulation_result;
global disturb_range;

disturb_range = 0; % Disturbance range

formatSpec = '%f %f\n';

fileID = fopen('nn_12_relu.txt','w');

for m=1:number
% Setting the initial state

x0 = 0.7 + 0.2*rand(1);
y0 = 0.7 + 0.2*rand(1);

x = [x0;y0;];

simulation_result = x;

% Things specfic to the model  ends here

options = optimoptions('fmincon','Algorithm','sqp','Display','none');
uopt = zeros(N,1);

u_max = 0;

% Apply the control input constraints
LB = -2*ones(N,1);
UB = 2*ones(N,1);

x_now = zeros(2,1);
x_next = zeros(2,1);
z = zeros(3,1);

x_now = x;

% Start simulation
trace = [x_now];
for ct = 1:(Duration/Ts)
     u = NN_output(x_now,4,1,'nn_1_relu');
     % u = NN_output(x_now,4,1,'nn_controller');
     % u = NN_output_tanh(x_now, 0, 4,'controller');
     % u = NN_output_sigmoid(x_now,0.5,8,'nn_1_sigmoid');
     
     z(1) = x_now(1) ;
     z(2) = x_now(2) ;
     z(3) = u;
     
      
%     x_next = system_eq_NN(x_now, Ts, u);
      x_next = system_eq_dis(x_now, Ts, u);

      x = x_next;
      x_now = x_next;
      trace = [trace x_now];
% Save plant states for display.
%    xHistory = [xHistory x]; 


%     Printing stuff

%    disp('x(1) = '); x(1)
%    disp('x(2) = '); x(2)

%    disp('Control input = '); u
    
        
end

% fclose(file);

% figure;
plot(trace(1,:),trace(2,:), 'color', [210/255, 95/255, 95/255]);
% plot(simulation_result(1,:),simulation_result(2,:), 'color', [210/255, 95/255, 95/255]);
% title('Benchmark 1 (ReLU)', 'FontSize', 14)
% xlabel('x1', 'FontSize', 18);
% ylabel('x2', 'FontSize', 18);
set(gca,'FontSize',16)
hold on;

fprintf(fileID, formatSpec, trace(1:2,:));
fprintf(fileID, '%c\n', ['*']);

end

fclose(fileID);
% fig = gcf;
% fig.PaperPositionMode = 'auto';
% fig_pos = fig.PaperPosition;
% fig.PaperSize = [fig_pos(3) fig_pos(4)];
% print(fig,'../Benchmarks/benchmark1_relu','-dpdf')
% export_fig ../Benchmarks/benchmark1_relu.pdf