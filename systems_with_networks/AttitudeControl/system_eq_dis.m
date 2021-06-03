function final_val = system_eq_dis(x_initial,time, control_input)

global simulation_result;
global disturb_range;

d = rand(6,1) * disturb_range * 2 - disturb_range;

function dxdt = system_cont(t,x)
    
    dxdt = [  control_input(1)/4 + x(2)*x(3)/4;
              control_input(2)/2 - 3*x(1)*x(3)/2;
              control_input(3) + 2*x(1)*x(2);
              x(2)*(x(4)^2/2 + x(5)^2/2 + x(6)^2/2 - x(6)/2) + x(3)*(x(4)^2/2 + x(5)^2/2 + x(5)/2 + x(6)^2/2) + x(1)*(x(4)^2/2 + x(5)^2/2 + x(6)^2/2 + 1/2);
              x(1)*(x(4)^2/2 + x(5)^2/2 + x(6)^2/2 + x(6)/2) + x(3)*(x(4)^2/2 - x(4)/2 + x(5)^2/2 + x(6)^2/2) + x(2)*(x(4)^2/2 + x(5)^2/2 + x(6)^2/2 + 1/2);
              x(1)*(x(4)^2/2 + x(5)^2/2 - x(5)/2 + x(6)^2/2) + x(2)*(x(4)^2/2 + x(4)/2 + x(5)^2/2 + x(6)^2/2) + x(3)*(x(4)^2/2 + x(5)^2/2 + x(6)^2/2 + 1/2);];

end

[t ,y] = ode45(@system_cont, [0 time],x_initial);

simulation_result = [simulation_result y'];

% disp(y');

s = size(y);
final_val = y(s(1),:);
final_val = final_val';

end