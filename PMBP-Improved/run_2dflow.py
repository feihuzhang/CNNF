import os;
import sys;
import platform;

if(platform.system()=="Windows"):
  bin_directory = "bin/Release"
else:
  bin_directory = "bin"

n_iterations = 2; 
patch_size = 20;
max_motion = 128;
n_particles = 1;
weight_pw = 0.4;
truncate_pw = 1.75;
tau1 = 20;
tau2 = 20;
alpha = 0.45;
asw = 15;
border = 0.85;
output_disparity_scale = 3;
 
out_dir = "outputs/2dflow"

if(platform.system()=="Windows"):
  out_dir = out_dir.replace("/","\\")

os.system("./../Extractor/Extractor ../data/L2.png ../Extractor/model/kitti_flow_fast16c.bin ../data/L2.bin")
os.system("./../Extractor/Extractor ../data/L1.png ../Extractor/model/kitti_flow_fast16c.bin ../data/L1.bin")

os.system("mkdir -p "+out_dir) 


one_name = "../data/L2.png"
two_name = "../data/L1.png"
one_data = "../data/L2.bin"
two_data = "../data/L1.bin"
if(platform.system()=="Windows"):
  exe = "pmbp.exe"
else:
  exe = "./pmbp"
command = exe + " -2dflow " + \
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


print command
if(platform.system()=="Windows"):
  command = command.replace("/","\\")

os.system(command)

