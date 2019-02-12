%% plot end effector positions: demos and test
clear all
clc
demo1=importdata('M_11_good.txt');
demo2=importdata('M_12_good.txt');
demo3=importdata('M_14_good.txt');
%demo4=importdata('EMT_09_n.txt');
Test=importdata('EMT_60deg_n.txt'); 
n=fix(length(Test(:,1))/2);
n1=fix(length(demo1(:,1))/2);
n2=fix(length(demo2(:,1))/2);
n3=fix(length(demo3(:,1))/2);
%n4=fix(length(demo4(:,1))/2);
px=zeros(n,1);
py=zeros(n,1);
pz=zeros(n,1);


for i=1:n
    EM1=Test(i*2-1,:); 
    EM2=Test(i*2,:);
    Tpx(i)=(EM2(1)-EM1(1))*25.4*0.96; % end effector position in mm
    Tpy(i)=(EM2(2)-EM1(2))*25.4*0.96;
    
end
% only plot EM2 end effector 
% Tpx=Tpx-Test(2,1)*25.4;
% Tpy=Tpy-Test(2,2)*25.4;
for i=1:n1
    EM1=demo1(i*2-1,:); 
    EM2=demo1(i*2,:);
    Dpx1(i)=(EM2(1)-EM1(1))*25.4; % end effector position in mm
    Dpy1(i)=(EM2(2)-EM1(2))*25.4;
    
end
% % only plot EM2 end effector 
% Dpx1=Dpx1-demo1(2,1)*25.4;
% Dpy1=Dpy1-demo1(2,2)*25.4;
for i=1:n2
    EM1=demo2(i*2-1,:); 
    EM2=demo2(i*2,:);
    Dpx2(i)=(EM2(1)-EM1(1))*25.4; % end effector position in mm
    Dpy2(i)=(EM2(2)-EM1(2))*25.4;
    
end
% only plot EM2 end effector 
% Dpx2=Dpx2-demo2(2,1)*25.4;
% Dpy2=Dpy2-demo2(2,2)*25.4;
for i=1:n3
    EM1=demo3(i*2-1,:); 
    EM2=demo3(i*2,:);
    Dpx3(i)=(EM2(1)-EM1(1))*25.4; % end effector position in mm
    Dpy3(i)=(EM2(2)-EM1(2))*25.4;
    
end
% only plot EM2 end effector 
% Dpx3=Dpx3-demo3(2,1)*25.4;
% Dpy3=Dpy3-demo3(2,2)*25.4;
% for i=1:n4
%     EM1=demo4(i*2-1,:); 
%     EM2=demo4(i*2,:);
%     Dpx4(i)=(EM2(1)-EM1(1))*25.4*1.1051; % end effector position in mm
%     Dpy4(i)=(EM2(2)-EM1(2))*25.4;
%     
% end
figure 
plot(Tpx,Tpy,'c','LineWidth',2)
hold on
plot(Dpx1,Dpy1,'r-.','LineWidth',2)
hold on
plot(Dpx2,Dpy2,'b-.','LineWidth',2)
hold on
plot(Dpx3,Dpy3,'g-.','LineWidth',2)
% hold on
% plot(Dpx4,Dpy4,'y-.')
xlabel('X/mm','Fontsize',12)
ylabel('Y/mm','Fontsize',12)
legend('Test','Demo1','Demo2','Demo3','Fontsize',12)

