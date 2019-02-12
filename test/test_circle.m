%% test demo1
clear all
clc
load('MP_HAHA.mat');
n=length(MP(1,:));
t=linspace(0,n*0.01,n)
figure

plot(t,MP(1,:),'r','LineWidth',2)
hold on
plot(t,MP(2,:),'g','LineWidth',2)
hold on
plot(t,MP(3,:),'b','LineWidth',2)
xlabel('t','FontSize',16)
ylabel('motor commands','FontSize',16)
legend('Zb','Dalphx','Dalphy')
n=length(MP(1,:));
dalphax=MP(2,:)*500+1500;
dalphay=MP(3,:)*500+1500;
ZB=MP(1,:)*4500+4500;
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
    OCR4B=dalphay(i);
    fwrite(s,strcat('RP',num2str(OCR4A)));
    pause(0.02);
    fwrite(s,strcat('LP',num2str(OCR4B)));
    pause(0.02);
    if(ZB(i)<1000)
        fwrite(s,strcat('BP0',num2str(ZB(i))));
    else
        fwrite(s,strcat('BP',num2str(ZB(i))));
    end
    pause(0.5);
end
fclose(s)