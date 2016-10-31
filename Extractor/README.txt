Compiling
=========
To compile this package, you need to have opencv installed.
You can simply use
$cmake .
$make
or just by 
$g++ -fopenmp *.cpp pkg-config opencv --libs --cflags opencv -o Extractor -fpermissive

To use
======
you can directly use like this
./CostFilter [image name] [feature model] [outputname] [Parallel threads]
the last parameter can be neglected.
for example you can use
for stereo:
./Extractor left.png model/kitti_stereo_fast16c.bin left.bin 
./Extractor right.png model/kitti_stereo_fast16c.bin right.bin 4
for optical flow:
./Extractor view1.png  model/kitti_flow_fast16c.bin view1.bin 
./Extractor view2.png  model/kitti_flow_fast16c.bin view2.bin 4


The outputs are necessary for running our improved PMBP and CostFilter. You can directly run the Extractor_demo.m to get the feature file for both stereo and optical in the data file.

For details, you can see our paper.



