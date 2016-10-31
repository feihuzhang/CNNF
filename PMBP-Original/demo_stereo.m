close all;
clear;
clc;

left=sprintf('../data/L1.png');
right=sprintf('../data/R1.png');

command=sprintf('./pmbp -stereo -one %s -two %s -n_iterations 2 -patch_size 20 -max_motion 220 -n_particles 2 -weight_pw 2 -truncate_pw 0.85 -tau1 2 -tau2 10 -alpha 0.9 -asw 20 -border 0.8 -disp_scale 1 -out_dir outputs/stereo',left,right);

dos(command);

