%% data preprocessing for demonstration
clear all;
clc
% fidin=fopen('EMT_Chen13.txt'); % ??test2.txt?? 
% fidout=fopen('M_13_good.txt','w'); % ??MKMATLAB.txt?? 
% while ~feof(fidin) % ????????? 
% tline=fgetl(fidin); % ????? 
% if double(tline(1))>=48&&double(tline(1))<=57 % ?????????? 
% fprintf(fidout,'%s\n\n',tline); % ????????????????MKMATLAB.txt 
% continue % ????????????? 
% end 
% end 
% fclose(fidout); 
% MK=importdata('M_13_good.txt'); 


% read falcon data
% robot parameters
N=21; % N joints
r=25; 
dd=5.5;
H0=0.8;
falcon=load ('falconChen15.mat');
n=length(falcon.falconChen15(:,1));
for i=1:n  %read line by line 
    %if(falcon.falconChen15(i,1)==0) % if button 0 is pressed , base stepper motor moves
        zb(i)=(falcon.falconChen15(i,3)+100)*45; % stepper motor control value  ???
    %else % if button 1 is pressed, servo moves and robot bend left/right
        angle = falcon.falconChen15(i,2)/(N-1)/180*pi;% bending angle 
        l1= (N-1)*(dd*sin(angle/2)-2*H0*sin(angle/4)*sin(angle/4));
        l2=-(N-1)*(dd*sin(angle/2)+2*H0*sin(angle/4)*sin(angle/4));
	 dalpha1=l1*180/(pi*r);
	 dalpha2=l2*180/(pi*r);
	 dalphax(i)=(abs(dalpha1)+abs(dalpha2))/2*sign(dalpha1); % servo motor control value   degree 
   % end
            
end

