#include<stdio.h>
#include<unistd.h>

int main(){
	if(link("originalhl.txt", "hardlink.txt") == -1){
		perror("hardlink");
		return 1;
	}
	
	printf("Hard link created successfully");
	return 0;
}
