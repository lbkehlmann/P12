#include "libc.h"



void notFound(char* cmd) {
    puts(cmd);
    puts(": command not found");
}

char** tokenize(char* string){
    
    int size = 0;
    int spaces = 0;
    while(string[size] != 0){
        if(string[size] == ' ')
            spaces++;
        size++;
    }

    char** tokens = malloc((size - spaces + 2) * 4);

    tokens[0] = string;

    int si = 0;
    int ti = 1;
    while(string[si] != 0){
        if(string[si] == ' '){
            string[si] = 0;
            tokens[ti] = string + si + 1;
            ti++;
        }
        si++;
        
    }
    tokens[ti] = 0;
    return tokens;
}

char* stripSpace(char* string){
    int len = 0;
    while(string[len] != 0){
        len++;
    }

    char* newString = malloc(len);

    len--;
    while(string[len] == ' '){
        string[len] = 0;
        len--;
    }

    while(string[0] == ' '){
        string++;
    }

    int index = 0;
    int realindex = 0;
    char lastChar = ' ';
    while(string[index] != 0){
        if(!(string[index] == ' ' && lastChar == ' ')){
            memcpy(newString + realindex, string + index, 1);
            realindex++;
        }
        lastChar = string[index];
        index++;
    }
    *(newString + realindex) = 0;


    return newString;
}

int main() {
    while (1) {
        puts("shell> "); 
        char* in = gets();
        in = stripSpace(in);
        char** tokens = tokenize(in);
        
        /*
        int i = 0;
        while(tokens[i] != 0){
            puts(tokens[i]);
            puts("|");
            i++;
        }
        */
        if(tokens[0][0] != 0){
            int id = fork();
            if(id == 0){

                long exec = execv(tokens[0], tokens);
                if(exec == -1001){
                    notFound(tokens[0]);
                }

                puts("\n");
            }

            else {
                join(id);
            }
        }

        if (in) free(in);
    }
    return 0;
}
