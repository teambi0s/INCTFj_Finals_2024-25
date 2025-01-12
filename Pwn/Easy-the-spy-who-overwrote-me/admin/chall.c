#include <stdio.h>
#include <stdlib.h>

init(){
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
}

void print_with_delay(const char *str, int time) {
    for (const char *c = str; *c != '\0'; ++c) {
        putchar(*c);
        fflush(stdout);
        usleep(time * 1000);
    }
}

void win(){
	printf("\033[0;32m");
	printf("\nGood job. Looking forward to working with you in the future, Agent 008.\n");
	printf("\033[0;31m");
	printf("Flag : ");
	char flag[50];
	FILE* fptr;
	fptr = fopen("flag.txt", "r");
	fgets(flag, 50, fptr);
	printf("\033[0;31m");
    printf("%s", flag);
	fclose(fptr);
}

void auth(){
	print_with_delay("Authenticating", 100);
	for(int i=0; i<11; i++){
		print_with_delay(".", 500);
	}
	usleep(500000);
	printf("\33[2K\r"); // remove the printed line
}

void banner(){
	int sel;
	int del = 300000;
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t     00000             0000        7777777777777777/========___________ \n");
	usleep(del);
	printf("\t    00000000         00000000      7777^^^^^^^7777/ || ||   ___________ \n");
	usleep(del);
	printf("\t   000    000       000    000     777       7777/=========//           \n");
	usleep(del);
	printf("\t  000      000     000      000             7777// ((     //            \n");
	usleep(del);
	printf("\t 0000      0000   0000      0000           7777//   ((   //             \n");
	usleep(del);
	printf("\t 0000      0000   0000      0000          7777//========//              \n");
	usleep(del);
	printf("\t 0000      0000   0000      0000         7777                           \n");
	usleep(del);
	printf("\t 0000      0000   0000      0000        7777                            \n");
	usleep(del);
	printf("\t  000      000     000      000        7777                             \n");
	usleep(del);
	printf("\t   000    000       000    000       77777                              \n");
	usleep(del);
	printf("\t    00000000         00000000       7777777                             \n");
	usleep(del);
	printf("\t      0000             0000        777777777                            \n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\033[0;31m");
	print_with_delay("Hi!\n", 20);
	print_with_delay("This is Bond ... James Bond\n", 20);
	print_with_delay("Congratulations You have been chosen to complete a very classified mission.\n", 20);
	print_with_delay("We have infiltrated the house of Dr. NO, a criminal mastermind who has been hiding from our agency for the past 5 years.\n", 20);
	print_with_delay("Our team recovered his computer but it requires a password\n", 20);
	print_with_delay("The computer contains a flag that may lead us to his current hiding place\n", 20);
	print_with_delay("Will you be able to help us bring Dr.NO to light\n", 20);
	printf("\n");
	printf("\033[0;37m");
	print_with_delay("Your mission, should you choose to accept it, is to face your fate\n", 20);
	printf("[ACCEPT] - Press 1\n");
	printf("[REJECT] - Press 0\n");
	printf("Choose:\n");
	scanf("%d", &sel);
	if(sel){
		printf("\033[0;37m");
		printf("\nHappy Hunting ");
		printf("%s", "\U0001f575");
		printf("\n");
		printf("\n");
	}
	else{
		printf("\033[0;31m");
		print_with_delay("This job is not for the faint hearted\n", 20);
		exit(0);
	}

}

int main(){
	init();
	banner();

	char buf[50];
	int attempts = 1;
	int passwd = 0x66616b65;
	printf("\033[0;37m");
	printf("Welcome Dr.NO\n");
	printf("Password please:");
	getchar();
	gets(buf);
	auth();

	if(passwd == 0x44724e6f){
		attempts = 1;
		win();
	}
	else{
		printf("\033[0;36m");
		print_with_delay("Incorrect password\n\n", 20);
		attempts = 0;
	}
	if(!attempts){
		printf("\033[0;31m");
		print_with_delay("Unfortunately, I misjudged you. You are just a stupid policeman... \n", 20);
		print_with_delay("...whose luck has run out.\n", 20);
	}

	return 0;
}
