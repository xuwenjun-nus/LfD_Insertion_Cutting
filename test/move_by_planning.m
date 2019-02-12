% control the CTSM, based on the motion planning results from yanjie; 
% the positions are all in the image plane
% author: lizheng
% date: 20150108
clear;
close all;
clc;
% connect the CTSM
s = serial('COM5');
set(s,'BaudRate',57600);
fopen(s);
pause(3);
%  fprintf(s, '*IDN?');
%  idn = fscanf(s);
% robot structure
robot.h0=0.8;
robot.D=7.5;
robot.d=5.5;
robot.R=25;
robot.N=21;

% calibration result

calib.Servo=500/(50/180*pi);
%calib.Stepper=400/4;
calib.Stepper=9999/180;
%calib.constraint=125;% 125count per mm

refPos(1)=1500;
refPos(2)=0100;
%refPos(3)=0000; % maximum

% % calibrate
% while(1)
%     
% end

% read the results from motion planning
%path(path,'D:\Dropbox\matlab program\motion planning with yanjie\reprogramcode');
Input_1 = load('2D30Degree20segmentANDMSmallPos.mat');

%Input_2 = load('Input_Im2.mat');
%%
% 
% * ITEM1
% * ITEM2
% 
%Input_3 = load('Input_Ini.mat');
postheta=(Input_1.position(:,1)-101)*0.1;
posz=Input_1.position(:,2)-1;
Pos1 = [postheta posz];
%Pos2 = Input_2.position;
%Pos3 = Input_3.position;

% convert the joint position to the motor control input
motorInput = joint2motor_2D(Pos1,robot,calib)
% motorInput_Im1 = joint2motor_2D(Pos1,robot,calib);
% motorInput_Im2 = joint2motor_2D(Pos2,robot,calib);
% motorInput_Ini = joint2motor_2D(Pos3,robot,calib);
% send the command
%fread(s);azx
fwrite(s,strcat('BP',num2str(0000)));
pause(2)
moveRobot_2D(s,motorInput(1,:),refPos);
%moveRobot_3D(s,motorInput(1,:),refPos);
%pause(5);
1
for i=2:size(motorInput,1)
    moveRobot_2D(s,motorInput(i,:),refPos);
    i
   pause(0.2);
end

fclose(s);




