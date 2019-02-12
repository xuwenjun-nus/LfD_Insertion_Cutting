%% This demo shows the inverse kinematics of a three link soft robot
clear all
clear
clc
L=3.2;
N=21;

syms beta k phi
x=(L*sin(N*beta)/(N*sin(beta)))*sin((N+1)*beta)*cos(phi); % beta=theta/2
y=(L*sin(N*beta)/(N*sin(beta)))*sin((N+1)*beta)*sin(phi);
z=(L*sin(N*beta)/(N*sin(beta)))*cos((N+1)*beta)+k;
%theta=2*N*beta;
J=jacobian([x;y;z],[beta phi k])
%% Generate the data for trajectory planning
delta_t=0.01;
t=[0:delta_t:1];
% desired trajectory
Yr=40*sin(2*pi*t);
Xr=ones(length(t),1)*(-20);
Zr=40*cos(2*pi*t)+13.5683;
%M=40*sin(2*pi*t);
%N=3.2+40*cos(2*pi*t);
lamda=1/delta_t;
%% Define the matrix to store joint angles and end effector positions
joint_angle=zeros(length(t),3);
position_x=zeros(length(t),1);
position_y=zeros(length(t),1);
position_z=zeros(length(t),1);
%position_theta=zeros(length(t),1);
%% Initialize the algorithm
q=[-0.0262,0.00000,0.00001]; % joint space q=[beta, phi, k]
joint_angle(1,:)=q;
% P denotes the current end effector information
P=[Xr(1),Yr(1),Zr(1)];
for i=2:length(t)
    % PP denotes the objective end effector information
    PP=[Xr(i),Yr(i),Zr(i)];
    betar=q(1);
    phir=q(2);
    kr=q(3);
    velocity=lamda*pinv(double(subs(J,{beta,phi,k},[betar,phir,kr])))*(PP-P)';
    P=PP;
    q=[q(1)+delta_t*velocity(1),q(2)+delta_t*velocity(2),q(3)+delta_t*velocity(3)];
    joint_angle(i,:)=q;
end
for j=1:length(t)
    betas=joint_angle(j,1);
    phis=joint_angle(j,2);
    ks=joint_angle(j,3);
    position_x(j)=double(subs(x,{beta,phi,k},[betas,phis,ks]));
    position_y(j)=double(subs(y,{beta,phi,k},[betas,phis,ks]));
    position_z(j)=double(subs(z,{beta,phi,k},[betas,phis,ks]));
    %position_theta(j)=subs(theta);
end
plot3(Xr,Yr,Zr,'r--','Linewidth',2)
hold on
plot3(position_x,position_y,position_z,'b--','Linewidth',2)
