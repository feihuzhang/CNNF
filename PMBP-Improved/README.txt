This is the improved PMBP algorithms with our feature implemented.
With this package you can test the performance of PMBP[2] stereo/flow and PatchMatch[1] stereo/flow. 
Compiling
=========
$cmake.
$make 
###c++11 is enabled, if you use different compiler, change the setting in CMakeLists.txt
###You should install libpng and zlib on your machine (and indicate the paths to CMake if it fails to find the packages automatically).

To use
======
you can directly run the run_stereo.m/run_stereo.py or run_2dflow.m/run_2dflow.py
or change the parameters  in these files accordingly.


Reference
========
[1] M. Bleyer, C. Rhemann, and C. Rother, ¡°Patchmatch stereo-stereo matching with slanted support windows.¡± in British Machine Vision Conference (BMVC), vol. 11, 2011, pp. 1šC11. 
[2] F. Besse, C. Rother, A. Fitzgibbon, and J. Kautz, ¡°Pmbp: Patchmatch belief propagation for correspondence field estimation,¡± Int¡¯l J. of Computer Vision, vol. 110, no. 1, pp. 2šC13, 2014.



