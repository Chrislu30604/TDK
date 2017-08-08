clear; 
close all; 
m=imread('test7.jpg'); 
figure,image(m); % Display the original picture 
r=m(:,:,1); %extract the red color 
g=m(:,:,2); %extract the green color 
b=m(:,:,3); %extract the blue 
hx =[ -1 -2 -1; 0 0 0; 1 2 1]; 
hy =[ -1 0 1; -2 0 2; -1 0 1]; 

% x dirction 'sobel' processing 
xr=filter2(hx,r); 
xg=filter2(hx,g); 
xb=filter2(hx,b); 
%combine the three color 
t1(:,:,1)=xr; 
t1(:,:,2)=xg; 
t1(:,:,3)=xb; 
t=uint8(t1); 
figure, image(t); 
% y dirction 'sobel' processing 
yr=filter2(hy,r); 
yg=filter2(hy,g); 
yb=filter2(hy,b); 
%combine the three color 
t2(:,:,1)=yr; 
t2(:,:,2)=yg; 
t2(:,:,3)=yb; 
t=uint8(t2); 
figure, image(t); 
%combine x and y direction processing 
t3(:,:,1)=xr+yr; 
t3(:,:,2)=xg+yg; 
t3(:,:,3)=xb+yb; 
t = uint8(t3); 
figure, image(t); 

%enforce 
HSV = rgb2hsv(m); 
i = HSV(:,:,3); 
imax= max(max(i)); 
i = i./imax; 
HSV(:,:,3)=i; 
t = hsv2rgb(HSV); 
rt(:,:,1)= uint8(t(:,:,1)*255); 
rt(:,:,2)= uint8(t(:,:,2)*255); 
rt(:,:,3)= uint8(t(:,:,3)*255); 
figure,image(rt); 
rr=rt(:,:,1); 
rg=rt(:,:,2); 
rb=rt(:,:,3); 
% x direction 'sobel' processing 
xr=filter2(hx,rr); 
xg=filter2(hx,rg); 
xb=filter2(hx,rb); 
%combine the three color 
t1(:,:,1)=xr; 
t1(:,:,2)=xg; 
t1(:,:,3)=xb; 
t=uint8(t1); 
figure, image(t); 
% y direction 'sobel' processing 
yr=filter2(hy,rr); 
yg=filter2(hy,rg); 
yb=filter2(hy,rb); 
%combine the three color 
t2(:,:,1)=yr; 
t2(:,:,2)=yg; 
t2(:,:,3)=yb; 
t=uint8(t2); 
figure, image(t); 
% combine x and y direction 
t3(:,:,1)=xr+yr; 
t3(:,:,2)=xg+yg; 
t3(:,:,3)=xb+yb; 
t = uint8(t3); 
figure, image(t);