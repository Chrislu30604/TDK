% https://www.mathworks.com/help/matlab/serial-port-devices.html?requestedDomain=www.mathworks.com

delete(instrfindall);

% If you have Instrument Control Toolbox you can also try >>info =instrhwinfo('serial'), to get all the information about serial ports.
clear;
ASA_PC = serial('com5');
set(ASA_PC,'BaudRate',38400);
set(ASA_PC,'InputBufferSize',5000);

set(ASA_PC, 'FlowControl', 'none');
set(ASA_PC, 'Parity', 'none');
set(ASA_PC, 'DataBits', 8);
set(ASA_PC, 'StopBit', 1);
set(ASA_PC, 'Timeout',1000);

fopen(ASA_PC);

i = 1;
a = 1;
start_point =5;

while 1
    if ASA_PC.BytesAvailable > 0
        fprintf('i = %d,BytesAvailable = %d \n',i,ASA_PC.BytesAvailable);
        data = fgets(ASA_PC);
        data
        
        
        if mean( data(1) == 'S' ) == 1
            fprintf(ASA_PC,'%d\n',start_point);
        end
        
%          if mean( data(1:5) == 'GetMicroSec1' ) == 1
%             fprintf(ASA_PC,'%d\n',start_point);
%         end

        if mean( data(1) == 'R' ) == 1
            [m,deg,x,y] = GetRearInfo();
            fprintf(ASA_PC,'%d\n',round(deg*100));
            fprintf('i =%d,deg =%d',i,round(deg*100));
            fprintf(ASA_PC,'%d\n',x);
            fprintf(ASA_PC,'%d\n',y);
        end

        if mean( data(1) == 'F' ) == 1
            fprintf('%d\n',2);
            [m,deg,x,y] = GetFrontInfo();
            fprintf(ASA_PC,'%d\n',round(deg*100));
            fprintf('i =%d,deg =%d',i,round(deg*100));
            fprintf(ASA_PC,'%d\n',x);
            fprintf(ASA_PC,'%d\n',y);
        end

        if mean( data(1) == 'E' ) == 1
            fprintf('%d\n',3);
            break
        end
    end
    %pause(0.2);
    i=i+1;
end

% fprintf(ASA_PC,'*IDN?')
% out = fscanf(ASA_PC)
fclose(ASA_PC)
delete(ASA_PC)
clear ASA_PC

%
