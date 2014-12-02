#include "libc.h"
int numUsers;

void notFound(char* user) {
    puts(user);
    puts(": user not found");
    puts("\n");
}

char ** loadUsers(){
	long userfile = open("users.txt");
	numUsers = getlen(userfile)/9;
	
	char** users = malloc(4 * numUsers);
	char* buffer = malloc(1);
	for(int i = 0; i < numUsers; i++){
		users[i] = malloc(9);
		readFully(userfile, users[i], 9);
		readFully(userfile, buffer, 1);
		//puts(users[i]);
		//puts("\n");
	}

	return users;

}

char* findUser(char ** users, char* in){
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
	notFound(in);
	return "";
}

int main(int argc, char ** argv, char* user){

	char** users = loadUsers();
	char* correctUser = "";

	while(correctUser[0] == 0){
		puts("username> ");
		char* in = gets();
		correctUser = findUser(users, in);
	}
	//puts(in);

	char** args = malloc(16);
	args[0] = correctUser;
	args[1] = "shell";
	execv("shell", args);
    
    return 0;
    
}
