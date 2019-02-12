clc
clear all
fidin=fopen('EMT_test3.txt'); % ??test2.txt?? 
fidout=fopen('test3.txt','w'); % ??MKMATLAB.txt?? 
while ~feof(fidin) % ????????? 
tline=fgetl(fidin); % ????? 
if double(tline(1))>=48&&double(tline(1))<=57 % ?????????? 
fprintf(fidout,'%s\n\n',tline); % ????????????????MKMATLAB.txt 
continue % ????????????? 
end 
end 
fclose(fidout); 
%MK=importdata('test2.txt'); 

% px=zeros(n,1);
% py=zeros(n,1);
% pz=zeros(n,1);
% n=length(x1);
% p=zeros(n,2);
% for i=1:n
%     %EM1=MK(i*2-1,:); 
%     %EM2=MK(i*2,:);
%     p(i,1)=(x1(1)-x2(1))*25.4; % end effector position in mm
%     p(i,2)=(y1(2)-y2(2))*25.4;
%    % p(i,3)=(EM2(3)-EM1(3))*25.4;
%     
% end


