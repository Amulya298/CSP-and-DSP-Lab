#include <stdio.h>
#include <math.h>
#define pi 3.14159
#include "common_functions.h"
int main(void)
{
//declaring and initializing variables
 int fcl,fsl,fch,fsh,fc1,fc2,fsb; //cut off and sampling frequencies of respective filters
 int m,k,n,N=39;
 m=(N-1)/2;
 k=2*m;

 float hl[k],hh[k],hb[k];//LPF,HPF and BPF declaration


 //LPF1 or HBF
 printf("enter the values of fcl and fsl for LPF1:\n");
 scanf("%d\t%d",&fcl,&fsl);

  LPF(fcl,fsl,N,hl);    //calling function LPF
 //LPF1 hl1[n]output
  n=-m;
  for(int i=0;i<=k;i++)
  {
      if((n>=-m)||(n<=m))
      {
           printf(" hl1[%d ] is %f\n",n,hl[i]);
      n=n+1;
      }

  }



 // LPF2
  printf("enter the values of fcl and fsl for LPF2:\n");
  scanf("%d\t%d",&fcl,&fsl);
   LPF(fcl,fsl,N,hl);      //calling function LPF
  //LPF2 hl2[n] output
  n=-m;
  for(int i=0;i<=k;i++)
  {
      if((n>=-m)||(n<=m))
      {
           printf(" hl2[%d ] is %f\n",n,hl[i]);
      n=n+1;
      }

  }

  // HPF
   printf("enter the fch and fsh values\n");
   scanf("%d\t%d",&fch,&fsh);
   HPF(fch,fsh,N,hh);         //calling function  HPF

  //HPF hh[n] output
   n=-m;
  for(int i=0;i<=k;i++)
  {
    if((n>=-m)||(n<=m))
      {
           printf("hh[%d ] is %f\n",n,hh[i]);
      n=n+1;
      }
   }



   // BPF
   printf("enter the fc1 fc2 and fsb values\n");
   scanf("%d\t%d\t%d",&fc1,&fc2,&fsb);
   BPF(fc1,fc2,fsb,N,hb);         //calling function  BPF
   //BPF hb[n] output
   n=-m;
  for(int i=0;i<=k;i++)
  {
     if((n>=-m)||(n<=m))
      {
           printf(" hb[%d ] is %f\n",n,hb[i]);
           n=n+1;
      }
  }
}
