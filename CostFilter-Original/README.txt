Compiling
=========
To compile this package, you need to have opencv installed.
You can simply use
$cmake .
$make
or just by 
$g++ -fopenmp *.cpp pkg-config opencv --libs --cflags opencv -o CostFilter -fpermissive

To use
======
you can directly use like this
./CostFilter [stereo or flow] [left image] [right image] [max motion] [filtering radius] [eps for filtering]
the last two parameters can be neglected.
for example you can use
./CostFilter stereo left.png right.png 100
./CostFilter flow view1.png view2.png  100 

The outputs are saved in int16 png form. you can use the matlab tools to change or visualize it.
For stereo you could get the results after a few seconds.
While, for optical flow it may take several minutes, because the time complexity is usually 100 times of the stereo.

For parameters and details of the algorithm, you can view [1].


Reference
========
[1] C. Rhemann, A. Hosni, M. Bleyer, C. Rother, and M. Gelautz, “Fast cost-volume filtering for visual correspondence and beyond,” in Proc. Conf. on Computer Vision and Pattern Recognition (CVPR). IEEE, 2011, pp. 3017–3024.



