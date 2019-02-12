%% demo motor data processed with DTW
clear all
clc
m1=importdata('motor_circle1.txt');
m2=importdata('motor_circle2.txt');
m3=importdata('motor_circle3.txt');
figure % plot before alignment
plot(m1(:,1),'r*','Linewidth',2)
hold on
plot(m2(:,1),'b*','Linewidth',2)
hold on
plot(m3(:,1),'g*','Linewidth',2)
legend('Demo1','Demo2','Demo3')
a=m1(:,1:3);
b=m2(:,1:3);
c=m3(:,1:3);
figure
plot3(a(:,1),a(:,2),a(:,3),'r*')
hold on
plot3(b(:,1),b(:,2),b(:,3),'b*')
hold on
plot3(c(:,1),c(:,2),c(:,3),'g*')

w=10;
% [d,p]=dtw_multid(a,b,w);
% bw=b(p(:,2),:);
% aw=a(p(:,1),:);
[Dist,D,k,w,bw,aw]=dtw(b(:,1),a(:,1),0);
[Dist,D,k,w,cw,aw2]=dtw(c(:,1),a(:,1),0);

% figure
% plot(bw(:,1),'b*')
% hold on
% plot(aw(:,1),'r*')
%plot after alingment

% 3D time warping
% example 
[d,p,D]=dtw_multid(c,a,w);
c3w=c(p(:,1),:); % after alingment
a3w=a(p(:,2),:); % after alignment
 figure
 axis equal
% plot(aw,'r*','Linewidth',2)
% hold on
plot3(a3w(:,1),a3w(:,2),a3w(:,3),'b*','Linewidth',2)
hold on
plot3(c3w(:,1),c3w(:,2),c3w(:,3),'g*','Linewidth',2)
%legend('Demo1','Demo2','Demo3')
% 


