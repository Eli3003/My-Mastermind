#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "time.h" 
typedef struct codeRaunds{
char*string;
int raunds;
}master;
int my_length(char*string){
    int i = 0;
    while(string[i]!='\0'){
        i++;
    }
  return i;
}
int ishave(char*str,char c){
    for(int i = 0; i < my_length(str);i++){
        if(str[i] == c){
            return 1;
        }
    }
    return 0;
}
char*randStr(){
    srand(time(NULL));
    int j=0;
    char*str = (char*)malloc(sizeof(char)*5);
    for(int i = 0; i < 4; ){
        j = rand()%9;
        if(ishave(str,j+'0')==0){
            str[i]=j+'0';
            i++;
        }
    }
    return str;
}
char*myScanf(){
    char*str = (char*)malloc(sizeof(char)*25);
    int k = 0;
    int index = 0;
    char*s = (char*)malloc(sizeof(char)*2);
    while((index = read(0,&s[0],1))>=0){
        if(index == 0) exit(0);
        if(s[0]=='\n'){
            return str;
        }else{
            str[k] = s[0];
            k++;
        }
    }
    return str;
}
int istrue(char*str){
    if(strlen(str)!=4) return 1;
    for(int i = 0; i < 4;i++){
        if(str[i] > '9' || str[i] < '0') return 1;
    }
    for(int i = 0; i < 3; i++){
        for(int j  = i+1; j < 4;j++){
            if(str[i] == str[j]) return 1;
        }
    }
    return 0;
}
int main(int argc, char**argv){
    master mastermind;
    mastermind.string = randStr();
    mastermind.raunds = 10;
    for(int i = 0; i < argc;i++){
        if(strcmp("-t",argv[i])==0){
            mastermind.raunds = atoi(argv[i+1]);
        }else if(strcmp("-c", argv[i])==0){
            mastermind.string = argv[i+1];
        }
    }
    char*guess;
    printf("Willn you find the secret code?\nPlease enter a valid guess");
    for(int i=0;i < mastermind.raunds;){
        printf("\n---\nRound %d\n",i);
        while(1){
            write(0,">",1);
            guess = myScanf();
            if(strcmp(guess,mastermind.string)==0){
                puts("Congratz! You did it!");
                return 0;
            }
            if(istrue(guess)!=0){
                puts("Wrong input!\n");
            }
            if(istrue(guess)==0){
                int w = 0;
                int m = 0;
                for(int i = 0; i < 4;i++){
                    if(guess[i]==mastermind.string[i]){
                        w++;
                    }
                }
                for(int i = 0; i < 4;i++){
                    if(ishave(mastermind.string,guess[i]) && guess[i] != mastermind.string[i]){
                        m++;
                    }
                }
                printf("Well placed pieces: %d\nMisplaced pieces: %d",w,m);
                break;
            }
        }
    }
    return 0;
}