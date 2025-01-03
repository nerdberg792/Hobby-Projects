#include<stdio.h> 
#include<stdlib.h> 
#include<fcntl.h> 
#include<unistd.h> 
#include<string.h> 

void prg(int seed_length , int output_length , unsigned char *output){
	if(output_length<seed_length){
		printf("ouput length must be greater than or equal to seed") ; 
		exit(EXIT_FAILURE) ; 
	}
	int fd = open("/dev/urandom" , O_RDONLY) ; 
	if(fd<0){
		printf("failed to open urandom") ; 
		exit(EXIT_FAILURE) ; 
	}
	unsigned char seed[seed_length] ; 
	if(read(fd , seed , seed_length) != seed_length ) {
		printf("Failed to read seed " ) ; 
		close(fd) ; 
		exit(EXIT_FAILURE) ; 
	}
	for(int i = 0 ; i < output_length ; i++){
		output[i] = seed[i%seed_length] ; 
	}
	close(fd) ; 
} 
int main(int argc , char** argv){
	int seed_length = atoi(argv[1]) ; 
	int output_length = atoi(argv[2]) ; 
	unsigned char output[output_length] ; 
	prg(seed_length , output_length , output) ; 
	printf("PRG ouput : " ) ; 
	for(int i = 0 ; i < output_length ; i++){
		printf("%02x" , output[i]) ; 
	}
	printf("\n") ; 
	return 0 ; 
}


