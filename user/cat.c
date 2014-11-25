#include "libc.h"

int main(int argc, char** argv) {
    
    for(int i = 1; i < argc; i++){
    	char* fileName = argv[i];
    	long file = open(fileName);
    	if(file == -1001){
    		puts("cat: ");
    		puts(fileName);
    		puts(": No such file or directory\n");
    		return 0;
    	}

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
    
    return 0;
}
