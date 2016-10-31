fprintf('Extracting feature for ../data/L1.png ...\n');
dos('./Extractor ../data/L1.png model/kitti_stereo_fast16c.bin ../data/L1.bin 4');
fprintf('Extracting feature for ../data/R1.png ...\n');
dos('./Extractor ../data/R1.png model/kitti_stereo_fast16c.bin ../data/R1.bin 4');
fprintf('feature data saved in ../data/ \n')
