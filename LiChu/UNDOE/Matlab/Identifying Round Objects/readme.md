


大津演算法

閾值 表示一個門檻

二值化 利用 pixel-by-pixel operation 把一張灰階圖（gray image）變成一張只有「黑、白」二值的圖。


%Step1. Image read
RGB = imread('test1.jpg');
imshow(RGB);

%Step2. Image binarization
I = rgb2gray(RGB);
    %灰階
threshold = graythresh(I);
    % Otsu's method to get a threshold that minimizes the intra-class variance
    % 大津演算法求閾值
bw = im2bw(I,threshold);
    % 依據閾值二值化
imshow(bw)
