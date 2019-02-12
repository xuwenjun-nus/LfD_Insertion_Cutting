%% This demo shows the inverse kinematics of a three link soft robot
clear all
clear
clc
L=3.2;
N=25;
syms beta k
x=(L*sin(N*beta)/(N*sin(beta)))*sin((N+1)*beta);
y=(L*sin(N*beta)/(N*sin(beta)))*cos((N+1)*beta)+k;
%theta=2*N*beta;
J=jacobian([x;y],[beta k]);
%% Generate the data for trajectory planning
delta_t=0.01;
t=[0:delta_t:1];
M=40*sin(2*pi*t);
N=50+40*cos(2*pi*t);
lamda=1/delta_t;
%% Define the matrix to store joint angles and end effector positions
joint_angle=zeros(length(t),2);
position_x=zeros(length(t),1);
position_y=zeros(length(t),1);
%position_theta=zeros(length(t),1);
%% Initialize the algorithm
q=[pi/3,0.0001];
joint_angle(1,:)=q;
% P denotes the current end effector information
P=[M(1),N(1)];
for i=2:length(t)
    % PP denotes the objective end effector information
    PP=[M(i),N(i)];
    betar=q(1);
    kr=q(2);
    velocity=lamda*pinv(double(subs(J,{beta,k},[betar,kr])))*(PP-P)';
    q=[q(1)+delta_t*velocity(1),q(2)+delta_t*velocity(2)];
     P(1)=double(subs(x,{beta,k},[q(1),q(2)]));
     p(2)=double(subs(y,{beta,k},[q(1),q(2)]));
    joint_angle(i,:)=q;
end
for j=1:length(t)
    betas=joint_angle(j,1);
    ks=joint_angle(j,2);
    position_x(j)=double(subs(x,{beta,k},[betas,ks]));
    position_y(j)=double(subs(y,{beta,k},[betas,ks]));
    %position_theta(j)=subs(theta);
end
plot(M,N,'r')
hold on

plot(position_x,position_y);
