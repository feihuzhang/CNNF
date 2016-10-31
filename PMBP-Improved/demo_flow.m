close all;
clear;
clc;

cd ..
cd Extractor
dos('./Extractor ../data/L1.png model/kitti_flow_fast16c.bin ../data/L1.bin 4');
dos('./Extractor ../data/L2.png model/kitti_flow_fast16c.bin ../data/L2.bin 4');
fprintf('Extract feature done...\n');
cd ..
cd 'PMBP-Improved'
left=sprintf('../data/L2.png');
right=sprintf('../data/L1.png');

data1=sprintf('../data/L2.bin');
data2=sprintf('../data/L1.bin');

command=sprintf('./pmbp -2dflow -one %s -two %s -Data1 %s -Data2 %s -n_iterations 2 -patch_size 20 -max_motion 220 -n_particles 1 -weight_pw 0.4 -truncate_pw 0.85 -tau1 2 -tau2 10 -alpha 0.9 -asw 20 -border 0.8 -disp_scale 1 -out_dir outputs/2dflow',left,right,data1,data2);

dos(command);
fprintf('results saved in outputs/2dflow \n');

