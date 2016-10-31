close all;
clear;
clc;

cd ..
cd Extractor
dos('./Extractor ../data/left.png model/kitti_stereo_fast16c.bin ../data/left.bin 4');
dos('./Extractor ../data/right.png model/kitti_stereo_fast16c.bin ../data/right.bin 4');
fprintf('Extract feature done...\n');
cd ..
cd 'CostFilter-Improved'
left=sprintf('../data/left.png');
right=sprintf('../data/right.png');

data1=sprintf('../data/left.bin');
data2=sprintf('../data/right.bin');

command=sprintf('./CostFilter stereo %s %s %s %d',left,data1,data2,100);

dos(command);
fprintf('reuslt saved as int16 png file "disp.png"\n');

