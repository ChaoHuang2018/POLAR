function final_val = system_eq_dis(x_initial,time, control_input)

global simulation_result;
global disturb_range;

d = rand(2,1) * disturb_range * 2 - disturb_range;

function dxdt = system_cont(t,x)
    
    dxdt = [  x(2) - x(1)^3 + d(1);
              control_input + d(2);];

end

[t ,y] = ode45(@system_cont, [0 time],x_initial);

simulation_result = [simulation_result y'];

s = size(y);
final_val = y(s(1),:);
final_val = final_val';

end