% jocabian matrix
clear all
clc
syms theta phi L1 L2 zb
syms l N d % robot parameters 
x=l*sin(N*theta/2)/(sin(theta/2))*sin((N+1)*theta/2)*cos(phi);
y=l*sin(N*theta/2)/(sin(theta/2))*sin((N+1)*theta/2)*sin(phi);
z=zb+l*sin(N*theta/2)/(sin(theta/2))*cos((N+1)*theta/2);

J1=jacobian([x,y,z],[theta, phi])

L1=N*d*cos(phi)*sin(theta/2);
L2=N*d*sin(phi)*sin(theta/2);
zb=-l*sin(N*theta/2)/(sin(theta/2))*cos((N+1)*theta/2);
J2=jacobian([L1,L2,zb],[theta,phi]);

J_final=J1*pinv(J2)