#include "libc.h"

int main() {
	long dir = open(".");
	if(dir == -1001){
		puts("Uh oh");
		return 0;
	}

	long length = getlen(dir);
	char buffer[16];
	for(long i = 0; i < length/16; i++){
		//long bytesRead = 
		readFully(dir, buffer, 16);
		//if(bytesRead < 16)
		//	read(dir, buffer + bytesRead, 16 - bytesRead);
		long filePerm = open("filePerm.txt");
		long permLen = getlen(filePerm);
		char* perms[permLen];
		readFully(filePerm, perms, permLen);
		

		for(int i = 0; i < 12; i++){
			if(buffer[i] == 0)
				break;
			putchar(buffer[i]);
		}
		puts("\n");
	}
	
    return 0;
}
