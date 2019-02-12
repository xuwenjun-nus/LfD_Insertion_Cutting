%% test demo1
clear all
clc
load('ZB.mat');
load('DALPHAX.mat')
n=length(ZB);
s = serial('COM5');
set(s,'BaudRate',57600);
fopen(s);
pause(3);
%  fprintf(s, '*IDN?');
%  idn = fscanf(s);
% robot structure
off_A=1500;
for i=1:n
    i
    OCR4A=off_A+DALPHAX(i)*1000/(100);
    fwrite(s,strcat('RP',num2str(OCR4A)));
    pause(0.5);
    if(ZB(i)<1000)
        fwrite(s,strcat('BP0',num2str(ZB(i))));
    else
        fwrite(s,strcat('BP',num2str(ZB(i))));
    end
    pause(0.5);
end
fclose(s)