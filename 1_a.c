#include<stdio.h>
#include<unistd.h>

int main(){
	if(symlink("original.txt", "softlink.txt") == -1){
		perror("symlink");
		return 1;
	}
	
	printf("Soft link created successfully");
	return 0;
}
