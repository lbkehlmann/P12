#include "libc.h"

int main(int argc, char** argv, char* user) {
    
    for(int i = 1; i < argc; i++){
    	char* fileName = argv[i];
        //puts(fileName);
        //puts("\n");

    	long file = open(fileName);
    	if(file == -1001){
    		puts("cat: ");
    		puts(fileName);
    		puts(": No such file or directory\n");
    		return 0;
    	}

        //long permFile = 
	open("filePerm.txt");
        

    	char buffer[100];
    	long bytesRead = 1;
    	while(bytesRead != 0) {
    		bytesRead = read(file,buffer,100);
    		if(bytesRead < 0)
    			return 0;
    		if(bytesRead == 0) break;
    		for(long i = 0; i < bytesRead; i++) {
    			putchar(buffer[i]);
    		}
    	}
    }
    
    //puts("Cat is done\n");
    return 0;
}

/*
int getPerm(char* user){
    for(int i = 0; i < numUsers; i++){
        int found = 1;
        for(int j = 0; j < 9 && found; j++){
            if(in[j] == 0)
                return in;
            if(users[i][j] != in[j])
                found = 0;
        }
        if(found)
            return in;
    }
}
*/
