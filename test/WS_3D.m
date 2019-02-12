% kinematics_3D
theta=linspace(-pi/12,pi/12,100);
zb=linspace(0,90,100);
len=3.2;
len2=10;
N=20;

for zb=0:1:90
    for theta=-pi/24:pi/1200:pi/24
        for phi=-pi:pi/100:pi
            x=len*(sin((N+1)/2*theta)*sin(N*theta/2)/sin(theta/2)+len2*sin((N+1)*theta))*cos(phi);
            y=len*(sin((N+1)/2*theta)*sin(N*theta/2)/sin(theta/2)+len2*sin((N+1)*theta))*sin(phi);
            z=zb+len*cos((N+1)/2*theta)*sin(N*theta/2)/sin(theta/2)+len2*cos((N+1)*theta);
            plot3(x,z,y,'r*')
            hold on
        end
    end
end
axis equal
