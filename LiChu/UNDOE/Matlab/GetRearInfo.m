function [m,deg,x_position,y_position]  = GetRearInfo()

cam = webcam('USB2.0 PC CAMERA');
% pause(3)
I = snapshot(cam);
I = imrotate(I,180);
imshow(I)
% I = snapshot(cam);
% I = imrotate(I,270);
% imshow(I)
% I=imread('road2.png');

% 顏色處理
Ir = I(:,:,1);
Ig = I(:,:,2);
Ib = I(:,:,3);
Cr = 1;
Cg = 0;
Cb = 0;
Inew = Ir*Cr + Ib*Cb + Ig*Cg;

Inew=medfilt2(Inew,[5,5]);

% 影像處理
threshold = graythresh(Inew);

    % Otsu's method to get a threshold that minimizes the intra-class variance
    % 大津演算法求閾值
bw = im2bw(Inew,threshold);
    % 依據閾值二值化
bw = imfill(~bw,'holes');
bw = bwareaopen(~bw,5000);
bw = bwareaopen(~bw,5000);
[B,L] = bwboundaries(bw,'noholes');

% Display the label matrix and draw each boundary
% imshow(label2rgb(L, @jet, [.5 .5 .5]))
% hold on
% for k = 1:length(B)
%   boundary = B{k};
%   plot(boundary(:,2), boundary(:,1), 'w', 'LineWidth', 2)
% end

stats = regionprops(L,'Area','Centroid');
centroids = stats.Centroid;
% plot(centroids(:,1),centroids(:,2), 'b*')

% figure(1);
% hold on
% plot(centroids(:,1),centroids(:,2), 'b*')
boundary = B{1};
tops = find( abs(boundary(:,2) - 642) == 0 );
bottoms = find( abs(boundary(:,2) - 503) == 1 );

% plot(boundary(I,2), boundary(I,1), 'r*')

[M,I1] = max( boundary(:,2) - centroids(1)  +  boundary(:,1) - centroids(2) );
[M,I2] = min( boundary(:,2) - centroids(1)  +  boundary(:,1) + centroids(2) );
[M,I3] = max( boundary(:,2) + centroids(1)  -  boundary(:,1) + centroids(2) );
[M,I4] = min( boundary(:,2) + centroids(1)  -  boundary(:,1) + centroids(2) );
mid_top = [( boundary(I2,1) + boundary(I3,1) )/2 , ( boundary(I2,2) + boundary(I3,2) )/2];
mid_bottom = [( boundary(I1,1) + boundary(I4,1) )/2 , ( boundary(I1,2) + boundary(I4,2) )/2];

% plot(boundary(I1,2),boundary(I1,1), 'g*');
% plot(boundary(I2,2),boundary(I2,1), 'g*');
% plot(boundary(I3,2),boundary(I3,1), 'g*');
% plot(boundary(I4,2),boundary(I4,1), 'g*');
% plot(mid_bottom(2),mid_bottom(1), 'g*');
% plot(mid_top(2),mid_top(1), 'g*');

m = (mid_top(1)-mid_bottom(1)) / (mid_top(2)-mid_bottom(2));
deg = atan(1/m)* 180/pi;
x_position = centroids(1) - 320;
y_position = centroids(2) - 240;