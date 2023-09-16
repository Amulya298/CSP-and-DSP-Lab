#include <stdio.h>
#include <math.h>
#define pi 3.14159
#include "common_functions.h"
int main(void)
{
//declaring and initializing variables
  int i,j,M,L,p1;
  int f0=100,f1=200,f2=300,fs=2400,fc,N=39;

  //step 1 x[n] generation
   int lx=48;
   float x[lx];
    printf("The input sequence:x[n]\n");
    for(i=0;i<lx;i++)
    {
        x[i]=sin((2*pi*f0*i)/fs)+0.5*sin((2*pi*f1*i)/fs)+0.6*sin((2*pi*f2*i)/fs);
        printf("x[%d]=%f\n",i,x[i]);
    }

  //step 2 LPF 1 or anti aliasing filter
  int lh=N;
  float h1[lh];        //LPF 1 declaration
  printf("enter the value of fc for LPF1:\n");
  scanf("%d",&fc);
  LPF1(fc,fs,N,h1);    //calling  LPF1 function


  //step 3 calling convolution1 function at LPF 1
   int lxf=lx+lh-1;
   float xf[lxf];
   convol1(x,lx,h1,lh,xf,lxf);


   // step 4 adjusting the length of lxf
   p1=(lh-1)/2;
   j=0;
   for (i=p1;i<lxf-p1;i++)
     {
      xf[j]=xf[i];
      j=j+1;
     }


    printf("enter the down sampling and up sampling factor\n");
    scanf("%d\n%d",&M,&L);

    //step 5 calling  down sampling function

    int lxd= (lx)/M;
    float xd[lxd];
    downsampling(xf,M,lx,xd);

    //step 6 calling up sampling function
    int lxu=lxd*L;
    float xu[lxu];
    upsampling(xd,L,lxu,xu);

    //step 7 LPF 2 (Anti imaging filter)
    float h2[lh];          //LPF 2 declaration
    LPF2(fc,fs,N,h2,L);    //calling function LPF2

    //step 8 convolution 2 at anti-imaging filter
    int ly=lxu+lh-1;
    float y[ly];
    convol2(xu,lxu,h2,lh,y,ly);

    // step 9 adjusting the length of ly
    printf("The output sequence:y[n]\n");
    j=0;
    for (i=p1;i<ly-p1;i++)
    {
      y[j]=y[i];
      printf("y[%d]=%f\n",j,y[j]);
      j=j+1;

    }
    // step 10 error calculation between output and input sequence
    float e[lx];
     printf("The error vector:e[n]\n");
    for(i=0;i<lx;i++)
    {
     e[i]=y[i]-x[i];
     printf("e[%d]=%f\n",i,e[i]);
    }
    //step 11 Average error calculation
    float avg=0;
    for(i=0;i<lx;i++)
    {
     avg=avg+e[i];
    }
    float  avgerror=avg/lx;
    printf("for M=L=%d , Average Error is %f",M,avgerror);

 }




