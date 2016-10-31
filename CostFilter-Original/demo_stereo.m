close all;
clear;
clc;


left=sprintf('../data/left.png');
right=sprintf('../data/right.png');


command=sprintf('./CostFilter stereo %s %s %d',left,right,100);

dos(command);
fprintf('reuslt saved as int16 png file "disp.png"\n');

