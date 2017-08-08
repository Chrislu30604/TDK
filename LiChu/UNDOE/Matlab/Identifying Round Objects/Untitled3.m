clc;clear;
cam = webcam(3);
I = snapshot(cam);
imshow(I)
% 未供電的usb hub 只足夠供一顆視訊頭的電壓

cam_name1 = 'Webcam C170'; % 夾爪
cam_name2 = 'USB2.0_Camera'; % 頭
cam_name3 = 'USB2.0 PC CAMERA'; % 屁股