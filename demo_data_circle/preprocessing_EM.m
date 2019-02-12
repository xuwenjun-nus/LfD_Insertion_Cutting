clc
clear all
fidin=fopen('EMT_circle6_test.txt'); % ??test2.txt?? 
fidout=fopen('EMT_circle6_test_n.txt','w'); % ??MKMATLAB.txt?? 
while ~feof(fidin) % ????????? 
tline=fgetl(fidin); % ????? 
if double(tline(1))>=48&&double(tline(1))<=57 % ?????????? 
fprintf(fidout,'%s\n\n',tline); % ????????????????MKMATLAB.txt 
continue % ????????????? 
end 
end 
fclose(fidout); 
MK=importdata('EMT_circle6_test_n.txt'); 
n=fix(length(MK(:,1))/2)
px=zeros(n,1);
py=zeros(n,1);
pz=zeros(n,1);

for i=1:n
    EM1=MK(i*2-1,:); 
    EM2=MK(i*2,:);
    px(i)=(EM2(1))*25.4; % end effector position in mm
    py(i)=(EM2(2))*25.4;
    pz(i)=(EM2(3))*25.4;
    
end

figure 
plot3(px,py,pz,'r*')
axis equal
