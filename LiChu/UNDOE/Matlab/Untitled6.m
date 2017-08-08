% https://www.mathworks.com/help/matlab/serial-port-devices.html?requestedDomain=www.mathworks.com

delete(instrfindall);

% If you have Instrument Control Toolbox you can also try >>info =instrhwinfo('serial'), to get all the information about serial ports.
clear;
ASA_PC = serial('com9');
set(ASA_PC,'BaudRate',38400);
set(ASA_PC,'InputBufferSize',5000);

set(ASA_PC, 'FlowControl', 'none');
set(ASA_PC, 'Parity', 'none');
set(ASA_PC, 'DataBits', 8);
set(ASA_PC, 'StopBit', 1);
set(ASA_PC, 'Timeout',100);

fopen(ASA_PC);
% 
% while (1) {
%     data = fgets(ASA_PC);
%     if ( data[1] == 's') {
%         % ?��?
%     }
%     if ( data[1] == 'l') {
%         % �??��?
%     }
%     if ( data[1] == 'r') {
%         % 紅�?
%     }
%     if ( data[1] == 'c') {
%         % 水杯
%     }
%     if ( data[1] == 'k') {
%         % ?��?
%     }
%     if ( data[1] == 'a') {
%         % ?��?
%     }
% }
% 
% fprintf(ASA_PC,'*IDN?')
% out = fscanf(ASA_PC);
% fclose(ASA_PC)
% delete(ASA_PC)
% clear ASA_PC

%

