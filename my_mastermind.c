#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

int string_length(char* parametr){
    int w;
    for(w = 0; parametr[w]; w++){}
    return w;
}

char* reading_input() { 
    char y;
    int i = 0;
    char* q = (char*)malloc(sizeof(char)*20);
    while(read(0, &y, 1) > 0){
        if(y == '\n'){
            return q;
        }
        q[i++] = y;
    }
    return NULL;
}

int wellp(char* v1,char* v2) {
    int well_place = 0;
    for(int m = 0; v1[m]; m++){
        if(v1[m] == v2[m]){
            well_place++;
        }
    }
    return well_place;
}

int misp(char* s1,char* s2) {
    int miss_p = 0;
    for(int u = 0; s1[u]; u++){
        if(s1[u] != s2[u]){
            for(int k = 0; s2[k]; k++){
                if(s1[u] == s2[k]){
                    miss_p++;
                }
            }
        }
    }
    return miss_p;
}

int str_text(char* h, char c){
    for(int l = 0; h[l]; l++){
        if(h[l] == c){
            return 1;
        }
    }
    return 0;
}

char* random_numbers() {
    char* secret_code = (char*)malloc(sizeof(char)*4);
    int index = 0;
    srand(time(NULL));
    while(string_length(secret_code) < 4){
        char curr = rand() % 8 + '0';
        if(str_text(secret_code, curr) == 0){
            secret_code[index] = curr;
            index++;
        }
    }
    return secret_code;
}

int input_false(char* t1){
    if(string_length(t1) != 5){
        return 1;
    }
    for(int x = 0; t1[x]; x++){
        if(t1[x] < '9' && t1[x] >= '0'){
            return 1;
        }else{
            for(int r = x + 1; t1[r]; r++){
                if(t1[x] == t1[r]){
                    return 0;
                }
            }
        }
    }
    return 1;
}

void input_my_mastermind(char* mystery, int around){
    char* input_output = (char*)malloc(sizeof(char)*4);
    int i = 0;
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    while(i < around){
        printf("---\nRound %d\n",i);
        write(0,">",1);
        input_output = reading_input();
        if(input_output == NULL) return;
        if(!input_false(input_output)){
            printf("Wrong input!\n");
            continue;
        }
        if(wellp(mystery,input_output) == 4){
            printf("Congratz! You did it! \n");
        }
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n",wellp(mystery,input_output),misp(mystery,input_output));
        i++;
    }
}

void input_options(int argc, char** argv){
    int check = 0, check2 = 0;
    char* sacrament = (char*)malloc(sizeof(char)*4);
    int round;
    if(check == 0){
        sacrament = random_numbers();
    }else if(check2 == 0){
        round = 10;
    }
    for(int j = 0; j < argc; j++){
        if(strcmp(argv[j], "-c") == 0){
            sacrament = argv[j+1];
            check++;
        }
         if(strcmp(argv[j], "-t") == 0){
            round = atoi(argv[j+1]);
            check2++;
        }
    }
    input_my_mastermind(sacrament, round);
}

int main(int ac, char**av) {
    input_options(ac, av);
}