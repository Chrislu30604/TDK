%Step1. Image read
RGB = imread('test2.jpg');
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

%Step3. Remove noise
se = strel('disk',2);
bw = imclose(bw,se);
    %imclose隙縫填滿，比較好分析
bw = bwareaopen(~bw,200);
    %bwareaopen將小於30 pixels的物體移除
    %移除不必要的雜訊，以免造成分析上的不便
bw = imfill(bw,'holes');
    %imfill所有被邊界所圍��來的洞填滿，這樣可以估計regionprops

imshow(bw)

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
stats = regionprops(L,'Area','Centroid');

threshold = 0.94;

% loop over the boundaries
for k = 1:length(B)

  % obtain (X,Y) boundary coordinates corresponding to label 'k'
  boundary = B{k};

  % compute a simple estimate of the object's perimeter
  delta_sq = diff(boundary).^2;
  perimeter = sum(sqrt(sum(delta_sq,2)));

  % obtain the area calculation corresponding to label 'k'
  area = stats(k).Area;

  % compute the roundness metric
  metric = 4*pi*area/perimeter^2;

  % display the results
  metric_string = sprintf('%2.2f',metric);

  % mark objects above the threshold with a black circle
  if metric > threshold
    centroid = stats(k).Centroid;
    plot(centroid(1),centroid(2),'ko');
  end

  text(boundary(1,2)-35,boundary(1,1)+13,metric_string,'Color','y',...
       'FontSize',14,'FontWeight','bold');

end

title(['Metrics closer to 1 indicate that ',...
       'the object is approximately round']);
