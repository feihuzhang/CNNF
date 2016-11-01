CONTENTS
========
This package of demo code include 6 different parts.

"Extractor":	the feature extractor, for demonstration, we provide 16-channel fast models for stereo and optical. (the rest, including the training code will be published in future.)

"PMBP-original":	the PMBP[3] continuous dense algorithms both for stereo and optical flow. If you set the "weight_pw" value to zero, you could also produce the PatchMatch[2] algorithms' results. In short, this package provides 4 algorithms (PMBP-stereo, PMBP-optical flow, PatchMatch stereo, PatchMatch flow). This package is writen by the author of [2].

"PMBP-improved":	this package is modified from the "PMBP-original" by implementing our features for matching. The 4 matching algorithms are corresponding to the above.

"CostFilter-original":	this is the original costvolume [1] method (particle based) for stereo matching and optical flow.

"CostFilter-improved": this is the improved costfilter with our feature scheme implemented. 

"Tools:"	this package provide some useful matlab tools to change the data form (e.g. 'flo' to 'int16 png', color coding for visualization).

"data:"		this package is some test images from the kitti dataset, you can also try other examples. kitti data can be download at http://www.cvlibs.net/datasets/kitti/index.php

These packages are used to evaluate our feature' performance. You can compare the original algorithm and the improved one with our feature implemented.


TO USE
======
To use these packages, you need to compile them fist. The most easy way is to "cd" into each package and then "cmake ." "make".
Note that these make file is only wrote for the Linux, if you what to use them on the windows, you need to build the project and set the environment.

To successfully compile all of them you need to have the following libs installed.

"Extractor", "CostFilter" and "CostFilter-improved" need the opencv for compiling.
For "PMBP-original" and "PMBP-improved",  It uses the CImg library, which is included in the its tools directory, as well as libpng and zlib which you should install on your machine (and indicate the paths to CMake if it fails to find the packages automatically).

After you compile them successfully, you can try the demo by 

Fist, extractor the feature for both the input images (left and right view). It can be finished in "Extractor" by command 
$./Extractor [input images] [feature model] [output file]

Then, you can try the above dense matching algorithms in each package.

In each package, we provide a matlab/python demo script. You can directly run them if you are not familiar with the steps.
If you want to try new examples, you can only change the inputs name and route in these demo scripts.
For parameters of these algorithms, you need to refer [1][2][3].
There is also a readme file in each of the above packages, you can refer them for more details.


REFERENCE
=========
[1] C. Rhemann, A. Hosni, M. Bleyer, C. Rother, and M. Gelautz, ¡°Fast cost-volume filtering for visual correspondence and beyond,¡± in Proc. Conf. on Computer Vision and Pattern Recognition (CVPR). IEEE, 2011, pp. 3017¨C3024.
[2] M. Bleyer, C. Rhemann, and C. Rother, ¡°Patchmatch stereo-stereo matching with slanted support windows.¡± in British Machine Vision Conference (BMVC), vol. 11, 2011, pp. 1¨C11. 
[3] F. Besse, C. Rother, A. Fitzgibbon, and J. Kautz, ¡°Pmbp: Patchmatch belief propagation for correspondence field estimation,¡± Int¡¯l J. of Computer Vision, vol. 110, no. 1, pp. 2¨C13, 2014.
