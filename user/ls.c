#include "libc.h"

int main(long argc, long argv, char * user) {
	long dir = open(".");
	if(dir == -1001){
		puts("Uh oh");
		return 0;
	}

	long length = getlen(dir);
	char buffer[16];

	long filePerm = open("filePerm");
	long permLen = getlen(filePerm);
	
	char perms[permLen];
	int offset = 0;

	readFully(filePerm, perms, permLen);

	for(long i = 0; i < length/16; i++){
		//For every file in the directory do this:

		readFully(dir, buffer, 16);

		//if(bytesRead < 16)
		//	read(dir, buffer + bytesRead, 16 - bytesRead);


		int permission = 0;

		char permType = perms[offset];
		offset+=2;

		//char user[9];
		if(permType == 'l'){
			char level = perms[offset];
			if(user[8] <= level)
				permission = 1;

		}
		else if(permType == 'u'){
			int index = 0;
			permission = 1;
			while(perms[offset] && user[index] && user[index]!=' ' && index < 8){
				if(perms[offset] != user[index]){
					permission = 0;
					break;
				}
				index++;
				offset++;
			}
		}

		// read the first char
		// read until next space

		//if m
		//call userPerm

		//if u
		//check with user

		//if permission print buffer
		

		if(permission){
			for(int i = 0; i < 12; i++){
				if(buffer[i] == 0)
					break;
				putchar(buffer[i]);
			}
			puts("\n");
		}

		while(perms[offset]!='\n'){
			offset++;
		}
		offset++;

	}
	
    return 0;
}
