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

char* concat(const char * s1, const char * s2){
    int l1 = 0;
    int l2 = 0;

    while(s1[l1] != 0){
        l1++;
    }

    while(s2[l2] != 0){
        l2++;
    }

    char * ret = malloc(l1 + l2);

    int i = 0;
    for(; i < l1; i++){
        ret[i] = s1[i];
    }
    for(; i < l1 + l2; i++){
        ret[i] = s2[i-l1];
    }
    ret[i] = 0;

    return ret;

}

int main(long d1, long d2, char * user) {
    while (1) {
      
        puts(user);
        puts("> ");

        char* in = gets();
        char * nin = stripSpace(in);
        //puts(in);
        /*
        int i = 0;
        while(tokens[i] != 0){
            puts(tokens[i]);
            puts("|");
            i++;
        }
        */
        if(in[0] != 0){
            nin = concat(" ", nin);
            nin = concat(user, nin);
            //puts(nin);

            char** tokens = tokenize(nin);
            
            //puts("\n");

            int id = fork();
            if(id == 0){

                long exec = execv(tokens[1], tokens);
                if(exec == -1001){
                    notFound(tokens[1]);
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
