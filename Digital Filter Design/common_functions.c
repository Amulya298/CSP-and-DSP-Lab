#include <stdio.h>
#include <math.h>
#define pi 3.14159
#include "common_functions.h"


//LPF
void LPF(int fcl,int fsl,int N,float hl[])
{
  float wc = (2*pi*fcl)/fsl;
 int n,m,i,k;
 m=(N-1)/2;
 k=2*m;
 float hdl[k],WH[k];
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
  for(i=0;i<=k;i++)
  {
    WH[i] = (0.54-0.46*cos(2*pi*i/(N-1)));
   hl[i]=WH[i]*hdl[i];
  }

}

  //HPF
void HPF(int fch,int fsh,int N,float hh[])
{
float wc = (2*pi*fch)/fsh;
 int n,m,i,k;
 m=(N-1)/2;
 k=2*m;
 float hdh[k],WH[k];
  n=0;
    for(i=-m;i<=m;i++)
    {
        if(i==0)
        {
            hdh[n]=1-(wc/pi);
            n=n+1;
        }
        else
        {

            hdh[n]=(sin(pi*i)-sin(wc*i))/(pi*i);
            n=n+1;
        }

    }
  for(i=0;i<=k;i++)
  {
    WH[i] = (0.54-0.46*cos(2*pi*i/(N-1)));
   hh[i]=WH[i]*hdh[i];
  }
}



  //BPF
void BPF(int fc1,int fc2,int fsb,int N,float hb[])
{
float wc1 = (2*pi*fc1)/fsb, wc2 = (2*pi*fc2)/fsb;;
 int n,m,i,k;
 m=(N-1)/2;
 k=2*m;
 float hdb[k],WH[k];
  n=0;
    for(i=-m;i<=m;i++)
    {
        if(i==0)
        {
            hdb[n]=(wc2/pi)-(wc1/pi);
            n=n+1;
        }
        else
        {

            hdb[n]=(sin(wc2*i)-sin(wc1*i))/(pi*i);
            n=n+1;
        }

    }
for(i=0;i<=k;i++)
  {
    WH[i] = (0.54-0.46*cos(2*pi*i/(N-1)));
   hb[i]=WH[i]*hdb[i];
  }
}







