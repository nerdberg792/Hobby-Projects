#include<stdio.h> 
#include<stdint.h> 
#include<string.h>
#include<unistd.h> 
#include<fcntl.h> 
#include<stdlib.h> 


void simple_prp(const uint32_t key , uint32_t input , uint32_t *output){
	const int num_rounds = 4 ; 
	uint32_t left = input>>16 ; 
	uint32_t right = input & 0xFFFF ; 
	for(int i = 0 ; i < num_rounds ; i++) {
		uint32_t temp = right ; 
		right = left^((right+key+i)*2654435761u) ; 
		left = temp ; 
	}
	*output = (right<<16)|(left&0xFFFF) ; 
}
uint32_t generate_random_key(){
	uint32_t key ; 
	int fd = open("/dev/urandom" , O_RDONLY) ; 
	if(fd<0){
		perror("Error opening /dev/urandom") ; 
		exit(1) ; 
	}
	if(read(fd , &key , sizeof(key))!=sizeof(key)){
		perror("failed to read the random key") ; 
		exit(1) ; 
	}
	close(fd) ;  
	return key ;
}

int main(int argc , char** argv){
	uint32_t input = atoi(argv[1]) ; 
	uint32_t output ; 
	uint32_t key = generate_random_key() ; 
	printf("Generated key : 0x%08X\n" , key ) ; 
	simple_prp(key , input , &output) ;  
	printf("Input : 0x%08X\n" , input ) ; 
	printf("Output : 0x%08X\n" , output) ; 
	return 0 ; 
}

