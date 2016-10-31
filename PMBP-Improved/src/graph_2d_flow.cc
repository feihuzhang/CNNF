//------------------------------------------------------------------------------

#include "graph_2d_flow.h"

//------------------------------------------------------------------------------

using namespace std;
using namespace std::placeholders;

//------------------------------------------------------------------------------

namespace pmbp{

//------------------------------------------------------------------------------

Graph2DFlow::Graph2DFlow(const Parameters& p) : GraphPmbp(p)
{
  data_dim = 6; // 2d displacement
  meta_dim = 8;
}

//------------------------------------------------------------------------------

Graph2DFlow::~Graph2DFlow()
{
  
}
  
//------------------------------------------------------------------------------

float Graph2DFlow::UnaryEnergy(View view, int x, int y, const State& state, float threshold) const
{
  if(!image_operator->IsStateValid(view, x, y, state))
    return parameters.infinity;
  
  return image_operator->PatchCost(view, x, y, state, threshold);
}

//------------------------------------------------------------------------------

float Graph2DFlow::PairwiseEnergy(View view, int x1, int y1, const State& state1, int x2, int y2, const State& state2) const
{
  float d1 = state1.meta[3];
  float d2 = state2.meta[3];
  
  float dx = x2 - x1;
  float dy = y2 - y1;
  float dd = d2 - d1;
  
  float n1x = state1.meta[0];
  float n1y = state1.meta[1];
  float n1z = state1.meta[2];
  float n2x = state2.meta[0];
  float n2y = state2.meta[1];
  float n2z = state2.meta[2];
  
  float e1 = fabs( n1x*dx + n1y*dy + n1z*dd );
  float e2 = fabs( n2x*dx + n2y*dy + n2z*dd );
/////////////y direction///////////
  d1 = state1.meta[7];
  d2 = state2.meta[7];
  
  dx = x2 - x1;
  dy = y2 - y1;
  dd = d2 - d1;
  
  n1x = state1.meta[4];
  n1y = state1.meta[5];
  n1z = state1.meta[6];
  n2x = state2.meta[4];
  n2y = state2.meta[5];
  n2z = state2.meta[6];
  
  float e3 = fabs( n1x*dx + n1y*dy + n1z*dd );
  float e4 = fabs( n2x*dx + n2y*dy + n2z*dd );
  
  return parameters.weight_pw*std::min(e1+e2+e3+e4,parameters.truncate_pw);
  // Quadratic truncated pairwise term
/*  float dx = state1.data[0]-state2.data[0];
  float dy = state1.data[1]-state2.data[1];
  return parameters.weight_pw*std::min((dx*dx+dy*dy),parameters.truncate_pw);*/
}

//------------------------------------------------------------------------------
  
State Graph2DFlow::GetRandomState(View view, int x, int y) const
{
  State state(data_dim, meta_dim);
  
  // Use the maximum dimension unless max_motion is set to 0
  float max_motion = (parameters.max_motion==0.f?std::max(w[view], h[view]):parameters.max_motion);
  
  // Generate random 2D offset until the motion is within the constraints

  
  // Random depth
  float d = max_motion*Random::DrawUniform(-1.f, 1.f);
  
  // Random normal vector
  float nx = Random::DrawUniform(-1.f, 1.f);
  float ny = Random::DrawUniform(-1.f, 1.f);
  float nz = Random::DrawUniform(-1.f, 1.f);
  
  // Normalize normal vector according to image dimensions
  nx /= w[view];
  ny /= h[view];
  nz /= max_motion;
  
  // Build unit vector
  float length = sqrt(nx*nx + ny*ny + nz*nz);
  nx /= length;
  ny /= length;
  nz /= length;

  state.data[0] = - 1.f * nx / nz;
  state.data[1] = - 1.f * ny / nz;
  state.data[2] = (nx * x + ny * y + nz * d) / nz;
  
  state.meta[0] = nx;
  state.meta[1] = ny;
  state.meta[2] = nz;
  state.meta[3] = d;

///////y direction//////
	
  d = max_motion*Random::DrawUniform(-1.f, 1.f);
  
  // Random normal vector
  nx = Random::DrawUniform(-1.f, 1.f);
  ny = Random::DrawUniform(-1.f, 1.f);
  nz = Random::DrawUniform(-1.f, 1.f);
  
  // Normalize normal vector according to image dimensions
  nx /= w[view];
  ny /= h[view];
  nz /= max_motion;
  
  // Build unit vector
  length = sqrt(nx*nx + ny*ny + nz*nz);
  nx /= length;
  ny /= length;
  nz /= length;

  state.data[3] = - 1.f * nx / nz;
  state.data[4] = - 1.f * ny / nz;
  state.data[5] = (nx * x + ny * y + nz * d) / nz;
  
  state.meta[4] = nx;
  state.meta[5] = ny;
  state.meta[6] = nz;
  state.meta[7] = d;
  return state;

 /* do{
    state.data[0] = max_motion*Random::DrawUniform(-1.f, 1.f);
    state.data[1] = max_motion*Random::DrawUniform(-1.f, 1.f);
  } while(!image_operator->IsStateValid(view, x, y, state));
  
  return state;*/
}
  
//------------------------------------------------------------------------------
  
State Graph2DFlow::GetRandomStateAround(View view, int x, int y, const State& current, float ratio) const
{
  State state = current;
  
  // Use the maximum dimension unless max_motion is set to 0
  float max_motion = (parameters.max_motion==0.f?std::max(w[view], h[view]):parameters.max_motion);
  
  
  float max_delta_z = max_motion*ratio;
  float max_delta_angle = ratio;
  
  // Random amount of change of point depth
  float delta_d = Random::DrawUniform(-1.f, 1.f) * max_delta_z;
  
  // Random amount of change of normal vector
  float delta_nx = Random::DrawUniform(-1.f, 1.f) * max_delta_angle;
  float delta_ny = Random::DrawUniform(-1.f, 1.f) * max_delta_angle;
  float delta_nz = Random::DrawUniform(-1.f, 1.f) * max_delta_angle;
  
  float nx = current.meta[0] + delta_nx;
  float ny = current.meta[1] + delta_ny;
  float nz = current.meta[2] + delta_nz;
  float d = current.meta[3] + delta_d;
  
  // Build unit vector
  float length = sqrt(nx*nx + ny*ny + nz*nz);
  nx /= length;
  ny /= length;
  nz /= length;
  state.data[0] = - 1.f * nx / nz;
  state.data[1] = - 1.f * ny / nz;
  state.data[2] = (nx * x + ny * y + nz * d) / nz;
  
  state.meta[0] = nx;
  state.meta[1] = ny;
  state.meta[2] = nz;
  state.meta[3] = d;
////update y direction
	
   delta_d = Random::DrawUniform(-1.f, 1.f) * max_delta_z;
   delta_nx = Random::DrawUniform(-1.f, 1.f) * max_delta_angle;
   delta_ny = Random::DrawUniform(-1.f, 1.f) * max_delta_angle;
   delta_nz = Random::DrawUniform(-1.f, 1.f) * max_delta_angle;
  
   nx = current.meta[4] + delta_nx;
   ny = current.meta[5] + delta_ny;
   nz = current.meta[6] + delta_nz;
   d = current.meta[7] + delta_d;
  
  // Build unit vector
   length = sqrt(nx*nx + ny*ny + nz*nz);
  nx /= length;
  ny /= length;
  nz /= length;
  state.data[3] = - 1.f * nx / nz;
  state.data[4] = - 1.f * ny / nz;
  state.data[5] = (nx * x + ny * y + nz * d) / nz;
  
  state.meta[4] = nx;
  state.meta[5] = ny;
  state.meta[6] = nz;
  state.meta[7] = d;
 
  return state;
}

//------------------------------------------------------------------------------
  
State Graph2DFlow::GetStateFromNeighbour(View view, int x, int y, int nx, int ny) const
{
  // Retrieve best state of the neighbour
  return GetMinDisbeliefState(view, nx, ny)->Copy();
}
  
//------------------------------------------------------------------------------
  
void Graph2DFlow::GetDisplacement(float x, float y, const State& state, float& dx, float& dy) const
{
  dx = state.data[0] * x + state.data[1] * y + state.data[2];
  dy = state.data[3] * x + state.data[4] * y + state.data[5];
//  dx = state.data[0];
//  dy = state.data[1];
	
}

//------------------------------------------------------------------------------
  
}

//------------------------------------------------------------------------------
