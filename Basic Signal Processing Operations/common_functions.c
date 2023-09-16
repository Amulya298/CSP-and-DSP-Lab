#include <stdio.h>
#include "common_functions.h"
//convolution
void convolution(float x[],int lx,float h[],int lh,int p2,float y[])

 {
     int k,n;
    for(n=0;n<p2;n++)
    {
        y[n]=0;
        for(k=0;k<lh;k++)
        {
            if((n-k)>=0 && (n-k)<lx)
            {
           y[n]=y[n]+h[k]*x[n-k];
            }
        }

    }
 }
 //correlation
 void correlation(float x[], int lx, float h[],int lh,int p2, float Rxy[])
 {
     int i,n,k;
     float y1[lh];
     for(i=0;i<lh;i++)
    {
      y1[i]=h[lh-1-i];
    }
   for(n=0;n<p2;n++)
    {
        Rxy[n]=0;
        for(k=0;k<lh;k++)
        {
            if((n-k)>=0 && (n-k)<lx)
            {
           Rxy[n]=Rxy[n]+y1[k]*x[n-k];
            }
        }
    }

 }


//downsampling
void downsampling(float xd[], int M,int lxd, float yd[])

{
 int i=0,j;
   for(j=0;j<lxd;j++)
   {
      if (j%M==0)
     {
         yd[i]=xd[j];
         i++;
     }

   }
}


//upsampling
void upsampling(float xu[], int L,int lxu,int p1, float yu[])

{
    int i=0,j;
   for(j=0;j<p1;j++)
   {
      if (j%L==0)
     {
         yu[i]=xu[j/L];
         i=i+1;
     }
     else
     {
       yu[i]=0;
       i=i+1;
     }
   }
}



