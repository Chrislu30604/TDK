%Step1. Image read
RGB = imread('test8.jpg');
figure(1)
imshow(RGB);

%Step2. Image binarization
I = rgb2gray(RGB);
    %¦Ç¶¥
threshold = graythresh(I);
threshold = 0.6
    % Otsu's method to get a threshold that minimizes the intra-class variance
    % ¤j¬zºtºâªk¨DìH­È
bw = im2bw(I,threshold);
    % ¨Ì¾ÚìH­È¤G­È¤Æ
figure(2)
imshow(bw)
figure(3)

%Step3. Remove noise
%se = strel('disk',2);
%bw = imclose(bw,se);
    %imclose»ØÁ_¶ñº¡¡A¤ñ¸û¦n¤ÀªR
bw = bwareaopen(bw,300);
    %bwareaopen±N¤p©ó30 pixelsªºª«Åé²¾°£
    %²¾°£¤£¥²­nªºÂø°T¡A¥H§K³y¦¨¤ÀªR¤Wªº¤£«K
bw = imfill(~bw,'holes');
    %imfill©Ò¦³³QÃä¬É©Ò³òş¨Óªº¬}¶ñº¡¡A³o¼Ë¥i¥H¦ô­pregionprops

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
