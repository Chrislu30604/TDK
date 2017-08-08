clc;clear;
cam = webcam(3);
pic = snapshot(cam);
pic = imrotate(pic,90);
% I=imread('test7.jpg');
I = pic;
Ir = I(:,:,1);
Ig = I(:,:,2);
Ib = I(:,:,3);
Cr = 1.0;
Cg = 0.9;
Cb = 2.3;
%158,179,200
Inew = Ib*Cb - Ir*Cr - Ig*Cg;
% Inew=I(:,:,1)*Cr-I(:,:,2)*Cg-I(:,:,3)*Cb;
figure(2);
imshow(Inew);

[m,n]=size(Inew);
Inew=medfilt2(Inew,[5,5]);%中值濾波
figure(3);
imshow(Inew);
[Im,M]=max(Inew);
[Imm,N]=max(Im);
P_x=N
P_y=M(N)
figure(1);
imshow(I);



text(P_x,P_y,'BLUE');

% 
threshold = graythresh(Inew);

    % Otsu's method to get a threshold that minimizes the intra-class variance
    % 大津演算法求閾值
bw = im2bw(Inew,threshold);
    % 依據閾值二值化
figure(4)
imshow(bw)
figure(2)

se = strel('disk',10);
bw = imclose(bw,se);
imshow(bw)
bw = imfill(bw,'holes');
imshow(bw)
bw = bwareaopen(~bw,2000);
% imshow(bw)

bw = bwareaopen(~bw,2000);
% imshow(bw)



[B,L] = bwboundaries(bw,'noholes');

% Display the label matrix and draw each boundary
imshow(label2rgb(L, @jet, [.5 .5 .5]))
hold on
for k = 1:length(B)
  boundary = B{k};
  plot(boundary(:,2), boundary(:,1), 'w', 'LineWidth', 2)
end

stats = regionprops(L,'Area','Centroid');
centroids = stats.Centroid
plot(centroids(:,1),centroids(:,2), 'b*')

figure(1);
hold on
plot(centroids(:,1),centroids(:,2), 'b*')

% figure(2);
hold on
boundary = B{1};
[M,top_right_I] = max(boundary(:,2));
[M,top_left_I] = min(boundary(:,2));
% [M,bottom_I] = max(boundary(:,1));
mid = find( abs(boundary(:,2) - centroids(1)) <1 )
bottom_I = mid(3);
I = top_right_I;
plot(boundary(I,2), boundary(I,1), 'r*')
I = top_left_I;
plot(boundary(I,2), boundary(I,1), 'r*')
I = bottom_I;
plot(boundary(I,2), boundary(I,1), 'r*')

top = ( boundary(top_right_I,:)+boundary(top_left_I,:) )/2;
plot(top(2),top(1), 'r*');
area = stats.Area;
a = boundary(top_right_I,2) - boundary(top_left_I,2);
h = boundary(bottom_I,1) - top(1);
b = 2*area/h-a;
left_down = [ boundary(bottom_I,1) , boundary(bottom_I,2)-b/2 ];
right_down = [ boundary(bottom_I,1) , boundary(bottom_I,2)+b/2 ];

plot(left_down(2),left_down(1), 'r*');
plot(right_down(2),right_down(1), 'r*');


