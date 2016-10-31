#ifndef fpmbp_image_operator_h
#define fpmbp_image_operator_h

//------------------------------------------------------------------------------

#include <functional>	
#include "utils.h"
#include<omp.h> 


//------------------------------------------------------------------------------

namespace pmbp {

//------------------------------------------------------------------------------
  
class Image;
class GraphParticles;

//------------------------------------------------------------------------------

typedef std::function<void(float, float, const State&, float&, float&)> DisplacementFunction;
  
//------------------------------------------------------------------------------

// Performs image operations

class ImageOperator
{
public:
  ImageOperator(float***Data,int Channel,Image** img, Image** grad, Image** filt, int* ww, int* hh, Parameters& params, DisplacementFunction displacement_function);
  virtual ~ImageOperator();
  
  // Patch comparison
  float PatchCost(View view, int x, int y, const State& state, float threshold) const;
  float PixelCost(View target, View source, float x_source, float y_source, float x_target, float y_target, float r_center, float g_center, float b_center) const;
  float PixelCost(View target, View source, float x_source, float y_source, float x_target, float y_target) const;
  // State validity
  bool IsStateValid(View view, int x, int y, const State& state) const;
  void LinearData(View target,float x,float y,float*rem,int tag) const;
  // Images and dimensions (pointer to that of the graph)
void CrossRegion(View view,int x,int y,float *error, float thresh)const;
float CrossAgg(View view, int x, int y, const State& state, float threshold) const;
void CrossAgg( float **RGB,float*&cost,int Height,int Width,int radius,float thresh)const;
void CrossAgg( float **RGB,int*&temp,int Height,int Width,int radius,float thresh,int i)const;
  float*** data;
  int channel;
  Image** images;
  Image** gradients;
  Image** filtered;
  int* w;
  int* h;
  
  // Displacement function object
  DisplacementFunction displacement_function;
  
  // Parameters
  Parameters& parameters;
};

//------------------------------------------------------------------------------
  
}

//------------------------------------------------------------------------------

#endif
