%% generate circular patterns within 3D workspace for demo2: cicular tissue cutting
clear all
clc
robot.h0=0.8;
robot.D=7.5;
robot.d=5.5;
robot.R=25;
robot.N=21;
%theta=linspace(-pi/12,pi/12,100);
len=3.2;
len2=10;
N=21;
i=1;
% for zb=0:1:90
%     for theta=-pi/36:pi/1000:pi/36
%         for phi=-pi:pi/1000:0
%             x(i)=len*(sin((N+1)/2*theta)*sin(N*theta/2)/sin(theta/2)+len2*sin((N+1)*theta))*cos(phi);
%             y(i)=len*(sin((N+1)/2*theta)*sin(N*theta/2)/sin(theta/2)+len2*sin((N+1)*theta))*sin(phi);
%             z(i)=zb+len*cos((N+1)/2*theta)*sin(N*theta/2)/sin(theta/2)+len2*cos((N+1)*theta);
%             i=i+1;
%            
%         end
%     end
% end
% 
% for j=1:20
%     lx(j)=0;
%     ly(j)=(j-1)*len;
%     lz(j)=0;
% end
% lx(21)=0;
% ly(21)=ly(20)+len2;
% lz(21)=0;
% figure
% plot3(x,z,y,'r*')
% hold on
% plot3(lx,ly,lz,'ko','MarkerSize',14)
% xlabel ('X/mm')
% ylabel('Z/mm')
% zlabel('Y/mm')
% axis equal
% 
% figure
% plot(x,z,'r*')
% xlabel ('X/mm')
% ylabel('Z/mm')
% axis equal
% 
% figure
% plot(x,y,'r*')
% xlabel ('X/mm')
% ylabel('Y/mm')
% axis equal


%% generate a circle that is on z-y plane, x=-20, r=40mm
% zb=linspace(50,140,100); % in mm
% phi=linspace(-pi,0,100);
% 
% x=len.*(sin((N+1)/2.*theta).*sin(N.*theta/2)./sin(theta/2)+len2.*sin((N+1).*theta)).*cos(phi);
% y=len.*(sin((N+1)/2.*theta).*sin(N.*theta/2)./sin(theta/2)+len2.*sin((N+1).*theta)).*sin(phi);
% z=len.*cos((N+1)/2.*theta).*sin(N.*theta/2)./sin(theta/2)+len2.*cos((N+1).*theta);
% plot3(x,y,z,'r*')
% axis equal

delta_t=0.01;
t=[0:delta_t:1];
% desired trajectory
Yr=40*sin(2*pi*t);
Zr=ones(length(t),1)*(100);
Xr=40*cos(2*pi*t);

% if theta=3deg phi=pi/2
% x=len*(sin((N+1)/2*theta)*sin(N*theta/2)/sin(theta/2))*cos(phi);
% y=len*(sin((N+1)/2*theta)*sin(N*theta/2)/sin(theta/2))*sin(phi);
% z=len*cos((N+1)/2*theta)*sin(N*theta/2)/sin(theta/2);
options = optimset('Display','none','TolFun',1e-8,'MaxFunEvals',500);

for n=1:length(t)
    xy=sqrt(Xr(n)^2+Yr(n)^2);
    eq_x=@(ang)xy-(len*sin(N*ang/2)/sin(ang/2)*sin((N+1)*ang/2)+len2*sin((N+1)*ang));
    thetal(n)=fsolve(eq_x,[1e-3],options);
    
    R=len*sin(N*thetal(n)/2)/sin(thetal(n)/2);

    zbl(n)=Zr(n)-R*cos((N+1)*thetal(n)/2);

    %phi=atan2(y,x);
    theta(n)=asin(sqrt(Xr(n)^2+Yr(n)^2)/(len*N))/(N+1)*2;
    phi(n)=atan2(Yr(n),Xr(n));
    zb(n)=Zr(n)-len*cos((N+1)/2*theta(n))*sin(N*theta(n)/2)/sin(theta(n)/2);
    for i=1:N  % 3D position of each node
        Xn(i)=len*sin(i*theta(n))*cos(phi(n));
        Yn(i)=len*sin(i*theta(n))*sin(phi(n));
        Zn(i)=zbl(n)+len*cos(i*theta(n));
        
    end
    
    plot3(Xn,Yn,Zn,'go')
    hold  on
    plot3(Xn(N),Yn(N),Zn(N),'r*')
    grid on
    drawnow
    pause(0.1)
    xlabel('X/mm')
    ylabel('Y/mm')
    zlabel('Z/mm')

end
dif=-theta-thetal
figure
plot(theta+0.01,'r')
hold on
plot(thetal,'g')


