clear clc

y={0:0.1:10};
A= [1, -2, 3;
    7, 12, 5;
    -1, 2, 8];
    
B=[2, -3, 1];

x=inv(A)*B;

plot(y, x);
