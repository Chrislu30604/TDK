clc;clear;
cam = webcam(3);
I = snapshot(cam);
% I=imread('test8.jpg');
Ir = I(:,:,1);
Ig = I(:,:,2);
Ib = I(:,:,3);
Cr = 2;
Cg = 1;
Cb = 1;
%158,179,200
Inew = Ir*Cr - Ib*Cb - Ig*Cg;
% Inew=I(:,:,1)*Cr-I(:,:,2)*Cg-I(:,:,3)*Cb;
figure(2);
imshow(Inew);

[m,n]=size(Inew);
Inew=medfilt2(Inew,[5,5]);%中值濾波
figure(3);
imshow(Inew);
[Im,M]=max(Inew);%最紅的點
[Imm,N]=max(Im);
P_x=N
P_y=M(N)
figure(1);
imshow(I);



text(P_x,P_y,'Redest');

% 
threshold = graythresh(Inew);

    % Otsu's method to get a threshold that minimizes the intra-class variance
    % 大津演算法求閾值
bw = im2bw(Inew,threshold);
    % 依據閾值二值化
figure(2)
imshow(bw)


bw = bwareaopen(~bw,1000);
imshow(bw)

bw = bwareaopen(~bw,1000);
imshow(bw)

se = strel('disk',50);
bw = imclose(bw,se);

imshow(bw)

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
