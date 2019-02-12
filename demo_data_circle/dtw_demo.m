% preprocessing motor data by dtw
clear all
clc
m1=importdata('motor_c5.txt');
m2=importdata('motor_c6.txt');
m3=importdata('motor_c7.txt');
m4=importdata('motor_c8.txt');
m5=importdata('motor_c9.txt');
m6=importdata('motor_c10.txt');
m1=m1(171:end,2:4);
m2=m2(202:end,2:4);
m3=m3(185:end,2:4);
m4=m4(177:end,2:4);
m5=m5(178:end,2:4);
m6=m6(181:end,2:4);
figure % plot before alignment
plot3(m1(:,1),m1(:,2),m1(:,3),'b')
hold on
plot3(m2(:,1),m2(:,2),m2(:,3),'r')
hold on
plot3(m3(:,1),m3(:,2),m3(:,3),'g')
hold on
plot3(m4(:,1),m4(:,2),m4(:,3),'k')
hold on
plot3(m5(:,1),m5(:,2),m5(:,3),'c')
hold on
plot3(m6(:,1),m6(:,2),m6(:,3),'m')
xlabel('X/mm','FontSize',14)
ylabel('Y/mm','FontSize',14)
zlabel('Z/mm','FontSize',14)
%hold on
%plot3(m3(:,1),'g*','Linewidth',2)
%legend('Demo1','Demo2','Demo3')
w=50;
[d,p,D]=dtw_multid(m1,m6,w);
[d,p2,D]=dtw_multid(m2,m5,w);
[d,p3,D]=dtw_multid(m3,m4,w);
m1w=m1(p(:,1),:); % after alingment
m6w=m6(p(:,2),:); % after alignment
m2w=m2(p2(:,1),:); % after alingment
m5w=m5(p2(:,2),:); % after alignment
m3w=m3(p3(:,1),:);
m4w=m4(p3(:,2),:);
m_n1=[m1w,m6w];
m_n2=[m2w,m5w];
m_n3=[m3w,m4w];
[dn,pn,Dn]=dtw_multid(m_n1,m_n2,w);
m_n1w=m_n1(pn(:,1),:);
m_n2w=m_n2(pn(:,2),:);
[dn,pn2,Dn]=dtw_multid(m_n2w,m_n3,w);
m_n2w2=m_n2w(pn2(:,1),:);
m_n3w=m_n3(pn2(:,2),:);
m_nn1=[m_n1w,m_n2w];
m_nn2=[m_n2w2,m_n3w];
[dnn,pnn,Dnn]=dtw_multid(m_nn1,m_nn2,w);
m_nn1w=m_nn1(pnn(:,1),:);
m_nn2w=m_nn2(pnn(:,2),:);
m1_f=m_nn1w(:,1:3);
m2_f=m_nn1w(:,7:9);
m3_f=m_nn2w(:,7:9);
m4_f=m_nn2w(:,10:12);
m5_f=m_nn1w(:,10:12);
m6_f=m_nn1w(:,4:6);
m2_ff=m_nn2w(:,1:3);
m5_ff=m_nn2w(:,4:6);

figure
% plot3(m1w(:,1),m1w(:,2),m1w(:,3),'b*','Linewidth',2)
% hold on
% plot3(m6w(:,1),m6w(:,2),m6w(:,3),'g*','Linewidth',2)

% plot all 6 signals after alingment
plot3(m1_f(:,1),m1_f(:,2),m1_f(:,3),'b')
hold on
plot3(m2_f(:,1),m2_f(:,2),m2_f(:,3),'r')
hold on
plot3(m3_f(:,1),m3_f(:,2),m3_f(:,3),'g')
hold on
plot3(m4_f(:,1),m4_f(:,2),m4_f(:,3),'k')
hold on
plot3(m5_f(:,1),m5_f(:,2),m5_f(:,3),'c')
hold on
plot3(m6_f(:,1),m6_f(:,2),m6_f(:,3),'m')
xlabel('X/mm','FontSize',14)
ylabel('Y/mm','FontSize',14)
zlabel('Z/mm','FontSize',14)