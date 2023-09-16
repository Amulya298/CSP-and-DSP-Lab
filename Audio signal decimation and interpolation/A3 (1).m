clc
close all
clear all
% Read in the sound data
[x,r] = audioread('msmn1.wav');
% Listen to it
soundsc(x,r);
lx=length(x);
figure(1)
specgram(x,1024,r);
N=101;%taps
% Decimation and Interpolation by a factor M=L=2,4,8
M1=4;
L1=M1;
fs=r;
fc1=fs/(2*L1)
wc1=2*pi*fc1/fs
h1=LPF(wc1,N,1);  
lh1=length(h1);
%calling convolution1 function at LPF 1
lxf1=lx+lh1-1;
xf1=convol1(x,lx,h1,lh1,lxf1);
  % adjusting the length of lxf
   p12=(lh1-1)/2;
    b1=0;
   for ii=p12:lxf1-p12-1
      xff1(b1+1)=xf1(ii+1);
      b1=b1+1;
   end
 %calling  down sampling function
lxd1= (lx)/M1;
xd1=downsampling(xff1,M1,lx);
% Listen to it
soundsc(xd1,r/L1);
filename='dec_L2.wav';
audiowrite(filename,xd1,round(r/L1));
pause(3);
 % Look at the spectrogram (spectrum as a function of time)
 figure(2)
specgram(xd1,1024,r/L1);
%calling up sampling function
 lxu1=lxd1*L1;
  xu1=upsampling(xd1,L1,lxu1);
 %step 7 LPF 2 (Anti imaging filter)
    h12=LPF(wc1,N,L1);    %calling function LPF2
  %convolution 2 at anti-imaging filter
    ly1=lxu1+lh1-1;
   y1=convol1(xu1,lxu1,h12,lh1,ly1);
   % adjusting the length of ly
   p12=(lh1-1)/2;
    b12=0;
   for ii=p12:ly1-p12-1
      yff1(b12+1)=y1(ii+1);
      b12=b12+1;
   end
% Listen to it
soundsc(yff1,r);
filename='int_L2.wav';
audiowrite(filename,yff1,r);
figure(3)
specgram(yff1,1024,r);
%----------------------convolution function
function xf=convol1(x,lx,h1,lh,lxf)
xff=[];
    for n=0:lxf-1
     xf(n+1)=0;
        for k=0:lh-1
            if((n-k)>=0 && (n-k)<lx)
           xf(n+1)=xf(n+1)+h1(k+1)*x(n-k+1);
            end
        end
    end
   end
 %------------------downsampling function
function xd=downsampling(xff,M,lx)
 i=1;
   for j=0:lx-1
      if (rem(j,M)==0)
         xd(i)=xff(j+1);
         i=i+1;
      end
   end
end
%--------------------upsampling function
  function xu=upsampling(xd,L,lxu)
    i=1;
   for j=0:lxu-1
      if rem(j,L)==0
         xu(i)=xd((j/L)+1);
         i=i+1;
      else
       xu(i)=0;
       i=i+1;
      end
   end
  end
%---------------------LPF function
function hn=LPF(wc,N,G)
 m=(N-1)/2;
 k=2*m;
 hd=[];
 n=1;
 for i=-m:m
   if (i==0)
     hd(n)=wc/pi;
     n=n+1;
   else
     hd(n)=sin(wc*(i))/(pi*i);
     n=n+1;
   end
 end
 WH=hamm_wind(N);
 for i=1:N
   hn(i)=G*WH(i)*hd(i);
 end
end
%--------------------hamming window
function WH=hamm_wind(N)
WH=[];
for i=1:N
WH(i) = (0.54-0.46*cos(2*pi*(i-1)/(N-1)));
end
end
