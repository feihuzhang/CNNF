close all;
clear;
clc;

cd ..
cd Extractor
dos('./Extractor ../data/L1.png model/kitti_stereo_fast16c.bin ../data/L1.bin 4');
dos('./Extractor ../data/R1.png model/kitti_stereo_fast16c.bin ../data/R1.bin 4');
fprintf('Extract feature done...\n');
cd ..
cd 'PMBP-Improved'
left=sprintf('../data/L1.png');
right=sprintf('../data/R1.png');

data1=sprintf('../data/L1.bin');
data2=sprintf('../data/R1.bin');

command=sprintf('./pmbp -stereo -one %s -two %s -Data1 %s -Data2 %s -n_iterations 2 -patch_size 17 -max_motion 220 -n_particles 1 -weight_pw 0.4 -truncate_pw 0.85 -tau1 2 -tau2 10 -alpha 0.9 -asw 20 -border 0.8 -disp_scale 1 -out_dir outputs/stereo',left,right,data1,data2);

dos(command);
fprintf('results saved in outputs/stereo \n');
