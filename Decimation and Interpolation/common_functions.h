//declaring functions
void LPF1(int fc,int fs,int N,float h1[]);
void convol1(float x[], int lx, float h[],int lh, float xf[],int lxf);
void downsampling(float xf[], int M,int lxf, float xd[]);
void upsampling(float xd[], int L,int lxu, float xu[]);
void LPF2(int fc,int fs,int N,float h2[],int L);
void convol2(float xu[], int lxu, float h2[],int lh, float y[],int ly);
