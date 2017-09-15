clear;clc;
%***********************Initialize*************************
deltaz = 134.2 - 20;
deltay = 4.5;
r1 = 99;
r2 = 159;
r3 = 104.5;
r4 = 93.535;
%***********************給定數據點**************************
xp = 394.025;
yp = 0;
zp = 216.043;
%***********************Angle Calculation******************
[fid,message] = fopen('nameToWrite.txt','w','n','UTF-8');

for yp = -80:80
    J = [0 0 0 0 0 0];    %four servo angle
    J(1) = asin((deltay + yp)/99);                   %J1 OK
 
    J(2) = -J(1);                                    %J2 OK

    parallel = 1;
    if (parallel == 0)
   
    
    
    end
    if (parallel == 1)
        rx = (xp - r4 - r1*cos(J(1)));
        rz = (zp - deltaz);
    end

    r = (rx^2 + rz^2)^0.5;
    theta = atan(rz/rx);
    a1 = r*cos(theta);
    b1 = acos((r^2 + r2^2 - r3^2) / (2*r2*r));
    eq1=sym(['0 =  159*sin(J3) + 104.5*sin(1.5707 + J4 - J3) - ' num2str(a1)]);
    eq2=sym(['1.5707 = J3 + ' num2str(b1 + theta)]);
    sol = solve(eq1,eq2);
    J(3) = real(sol.J3(1,1));
    J(4) = real(sol.J4(2,1));

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
