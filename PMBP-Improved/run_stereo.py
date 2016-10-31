import os;
import sys;
import platform;

if(platform.system()=="Windows"):
  bin_directory = "bin/Release"
else:
  bin_directory = "bin"#"bin"

n_iterations = 2; 
patch_size = 20;
max_motion = 120;
n_particles = 1;
weight_pw = 0.4;
#the following 7 parameters has no use for when our feature is employed
#############################
truncate_pw = 1;
tau1 = 10;
tau2 = 2;
alpha = 0.45;
asw = 10;
border = 0.8;
output_disparity_scale = 3;
#############################
out_dir = "outputs/stereo"
if(platform.system()=="Windows"):
  out_dir = out_dir.replace("/","\\")
os.system("mkdir -p "+out_dir) 
#image name and the correspoinding feature data file.
os.system("./../Extractor/Extractor ../data/R1.png ../Extractor/model/kitti_stereo_fast16c.bin ../data/R1.bin")
os.system("./../Extractor/Extractor ../data/L1.png ../Extractor/model/kitti_stereo_fast16c.bin ../data/L1.bin")

one_name = "../data/L1.png"
two_name = "../data/R1.png"
one_data = "../data/L1.bin"
two_data = "../data/R1.bin"

if(platform.system()=="Windows"):
  exe = "pmbp.exe"
else:
  exe = "./pmbp"

command = exe + " -stereo " + \
          " -one " + one_name + \
          " -two " + two_name + \
	  " -Data1 " + one_data + \
          " -Data2 " + two_data + \
          " -n_iterations " + str(n_iterations) + \
          " -patch_size " + str(patch_size) + \
          " -max_motion " + str(max_motion) + \
          " -weight_pw " + str(weight_pw) + \
          " -n_particles " + str(n_particles) + \
          " -weight_pw " + str(weight_pw) + \
          " -truncate_pw " + str(truncate_pw) + \
          " -tau1 " + str(tau1) + \
          " -tau2 " + str(tau2) + \
          " -alpha " + str(alpha) + \
          " -asw " + str(asw) + \
          " -border " + str(border) + \
          " -disp_scale " + str(output_disparity_scale) + \
          " -out_dir " + str(out_dir)

if(platform.system()=="Windows"):
  command = command.replace("/","\\")

os.system(command)
