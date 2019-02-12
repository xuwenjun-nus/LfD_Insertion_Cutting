%% test demo1
clear all
clc
load('matlab_2.mat');

n=length(expData(2,:));
dalphax=expData(3,:)*500+1500;
ZB=expData(2,:)*4500+4500;
s = serial('COM5');
set(s,'BaudRate',57600);
fopen(s);
pause(10);
%  fprintf(s, '*IDN?');
%  idn = fscanf(s);
% robot structure
off_A=1500;
for i=1:n
    i
    OCR4A=dalphax(i);
    fwrite(s,strcat('RP',num2str(OCR4A)));
    pause(0.02);
    if(ZB(i)<1000)
        fwrite(s,strcat('BP0',num2str(ZB(i))));
    else
        fwrite(s,strcat('BP',num2str(ZB(i))));
    end
    pause(0.2);
end
fclose(s)