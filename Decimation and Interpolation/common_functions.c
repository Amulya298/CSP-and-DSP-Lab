#include <stdio.h>
#include <math.h>
#define pi 3.14159
#include "common_functions.h"


//LPF1 (Anti aliasing filter)
void LPF1(int fc,int fs,int N,float h1[])
{
  float wc = (2*pi*fc)/fs;
 int n,m,i,lh;
 m=(N-1)/2;
 lh=N;
 float hdl[lh],WH[lh];
 n=0;
    for(i=-m;i<=m;i++)
    {
        if(i==0)
        {
            hdl[n]=wc/pi;
            n=n+1;
        }
        else
        {

            hdl[n]=sin(wc*(i))/(pi*i);
            n=n+1;
        }

    }
  for(i=0;i<lh;i++)
  {
    WH[i] = (0.54-0.46*cos(2*pi*i/(N-1)));
   h1[i]=WH[i]*hdl[i];
  }

}

//convolution 1

void convol1(float x[],int lx,float h1[],int lh,float xf[],int lxf)

 {
     int k,n;
    for(n=0;n<lxf;n++)
    {
        xf[n]=0;
        for(k=0;k<lh;k++)
        {
            if((n-k)>=0 && (n-k)<lx)
            {
           xf[n]=xf[n]+h1[k]*x[n-k];
            }
        }

    }
 }



 //down sampling
void downsampling(float xf[], int M,int lx, float xd[])

{
 int i=0,j;
   for(j=0;j<lx;j++)
   {
      if (j%M==0)
     {
         xd[i]=xf[j];
         i++;
     }

   }
}



//up sampling
void upsampling(float xd[], int L,int lxd, float xu[])

{
    int i=0,j;
   for(j=0;j<lxd*L;j++)
   {
      if (j%L==0)
     {
         xu[i]=xd[j/L];
         i=i+1;
     }
     else
     {
       xu[i]=0;
       i=i+1;
     }
   }
}


//LPF2 (anti imaging filter)
void LPF2(int fc,int fs,int N,float h2[],int L)
{
  float wc = (2*pi*fc)/fs;
 int n,m,i,lh;
 m=(N-1)/2;
 lh=N;
 float hdl[lh],WH[lh];
 n=0;
    for(i=-m;i<=m;i++)
    {
        if(i==0)
        {
            hdl[n]=wc/pi;
            n=n+1;
        }
        else
        {

            hdl[n]=sin(wc*(i))/(pi*i);
            n=n+1;
        }

    }
  for(i=0;i<lh;i++)
  {
    WH[i] = (0.54-0.46*cos(2*pi*i/(N-1)));
   h2[i]=L*WH[i]*hdl[i];
  }

}
//convolution2

void convol2(float xu[], int lxu, float h2[],int lh, float y[],int ly)

 {
     int k,n;
    for(n=0;n<ly;n++)
    {
        y[n]=0;
        for(k=0;k<lh;k++)
        {
            if((n-k)>=0 && (n-k)<lxu)
            {
           y[n]=y[n]+h2[k]*xu[n-k];
            }
        }

    }
 }
