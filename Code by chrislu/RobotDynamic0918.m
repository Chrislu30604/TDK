clear;clc;
%***********************Initialize*************************
deltaz = 0;
deltay = 4.5;
r1 = 99;
r2 = 159;
r3 = 104.5;
r4 = 93.535;
%***********************給定數據點**************************
xp = 300;
yp = 0;
zp = 270;
Jtemp4 = 0;
%***********************Angle Calculation******************
[fid,message] = fopen('nameToWrite1.txt','w','n','UTF-8');

for yp = -70:70
    J = [0 0 0 0 0 0];    %four servo angle
    J(1) = asin((deltay + yp)/99);                   %J1 OK
 
    J(2) = -J(1);                                    %J2 OK

    parallel = 1;         %parllel to floor
    if (parallel == 0)
   
    
    
    end
    if (parallel == 1)
        deltaz = 134.2 - 20;
        rx = (xp - r4 - r1*cos(J(1)));
        rz = (zp - deltaz);
    end

    r = (rx^2 + rz^2)^0.5;
    theta = atan(rz/rx);
    a1 = r*cos(theta);
    b1 = acos((r^2 + r2^2 - r3^2) / (2*r2*r));
    
    eq1=sym(['0 =  159*sin(J3) + 104.5*sin(1.5707 - J4 + abs(J3)) - ' num2str(a1)]);
    eq2=sym(['1.5707 = J3 + ' num2str(b1 + theta)]);
    sol = solve(eq1,eq2);
    J4 = double([real(sol.J4(1,1)), real(sol.J4(2,1))]);
    if (abs(J4(2) - Jtemp4) < 0.1)
        J(3) = real(sol.J3(2,1));
        J(4) = real(sol.J4(2,1));
        Jtemp4 = J4(2);
    else 
        J(3) = real(sol.J3(1,1));
        J(4) = real(sol.J4(1,1));
        Jtemp4 = J4(1);
    end

    if (parallel == 0)
        J(5) = J(4) - J(3) + (pi/3);
    end
    if (parallel == 1)
    	J(5) = J(4) - J(3);
    end
    degree = round(rad2deg(J))
    fprintf(fid,'%d,%d,%d,%d,%d,%d,\r\n',degree);
end

Jtemp4 = 0;

yp = 0;
fprintf(fid,'*********************\r\n');
for i = zp:-1:(zp - 165 )
    J = [0 0 0 0 0 0];    %four servo angle
    J(1) = asin((deltay + yp)/99);                   %J1 OK
 
    J(2) = -J(1);                                    %J2 OK

    parallel = 1;         %parllel to floor
    if (parallel == 0)
   
    
    
    end
    if (parallel == 1)
        deltaz = 134.2 - 20;
        rx = (xp - r4 - r1*cos(J(1)));
        rz = (i - deltaz);
    end

    r = (rx^2 + rz^2)^0.5;
    theta = atan(rz/rx);
    a1 = r*cos(theta);
    b1 = acos((r^2 + r2^2 - r3^2) / (2*r2*r));
    
    eq1=sym(['0 =  159*sin(J3) + 104.5*sin(1.5707 + J4 - abs(J3)) - ' num2str(a1)]);
    eq2=sym(['1.5707 = J3 + ' num2str(b1 + theta)]);
    sol = solve(eq1,eq2);
    J4 = double([real(sol.J4(1,1)), real(sol.J4(2,1))]);
    if (abs(J4(2) - Jtemp4) < 0.1)
        J(3) = real(sol.J3(2,1));
        J(4) = real(sol.J4(2,1));
        Jtemp4 = J4(2);
    else 
        J(3) = real(sol.J3(1,1));
        J(4) = real(sol.J4(1,1));
        Jtemp4 = J4(1);
    end


    if (parallel == 0)
        J(5) = J(4) - J(3) + (pi/3);
    end
    if (parallel == 1)
    	J(5) = J(4) - J(3);
    end
    degree = round(rad2deg(J))
    fprintf(fid,'%d,%d,%d,%d,%d,%d,\r\n',degree);
end
fclose(fid);
