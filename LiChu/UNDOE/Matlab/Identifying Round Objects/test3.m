%Step1. Image read
RGB = imread('test8.jpg');
figure(1)
imshow(RGB);

%Step2. Image binarization
I = rgb2gray(RGB);
    %�Ƕ�
threshold = graythresh(I);
threshold = 0.6
    % Otsu's method to get a threshold that minimizes the intra-class variance
    % �j�z�t��k�D�H��
bw = im2bw(I,threshold);
    % �̾��H�ȤG�Ȥ�
figure(2)
imshow(bw)
figure(3)

%Step3. Remove noise
%se = strel('disk',2);
%bw = imclose(bw,se);
    %imclose���_�񺡡A����n���R
bw = bwareaopen(bw,300);
    %bwareaopen�N�p��30 pixels�����鲾��
    %���������n�����T�A�H�K�y�����R�W�����K
bw = imfill(~bw,'holes');
    %imfill�Ҧ��Q��ɩҳ���Ӫ��}�񺡡A�o�˥i�H���pregionprops

imshow(bw)
figure(4)

%Step4. Find the boundary
[B,L] = bwboundaries(bw,'noholes');

    % Display the label matrix and draw each boundary
imshow(label2rgb(L, @jet, [.5 .5 .5]))
hold on
for k = 1:length(B)
  boundary = B{k};
  plot(boundary(:,2), boundary(:,1), 'w', 'LineWidth', 2)
end

%Circular resolution
