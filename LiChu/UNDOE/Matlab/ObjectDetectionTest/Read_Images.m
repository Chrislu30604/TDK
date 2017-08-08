%1
I_obj = rgb2gray(imread('object1.jpg'));
figure(1);
imshow(I_obj);
title('Image of a Obj1');

obj1_Points = detectSURFFeatures(I_obj);

figure(2);
imshow(I_obj);
title('100 Strongest Feature Points from Obj1');
hold on;
plot(selectStrongest(obj1_Points, 100));

%2
cam = webcam(2);
pic = snapshot(cam);
figure(3);
imshow(pic);

gray_pic = rgb2gray(pic);
figure(4);
imshow(gray_pic); hold on;

pic_Points = detectSURFFeatures(gray_pic);
%plot(selectStrongest(pic_Points, 300));
clear cam;


%3
[obj1_Features, obj1_Points] = extractFeatures(I_obj, obj1_Points);
[pic_Features, pic_Points] = extractFeatures(gray_pic, pic_Points);

%Step 4: Find Putative Point Matches
Pairs = matchFeatures(obj1_Features, pic_Features);

matched_obj1_Points = obj1_Points(Pairs(:, 1), :);
matched_pic_Points  = pic_Points(Pairs(:, 2), :);

figure(5);
showMatchedFeatures(I_obj, gray_pic, matched_obj1_Points, matched_pic_Points, 'montage');
title('Putatively Matched Points (Including Outliers)');


%Step 5: Locate the Object in the Scene Using Putative Matches
[tform, inlier_obj1_Points, inlier_pic_Points] = estimateGeometricTransform(matched_obj1_Points, matched_pic_Points, 'affine');

obj1_Polygon = [1, 1;                              % top-left
        size(I_obj, 2), 1;                    % top-right
        size(I_obj, 2), size(I_obj, 1);    % bottom-right
        1, size(I_obj, 1);                    % bottom-left
        1, 1];
    
new_obj1_Polygon = transformPointsForward(tform, obj1_Polygon);

figure(6);
imshow(gray_pic);
hold on;
line(new_obj1_Polygon(:, 1), new_obj1_Polygon(:, 2), 'Color', 'y');
title('Detected obj1');

[B,L] = bwboundaries(bw,'noholes');

% Display the label matrix and draw each boundary
imshow(label2rgb(L, @jet, [.5 .5 .5]))
hold on
for k = 1:length(B)
  boundary = B{k};
  plot(boundary(:,2), boundary(:,1), 'w', 'LineWidth', 2)
end
    