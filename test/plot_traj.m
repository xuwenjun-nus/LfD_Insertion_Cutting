% plot test circle VS kinematics VS demo 
clear all
clc
load('G3_circle.mat');
c5=importdata('EMT_c5_n.txt');
c7=importdata('EMT_c7_n.txt');
c9=importdata('EMT_c9_n.txt');
test=importdata('EMT_circle4_test_n.txt');
test2=importdata('EMT_circle5_test_n.txt');
n=length(G(1,:));
OCR4A=G(2,:)*500+1500;
OCR4B=G(3,:)*500+1500;
ZB=(G(1,:)*4500+4500)/150;
l=3.2;
d=5.5;
N=21;
r=25;
off_A=1500;
off_B=1500;

% kinematics to compute end-effector
for i=1:n
    l1(i)=(OCR4A(i)-off_A)/1800*pi*r;
    l2(i)=(OCR4B(i)-off_B)/1800*pi*r;

    thetak(i)=2*asin((l1(i)*l1(i)+l2(i)*l2(i))/(N*d));
    phi(i)=atan(l2(i)/l1(i));

    x(i)=l*sin(N*thetak(i)/2)/(sin(thetak(i)/2))*sin((N+1)*thetak(i)/2)*cos(phi(i));
    y(i)=l*sin(N*thetak(i)/2)/(sin(thetak(i)/2))*sin((N+1)*thetak(i)/2)*sin(phi(i));
    z(i)=ZB(i)+l*sin(N*thetak(i)/2)/(sin(thetak(i)/2))*cos((N+1)*thetak(i)/2)-75;
end

% test _without optimization traj
n=fix(length(test(:,1))/2)
px_t=zeros(n,1);
py_t=zeros(n,1);
pz_t=zeros(n,1);
pt0=[test(2,1),test(2,2),test(2,3)];

theta=-0.165;
for i=1:n
    EM1=test(i*2-1,:); 
    EM2=test(i*2,:);
    px_t(i)=(EM2(1)-pt0(1))*25.4*0.9; % end effector position in mm
    %py_t(i)=(EM2(2)-pt0(2))*25.4;
    py_t(i)=(EM2(2)-pt0(2))*25.4*0.9;
    pz_t(i)=(EM2(3)-pt0(3))*25.4; 
    px_tr(i)=cos(theta)*px_t(i)+sin(theta)*pz_t(i);
    pz_tr(i)=-sin(theta)*px_t(i)+cos(theta)*pz_t(i);
end
% demo traj
n=fix(length(c5(:,1))/2)
px5=zeros(n,1);
py5=zeros(n,1);
pz5=zeros(n,1);
p05=[c5(2,1),c5(2,2),c5(2,3)];

for i=1:n
    EM1=c5(i*2-1,:); 
    EM2=c5(i*2,:);
    px5(i)=(EM2(1)-p05(1))*25.4; % end effector position in mm
    py5(i)=(EM2(2)-p05(2))*25.4;
    pz5(i)=(EM2(3)-p05(3))*25.4;
    px5r(i)=cos(theta)*px5(i)+sin(theta)*pz5(i);
    pz5r(i)=-sin(theta)*px5(i)+cos(theta)*pz5(i);
end
n=fix(length(c9(:,1))/2)
px9=zeros(n,1);
py9=zeros(n,1);
pz9=zeros(n,1);
p09=[c9(2,1),c9(2,2),c9(2,3)];

for i=1:n
    EM1=c9(i*2-1,:); 
    EM2=c9(i*2,:);
    px9(i)=(EM2(1)-p09(1))*25.4; % end effector position in mm
    py9(i)=(EM2(2)-p09(2))*25.4;
    pz9(i)=(EM2(3)-p09(3))*25.4;
    px9r(i)=cos(theta)*px9(i)+sin(theta)*pz9(i);
    pz9r(i)=-sin(theta)*px9(i)+cos(theta)*pz9(i);
end
n=fix(length(c7(:,1))/2)
px7=zeros(n,1);
py7=zeros(n,1);
pz7=zeros(n,1);
p07=[c7(2,1),c7(2,2),c7(2,3)];

for i=1:n
    EM1=c7(i*2-1,:); 
    EM2=c7(i*2,:);
    px7(i)=(EM2(1)-p07(1))*25.4; % end effector position in mm
    py7(i)=(EM2(2)-p07(2))*25.4;
    pz7(i)=(EM2(3)-p07(3))*25.4;
    px7r(i)=cos(theta)*px7(i)+sin(theta)*pz7(i);
    pz7r(i)=-sin(theta)*px7(i)+cos(theta)*pz7(i);
end
% plot

figure
plot3(px_tr,py_t,pz_tr,'r','Linewidth',3)
hold on
plot3(px5r,py5,pz5r,'g','Linewidth',2)
hold on
plot3(px7r,py7,pz7r,'b','Linewidth',2)
hold on
plot3(px9r,py9,pz9r,'c','Linewidth',2)
hold on
plot3(z,y,x,'y*','Linewidth',2)

axis equal
xlabel('X/mm')
ylabel('Y/mm')
zlabel('Z/mm')
legend('Test','Demo1','Demo2','Demo3','kinematics')
%hold on
% figure
% axis equal
% xlabel('X/mm')
% ylabel('Y/mm')
% zlabel('Z/mm')
