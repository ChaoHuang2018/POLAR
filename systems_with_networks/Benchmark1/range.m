u = NaN(10000, 1);
low = [ 7.245531140095314e-01 , 8.202206496088046e-01 ];
upp = [ 2.855619999999998e-01 , 1.205562100000000e+00 ];
for t = 1:10000
    x0 = (low(2) - low(1)) *(rand(1)-0.5) + (low(2) + low(1))/2;
    y0 = (upp(2) - upp(1)) *(rand(1)-0.5) + (upp(2) + upp(1))/2;
    x = [x0;y0;];
    u(t) = NN_output_sigmoid(x,0.5,8,'nn_1_sigmoid');
end
max(u)
min(u)

