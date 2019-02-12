%% test the servo to draw a circle
clear all
clc
s = serial('COM5');
set(s,'BaudRate',57600);
fopen(s);
pause(3);

H0=0.8;
D=7.5;
dd=5.5;
r=25;
off_A=1500;
off_B=1500;
%theta=linspace(-pi/12,pi/12,100);
len=3.2;
len2=10;

N=21;

angle=pi/3/N;
f=1;% frequency
fwrite(s,strcat('BP',num2str(1500)));
pause(3);
i=0;
for t=0:0.1:10
    t
    i=i+1;
    phi=2*pi*f*t;
    l1= ((N-1)*(dd*sin(angle/2)-2*H0*sin(angle/4)*sin(angle/4)))*sin(phi);
	l3=-((N-1)*(dd*sin(angle/2)+2*H0*sin(angle/4)*sin(angle/4)))*sin(phi);
	l2=(N-1)*(dd*sin(angle/2)-2*H0*sin(angle/4)*sin(angle/4))*cos(phi);
	l4=-((N-1)*(dd*sin(angle/2)+2*H0*sin(angle/4)*sin(angle/4)))*cos(phi);
    dalpha1=l1*180/(pi*r);
    dalpha2=l2*180/(pi*r);
    dalpha3=l3*180/(pi*r);
    dalpha4=l4*180/(pi*r);
    dalphay=(abs(dalpha1)+abs(dalpha3))/2*sign(dalpha1);
	dalphax=(abs(dalpha2)+abs(dalpha4))/2*sign(dalpha4);
     OCR4A=off_A+dalphax*1000/(100);    
	 OCR4B=off_B+dalphay*1000/(100);
     L(i)=OCR4A;
     R(i)=OCR4B;
    fwrite(s,strcat('RP',num2str(OCR4A)));
     pause(0.02);
     fwrite(s,strcat('LP',num2str(OCR4B)));
     pause(0.02);
end
fclose(s)
figure
plot(L,'k')
hold on
plot(R,'r')