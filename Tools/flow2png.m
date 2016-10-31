function I=flow2png(flow)
I=zeros(size(flow,1),size(flow,2),3);
I(:,:,3)=1;
I(:,:,1)=flow(:,:,1)*64+2^15;
I(:,:,2)=flow(:,:,2)*64+2^15;
I=uint16(I);
%imwrite(uint16(I),'flow.png');

