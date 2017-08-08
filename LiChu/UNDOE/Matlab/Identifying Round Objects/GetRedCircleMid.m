clc;clear;
cam = webcam(3);
I = snapshot(cam);
% I=imread('test5.jpg');
Ir=I(:,:,1)*2-I(:,:,2)-I(:,:,3);  
[m,n]=size(Ir);
Ir=medfilt2(Ir,[5,5]);%中值濾波
figure(3);
imshow(Ir);
[Im,M]=max(Ir);%最紅的點
[Imm,N]=max(Im);
P_x=N
P_y=M(N)
figure(1);
imshow(I);


text(P_x,P_y,'Redest');


threshold = graythresh(Ir);
    % Otsu's method to get a threshold that minimizes the intra-class variance
    % 大津演算法求閾值
bw = im2bw(Ir,threshold);
threshold
    % 依據閾值二值化
figure(2)
imshow(bw)


bw = bwareaopen(~bw,111800);
imshow(bw)

bw = bwareaopen(~bw,111800);
imshow(bw)

se = strel('disk',70);
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
centroids = stats.Centroid;
plot(centroids(:,1),centroids(:,2), 'b*')

figure(1);
hold on
plot(centroids(:,1),centroids(:,2), 'b*')
