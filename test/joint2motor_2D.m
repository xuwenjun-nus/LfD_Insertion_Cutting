function motorInput = joint2motor_2D(jointPos,robot,calib)
% jointPos is a vector containing the joint rotations
% in this program,only two joints is considered
% the first joint is the rotation
% the second joint is the base translation
M=size(jointPos,1);

% robot is a structure, containing N, d, h0, D, R
% calib is a structure, caontining Servo, Stepper and constraint 

for i=1:M
   %theta(i)=deg2rad(jointPos(i,1));
    theta(i)=jointPos(i,1)/180*pi*2;
    %zb(i)=(jointPos(i,2)-13)*5;
    zb(i)=(jointPos(i,2));
    %cb(i)=(jointPos(i,3)-1)4; %4mm
    
    dL(i)=-robot.N*(robot.d*sin(theta(i)/2)+2*robot.h0*sin(theta(i)/4)^2);
    
    motorInput(i,1)=-dL(i)/robot.R*calib.Servo;
    motortheta=dL(i)/robot.R/pi*180;
   
    motorInput(i,2)=zb(i)*calib.Stepper;
    %zb(i)*calib.Stepper;
    %%motorInput(i,3)=cb(i)*calib.constraint;
end

