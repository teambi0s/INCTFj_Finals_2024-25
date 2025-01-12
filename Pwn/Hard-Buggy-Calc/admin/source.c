#include <stdio.h>

void banner(){
    puts("====================================");
            puts(" \n\
   ██████╗ █████╗ ██╗      ██████╗ \n\
  ██╔════╝██╔══██╗██║     ██╔════╝ \n\
  ██║     ███████║██║     ██║      \n\
  ██║     ██╔══██║██║     ██║      \n\
  ╚██████╗██║  ██║███████╗╚██████╗ \n\
   ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝ \n\
                                ");
}

/* Setting up buffering */
void init(){
    setvbuf(stdin,0,_IONBF,0);
    setvbuf(stdout,0,_IONBF,0);
    banner();
}

/* Calculator functions */
int add(int a,int b){
    return a + b;
}

int sub(int a,int b){
    return a - b;
}

int mul(int a,int b){
    return a * b;
}

int div(int a,int b){
    return a / b;
}

/* Driver Code */
int main() {

    size_t option = 0;
    int numa = 0;
    int numb = 0;
    int result;

    int varnum;
    int var[4];
    
    for(int i=0;i<4;i++){var[i] = 0;}

    int (*func[4])(int a,int b);
    func[0] = &add;
    func[1] = &sub;
    func[2] = &mul;
    func[3] = &div;

    
    init();
    while(1) {
        puts("\n====================================");
        puts("| You have the following options - |");
        puts("====================================");
        puts("1. ADD\n2. SUBTRACT\n3. MULTIPLY\n4. DIVIDE\n5. VARIABLES\n6. EXIT");
        printf(">> ");
        scanf("%ld",&option);
        if(option > 6)
            puts("Invalid Option");
        else if (option == 6){
            break;
        } else if (option == 5){
            puts("1. SET VARIABLE\n2. USE VARIABLE");
            printf(">> ");
            scanf("%ld",&option);
            printf("SELECT VARIABLE | <1> <2> <3> <4> | >> ");
            scanf("%d",&varnum);
            if(varnum > 4 || varnum < 1){
                printf("Invalid Variable");
                continue;
            } 
            if(option == 1){
                printf("Enter variable value - ");
                scanf("%d",&var[varnum - 1]);
                printf("The variable has been put in the stash\n");
            } else {
                printf("VARIABLE %d => %d \n",varnum,var[varnum]);
            }
        } else {
            printf("Enter the numbers a : ");
            scanf("%d",&numa);
            printf("Enter the numbers b : ");
            scanf("%d",&numb);
            result = (func[--option])(numa,numb);
            printf("Result from operation : %d\n",result);
        }
    }
    printf("Hoping you liked the calculator");
}