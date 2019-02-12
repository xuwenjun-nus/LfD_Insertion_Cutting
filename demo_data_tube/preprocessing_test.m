clc
clear all
load('test3_demo1.mat')
n=fix(length(test3(:,1))/2);
p=zeros(n,2);
for i=1:n
     EM1=test3(i*2-1,:); 
     EM2=test3(i*2,:);
    p(i,1)=(EM2(1)-EM1(1))*25.4; % end effector position in mm
    p(i,2)=(EM2(2)-EM1(2))*25.4;
   % p(i,3)=(EM2(3)-EM1(3))*25.4;
    
end
