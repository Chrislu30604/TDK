cam = webcam(2);
pic = snapshot(cam);
imshow(pic); 
figure;
I = rgb2gray(pic);
imshow(I); hold on;
s = detectSURFFeatures(I);
plot(s);
clear cam;