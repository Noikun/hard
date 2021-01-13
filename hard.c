#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void){
int i,j,k,h,C;
int q;
int T[6] = {0x00,0x00,0x00,0x00,0x00,0x00};
int T_x0yi[6] = {0x00,0x00,0x00,0x00,0x00,0x00};
int x0yi[6] = {0x00,0x00,0x00,0x00,0x00,0x00};
int X[6] = {0x88,0x2f,0xd7,0xf3,0x00,0x00};
int Y[6] = {0x98,0xba,0xc6,0xf6,0x00,0x00};
int N[6] = {0x2b,0x89,0x81,0xf9,0x00,0x00};
int N0[6] = {0x7D,0x82,0x00,0x00,0x00,0x00};
int hh[6];
int hhh[6];
int qn[6];
int yiX[6];

k =256;
C=0;


for(i=0;i<4;i++){
    //T+yix0の導出
    x0yi[0] = X[0]*Y[i];
        h = x0yi[0];
        x0yi[0] = h % 256;
        x0yi[1] = (h - x0yi[0])/256;//x0*yi

    for(j=0;j<6;j++){
    T_x0yi[j] = x0yi[j] + T[j] + C;
    C=0;
        h = x0yi[j];
        x0yi[j] = x0yi[j] % 256;
        C = (h - x0yi[0])/256;
        }//x0*yi+T
 C=0;

//nの掛け算

for(j=0;j<6;j++){
    hh[j] = T_x0yi[j];
    }


    for(j=0;j<6;j++){
    h = N0[0]*hh[j] + C;
    C = 0;
    T_x0yi[j] = h % 256;
    C = (h - T_x0yi[j])/256;
    }//n0計算
 C=0;

    for(j=0;j<6;j++){
    h = N0[1]*hh[j] + C;
    C = 0;
    hhh[j] = h % 256;
    C = (h - hhh[j])/256;
    }//n1計算
 C=0;

for(j=0;j<5;j++){
    T_x0yi[j+1] += hhh[j];
    T_x0yi[j+1] += C;
    C=0;
    h = T_x0yi[j+1];
    T_x0yi[j] = T_x0yi[j] % 256;
    C = (h - T_x0yi[0])/256;
}
//掛け算終わり

//Tの導出
C=0;
q = T_x0yi[0];
printf("q=%02x\n",q);

//qnの導出
for(j=0;j<6;j++){
    h = q*N[j] + C;
    C = 0;
    qn[j] = h % 256;
    C = (h - qn[j])/256; 
    }
    C=0;

// yiX[j]の導出
for(j=0;j<6;j++){
    h = Y[i]*X[j] + C;
    C = 0;
    yiX[j] = h % 256;
    C = (h - yiX[j])/256;
    }
    C=0;

//T+qn+yiXの導出
printf("T+qn+yiX = ");
for(j=0;j<6;j++){
    h = T[j] + qn[j] + yiX[j] + C;
    C = 0;
    T[j] = h % 256;
    
    C = (h - T[j])/256;
    }
    C=0;

T[5]=1;
for(j=5;j>-1;j--){
printf("%02x",T[j]);
}

printf("\n");
printf("T=");

//シフトして256の除算を実行
for(j=0;j<5;j++){
T[j] = T[j+1];
}
for(j=4;j>-1;j--){
printf("%02x",T[j]);
}

printf("\n");
}

return 0;
}

