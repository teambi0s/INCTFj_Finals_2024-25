#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<string.h>

void main () {
    FILE *enc_f=fopen("enc_flag.txt","r");
    if (enc_f == NULL) {
        printf("no file \n");
    }
    int tim;
    printf("TIME:");
    scanf("%d",&tim);
    srand(tim);

    char hex[3];
    int hd;
    for (int i =0; i<64; i=i+2) {
        fgets(hex,3,enc_f);
        //printf("%s ",hex);
        hd = (int) strtol(hex,NULL,16);
        hd = hd ^ (rand() & 0xff)&0xff;
        printf("%c",hd);

    }
    printf("\n");
}