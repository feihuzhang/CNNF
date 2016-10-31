function img = flowToColor(flow, varargin)

%  flowToColor(flow, maxFlow) flowToColor color codes flow field, normalize
%  based on specified value, 
% 
%  flowToColor(flow) flowToColor color codes flow field, normalize
%  based on maximum flow present otherwise 


UNKNOWN_FLOW_THRESH = 1e9;
UNKNOWN_FLOW = 1e10;            % 

[height widht nBands] = size(flow);

if nBands ~= 2
    error('flowToColor: image must have two bands');    
end;    

u = flow(:,:,1);
v = flow(:,:,2);

maxu = -999;
maxv = -999;

minu = 999;
minv = 999;
maxrad = 100;

% fix unknown flow
idxUnknown = (abs(u)> UNKNOWN_FLOW_THRESH) | (abs(v)> UNKNOWN_FLOW_THRESH) ;
u(idxUnknown) = 0;
v(idxUnknown) = 0;

maxu = max(maxu, max(u(:)));
minu = min(minu, min(u(:)));

maxv = max(maxv, max(v(:)));
minv = min(minv, min(v(:)));

rad = sqrt(u.^2+v.^2);
maxrad = max(maxrad, max(rad(:)));

fprintf('max flow: %.4f flow range: u = %.3f .. %.3f; v = %.3f .. %.3f\n', maxrad, minu, maxu, minv, maxv);

if isempty(varargin) ==0
    maxFlow = varargin{1};
    if maxFlow > 0
        maxrad = maxFlow;
    end;       
end;

u = u/(maxrad+eps);
v = v/(maxrad+eps);

% compute color

img = computeColor(u, v);  
    
% unknown flow
IDX = repmat(idxUnknown, [1 1 3]);
img(IDX) = 0;
