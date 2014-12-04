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
		for(int j = 0; j < 8 && found; j++){
			if(in[j] == 0 && users[i][j] == ' ')
				return users[i];
			if(users[i][j] != in[j])
				found = 0;
		}
		if(found)
			return users[i];
	}
	notFound(in);
	free(in);
	return "";
}

int main(int argc, char ** argv, char* user){

	char** users = loadUsers();
	char* correctUser = "";
	

	while(correctUser[0] == 0){
		char* in;
		puts("enter valid username> ");
		in = gets();
		correctUser = findUser(users, in);
	}
	//puts(correctUser);
	//puts("\n");

	argv[0] = correctUser;
	argv[1] = "shell";
	//puts("ok\n");
	execv("shell", argv);
    
    return 0;
    
}
