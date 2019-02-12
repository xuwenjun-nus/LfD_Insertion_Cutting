function moveRobot_2D(s,motorInput,refPos)
% s is the serial port
% q is the commands to the motors
% motorInput(:,1) is the servo position
% motorInput(:,2) is the stepper position

fwrite(s,strcat('RP',num2str(motorInput(1)+refPos(1))));
pause(0.5);
if(motorInput(2)+refPos(2)<1000)
fwrite(s,strcat('BP0',num2str(motorInput(2)+refPos(2))));
else
    fwrite(s,strcat('BP',num2str(motorInput(2)+refPos(2))));
end
end