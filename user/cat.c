#include "libc.h"


int getNextFile(char* perms, char* dest, int offset){
    int i;
    for(i = 0; i < 12; i++){
        dest[i] = 0;
    }

    /*
    for(i = 0; i < 2; i++){
        while(perms[offset] != ' ')
            offset++;
        offset++;
    }
    */

    i = 0;
    while(perms[offset]!='\n'){
        dest[i] = perms[offset];
        offset++;
        i++;
    }
    return offset + 1;

}

int main(int argc, char** argv, char* user) {
    

    for(int i = 1; i < argc; i++){

        long filePerm = open("filePerm");
        long permLen = getlen(filePerm);

        char perms[permLen];
        int offset = 0;

        readFully(filePerm, perms, permLen);

    	char* fileName = argv[i];
        //puts(fileName);
        //puts("\n");

    	long file = open(fileName);
    	if(file == -1001){
    		puts("cat: ");
            puts(fileName);
            puts(": No such file or directory\n");
    		continue;
    	}
        

        int permission = 0;

        char dest[12];
        while(offset<permLen){
            char permType = perms[offset];
            offset+=2;

            if(permType == 'l'){
                char level = perms[offset];
                if(user[8] <= level)
                    permission = 1;
                offset+=2;

            }
            else if(permType == 'u'){
                int index = 0;
                permission = 1;
                while(perms[offset] && user[index] && user[index]!=' ' && index < 8){
                    if(perms[offset] != user[index]){
                        permission = 0;
                        while(perms[++offset]!=' '){}
                        break;
                    }
                    index++;
                    offset++;
                }
                offset++;
            }

            offset = getNextFile(perms, dest, offset);
            
            int i = 0;
            //putdec(permission);
            //puts(dest);
            //puts("\n");

            while(dest[i] && fileName[i]){
                if(dest[i] != fileName[i]){
                    permission = 0;
                    break;
                }
                i++;
            }

            if(fileName[i]!=0){
                permission = 0;
            }

            if(permission == 1)
                break;

            //puts("\n");
        }
        


        if(permission){
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
        else{
            puts("cat: ");
            puts(fileName);
            puts(": No such file or directory\n");
        }
    }
    
    //puts("Cat is done\n");
    return 0;
}

