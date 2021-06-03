function final_val = system_eq_dis(x_initial,time, control_input)

global simulation_result;
global disturb_range;

d = rand(4,1) * disturb_range * 2 - disturb_range;

function dxdt = tora(t,x)
 
    e = 0.1;
    dxdt =[ x(2) + d(1);
%             -x(1) + 2.718281828 * sin(x(3));
            -x(1) + e * sin(x(3)) + d(2);
            x(4) + d(3);
            control_input + d(4) ;];
end

[t ,y] = ode45(@tora, [0 time],x_initial);

simulation_result = [simulation_result y'];

s = size(y);
final_val = y(s(1),:);
final_val = final_val';

end