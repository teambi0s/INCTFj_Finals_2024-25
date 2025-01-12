#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void enc(char *flag,int long seed) {
    srand(seed);
    for (int i=0; i<0x20;i++) {
        flag[i] = flag[i] ^ (rand() & 0xff);
    }
}

void main(){
    char flag[0x21];
    FILE *a = fopen("flag.txt","r");  
    if (a==NULL){
        printf("Bruhh!, you have no flag.txt\n");
        exit(0);
    }
    fgets(flag,0x21,a);
    fclose(a);

    int long tim;
    time(&tim);
    printf("Time: %ld\n",tim);

    FILE *enc_flag = fopen("enc_flag.txt","w");

    enc(flag, tim);
    char hex[3];
    for (int j=0; j< 0x20; j++) {
        fprintf(enc_flag, "%02X",flag[j]&0xff);
    }

}

