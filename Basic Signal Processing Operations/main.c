#include <stdio.h>
#include "common_functions.h"

int main (void)
{
//declaring and initializing variables
    int i,M,L,p1,p2;
    float x[]={0.5377, 1.8339, -2.2588, 0.8622, 0.3188, -
1.3077, -0.4336, 0.3426, 3.5784, 2.7694, -1.3499, 3.0349,
0.7254, -0.0631, 0.7147, -0.2050, -0.1241, 1.4897, 1.4090,
1.4172};
float h[]={0.6715, -1.2075, 0.7172, 1.6302, 0.4889, 1.0347,
0.7269, -0.3034, 0.2939, -0.7873, 0.8884, -1.1471, -1.0689, -
0.8095, -2.9443};
    float xu[]={0.3252, 1.3703, -0.1022, 0.3192, -0.8649, -0.1649, 1.0933, -0.8637, -1.2141,
    -0.0068, -0.7697, -0.2256, -1.0891, 0.5525, 1.5442, -1.4916, -1.0616, -0.6156};
    float xd[]= {0.3252, -0.7549, 1.3703, -1.7115, -0.1022, -0.2414, 0.3192, 0.3129, -0.8649, -0.0301, -0.1649, 0.6277,
1.0933, 1.1093, -0.8637, 0.0774, -1.2141, -1.1135, -0.0068,1.5326, -0.7697, 0.3714, -0.2256, 1.1174, -1.0891, 0.0326,
0.5525, 1.1006, 1.5442, 0.0859, -1.4916, -0.7423, -1.0616,2.3505, -0.6156, 0.7481};
   int lx = sizeof(x)/sizeof(x[0]);      //length of  x[n] sequence
   int lh = sizeof(h)/sizeof(h[0]);        //length of h[n] sequence
   int lxd = sizeof(xd)/sizeof(xd[0]);      //length of xd[n] down sampling input sequence
   int lxu = sizeof(xu)/sizeof(xu[0]);      //length of xu[n] up sampling input sequence
    printf("enter the down sampling and up sampling factor\n");
    scanf("%d\n%d",&M,&L);
    p1=(L-1)*(lxu-1)+lxu;//length of up sampled sequence
    p2=lx+lh-1;          //length of convoluted and correlated sequence
    float yd[lxd/M],yu[p1];
    float y[p2],Rxy[p2];
    printf("lx=%d,lh=%d,lxd=%d,lxu=%d,p1=%d,p2=%d\n",lx,lh,lxd,lxu,p1,p2);
   //calling function convolution
   convolution(x,lx,h,lh,p2,y);

   //printing convolution output sequence

   printf("convolution output sequence\n");
    for(i=0;i<p2;i++)
    {
    printf("%d element of y[n] sequence:%f\n",i,y[i]);
    }

    //calling function correlation
   correlation(x,lx,h,lh,p2,Rxy);

   //printing correlation output sequence

   printf("correlation output sequence\n");
    for(i=0;i<p2;i++)
    {
    printf("%d element of Rxy[n] sequence:%f\n",(i-(lh-1)),Rxy[i]);
    }


    //calling function down sampling
    downsampling(xd,M,lxd,yd);


    //printing downsampling outputs

    printf("down sampled sequence\n");
    for(i=0;i<(lxd/M);i++)    //(lxd/M) is the length of down sampled signal
    {
    printf("%d element of yd[n] sequence:%f\n",i,yd[i]);
    }


    //calling function upsampling
    upsampling(xu,L,lxu,p1,yu);

    //printing upsampling outputs
    printf("up sampled sequence\n");
    for(i=0;i<p1;i++)
    {
    printf("%d element of yu[n] sequence:%f\n",i,yu[i]);
    }



}
