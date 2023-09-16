




clc
close all
clear all
N=1000000;
bpsk_ber_pr=[];
bpsk_ber_thry=[];
bpsk_ser_pr=[];
bpsk_ser_thry=[];
qpsk_ber_pr=[];
qpsk_ber_thry=[];
qpsk_ser_pr=[];
qpsk_ser_thry=[];
for EbNo_dB=0:1:10
bpsk_er_count=0;
qpsk_er_count=0;
EbNo_L=10^(EbNo_dB/10);
bpsk_snr_L=EbNo_L; 
qpsk_snr_L=(2*EbNo_L);
sd_b=(1/sqrt(2*bpsk_snr_L));
sd_q=(1/sqrt(2*qpsk_snr_L));
for iter=1:N
bbitg=randi([0 1],1,1);
bx=dig_mod_bpsk(bbitg);
bn=sd_b*(randn(1,1)+1i*randn(1,1));
by=bx+bn;
bx_cp=MLdetcbpsk(by);
bpsk_er_count=bpsk_er_count+sum(bx~=bx_cp);
end
bpsk_ser=bpsk_er_count/(N);
bpsk_ser_pr=[bpsk_ser_pr bpsk_ser];
bpsk_ber=bpsk_er_count/(N);
bpsk_ber_pr=[bpsk_ber_pr bpsk_ber];

bpsk_ber_try1=qfunc(sqrt(bpsk_snr_L*2));
bpsk_ber_thry=[bpsk_ber_thry bpsk_ber_try1];
bpsk_ser_try1=qfunc(sqrt(bpsk_snr_L*2));
bpsk_ser_thry=[bpsk_ser_thry bpsk_ser_try1];

for iter=1:2:N
qbitg=randi([0 1],1,2);
qx=dig_mod_qpsk(qbitg);
qn=sd_q*(randn(1,1)+1i*randn(1,1));
qy=qx+qn;
qx_cp=MLdetcqpsk(qy);
qpsk_er_count=qpsk_er_count+sum(qx~=qx_cp);
end
qpsk_ser=qpsk_er_count/(N/2);
qpsk_ser_pr=[qpsk_ser_pr qpsk_ser];

qpsk_ber=qpsk_er_count/(N);
qpsk_ber_pr=[qpsk_ber_pr qpsk_ber];

qpsk_ber_try1=qfunc(sqrt(EbNo_L*2));
qpsk_ber_thry=[qpsk_ber_thry qpsk_ber_try1];
qpsk_ser_try1=2*qfunc(sqrt(EbNo_L*2));
qpsk_ser_thry=[qpsk_ser_thry qpsk_ser_try1];
end
EbNo_dB=0:1:10;
semilogy(EbNo_dB,bpsk_ber_pr,'-x',EbNo_dB,bpsk_ber_thry,'-o',EbNo_dB,bpsk_ser_pr,'-v',EbNo_dB,bpsk_ser_thry,'-x',EbNo_dB,qpsk_ber_pr,'-o',EbNo_dB,qpsk_ber_thry,'-r',EbNo_dB,qpsk_ser_pr,'-v',EbNo_dB,qpsk_ser_thry,'-k');
xlabel('EbNodB');
ylabel('BER/SER');
legend('bpskbersim','bpskberthry','bpsksersim','bpskserthry','qpskbersim','qpskberthry','qpsksersim','qpskserthry');
grid on;
function bx=dig_mod_bpsk(bbitg)
    if (bbitg==0)
        bx=1;
    else
        bx=-1;
    end

end
function qx=dig_mod_qpsk(qbitg)
        if (qbitg(1)==0 && qbitg(2)==0)
        qx=0.707+1i*0.707;
    elseif (qbitg(1)==0 && qbitg(2)==1)
        qx=-0.707+1i*0.707;
    elseif (qbitg(1)==1 && qbitg(2)==1)
        qx=-0.707-1i*0.707;
    elseif (qbitg(1)==1 && qbitg(2)==0)
        qx=0.707-1i*0.707; 
    end

end
function bx_cp=MLdetcbpsk(by)
         d1=sqrt(((real(by)-1))^2+(imag(by))^2);
         d2=sqrt(((real(by)+1))^2+(imag(by))^2);
         if (d1<d2)
             bx_cp=1;
         else
             bx_cp=-1;
         end
  
end

function qx_cp=MLdetcqpsk(qy)    
         d1=sqrt((real(qy)-0.707)^2+(imag(qy)-0.707)^2);
         d2=sqrt((real(qy)+0.707)^2+(imag(qy)-0.707)^2);
         d3=sqrt((real(qy)+0.707)^2+(imag(qy)+0.707)^2);
         d4=sqrt((real(qy)-0.707)^2+(imag(qy)+0.707)^2);
         x=[d1 d2 d3 d4];
         min_dis=min(x);
         if (min_dis==d1)
             qx_cp=0.707+1i*0.707;
         elseif (min_dis==d2)
             qx_cp=-0.707+1i*0.707;
          elseif (min_dis==d3)
             qx_cp=-0.707-1i*0.707;
           elseif (min_dis==d4)
             qx_cp=0.707-1i*0.707;
         end
      
end