import os;
import sys;
import platform;

if(platform.system()=="Windows"):
  bin_directory = "bin/Release"
else:
  bin_directory = "bin"

n_iterations = 2; 
patch_size = 20;
max_motion = 220;
n_particles = 1;
weight_pw = 2;
truncate_pw = 1;
tau1 = 20;
tau2 = 20;
alpha = 0.9;
asw = 15;
border = 0.85;
 
out_dir = "outputs/2dflow"

if(platform.system()=="Windows"):
  out_dir = out_dir.replace("/","\\")

os.system("mkdir -p "+out_dir) 

one_name = "../data/L2.png";
two_name = "../data/L1.png";

if(platform.system()=="Windows"):
  exe = "pmbp.exe"
else:
  exe = "./pmbp"
command = exe + " -2dflow " + \
          " -one " + one_name + \
          " -two " + two_name + \
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
          " -out_dir " + str(out_dir)

if(platform.system()=="Windows"):
  command = command.replace("/","\\")

os.system(command)
